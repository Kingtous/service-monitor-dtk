#include "servicemonitor.h"
#include "httpservicemonitortask.h"
#include "servicegrouprepo.h"

#include <DLog>
#include <QNetworkReply>
#include <QTimer>

using namespace networker::http;

ServiceMonitor::ServiceMonitor() {}

ServiceMonitor::~ServiceMonitor() {}

void ServiceMonitor::initServiceMonitor()
{
    pool.setMaxThreadCount(QThread::idealThreadCount());
    pool.setExpiryTimeout(30 * 1000); // 30s 任务过期
    auto groups = ServiceGroupRepo::instance()->getServiceGroups();
    auto it = groups.begin();
    while (it != groups.end()) {
        auto services = it->getServices();
        auto sit = services->begin();
        while (sit != services->end()) {
            this->addServiceItemToPool(*sit);
            sit++;
        }
        it++;
    }
}

bool ServiceMonitor::isInService() { return inService; }

bool ServiceMonitor::startService()
{
    inService = true;
    initServiceMonitor();
    return inService;
}

bool ServiceMonitor::stopService()
{
    inService = false;
    this->pool.clear();
    return inService;
}

void ServiceMonitor::addServiceItemToPool(const ServiceItem& item)
{
    // 如果不在service，则不添加
    if (!isInService()) {
        return;
    } else {
        auto task = new HttpServiceMonitorTask(item);
        connect(task, &HttpServiceMonitorTask::timeout, this,
            [=](const ServiceItem& taskServieItem) {
                // 任务超时
                auto timer = new QTimer(this);
                timer->setInterval(taskServieItem.getCheckGapTimeInSec() * 1000);
                connect(timer, &QTimer::timeout, this, [=]() {
                    this->addServiceItemToPool(taskServieItem);
                });
                timer->setSingleShot(true);
                timer->start();
                emit this->onLastRequestResult(taskServieItem, INT_MAX);

                dDebug() << taskServieItem.getUrl() << "超时";
            });
        connect(task, &HttpServiceMonitorTask::onHttpRequestCompleted, this,
            [=](QNetworkReply* r, const ServiceItem& taskServiceItem, qint64 elapsed) {
                dDebug() << taskServiceItem.getUrl() << "耗时：" << elapsed
                         << "ms. ";
                emit this->onLastRequestResult(taskServiceItem, elapsed);
                auto timer
                    = new QTimer(this);
                timer->setInterval(taskServiceItem.getCheckGapTimeInSec() * 1000);
                timer->setSingleShot(true);
                connect(timer, &QTimer::timeout, this, [=]() {
                    this->addServiceItemToPool(taskServiceItem);
                });
                timer->start();
                r->deleteLater();
            });
        pool.start(task);
    }
}
