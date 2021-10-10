#include "servicemonitor.h"
#include "httpservicemonitortask.h"
#include "servicegrouprepo.h"

#include <DLog>
#include <QNetworkReply>
#include <QTimer>

using namespace networker::http;

ServiceMonitor::ServiceMonitor() {}

ServiceMonitor::~ServiceMonitor() {}

void
ServiceMonitor::initServiceMonitor()
{
  dDebug() << "system ideal thread counts: " << QThread::idealThreadCount();
  pool.setMaxThreadCount(QThread::idealThreadCount());
  pool.setExpiryTimeout(30 * 1000); // 30s 任务过期
  auto groups = ServiceGroupRepo::instance()->getServiceGroups();
  auto it = groups.begin();
  while (it != groups.end()) {
    auto group = *it;
    auto services = it->getServices();
    auto sit = services->begin();
    while (sit != services->end()) {
      auto service = *sit;
      this->addServiceItemToPool(group, service);
      sit++;
    }
    it++;
  }
}

bool
ServiceMonitor::isInService()
{
  return inService;
}

bool
ServiceMonitor::startService()
{
  inService = true;
  initServiceMonitor();
  emit this->onStartService();
  return inService;
}

bool
ServiceMonitor::stopService()
{
  inService = false;
  this->pool.clear();
  emit this->onStopService();
  return inService;
}

void
ServiceMonitor::addServiceItemToPool(const ServiceGroup& group,
                                     const ServiceItem& item)
{
  // 如果不在service，则不添加
  if (!isInService()) {
    return;
  } else {
    auto task = new HttpServiceMonitorTask(item, this);
    // 程序控制删除
    task->setAutoDelete(false);
    connect(task,
            &HttpServiceMonitorTask::timeout,
            this,
            [=](const ServiceItem& taskServieItem) {
              // 任务超时
              auto timer = new QTimer(this);
              timer->setInterval(taskServieItem.getCheckGapTimeInSec() * 1000);
              connect(timer, &QTimer::timeout, this, [=]() {
                this->addServiceItemToPool(group, taskServieItem);
              });
              timer->setSingleShot(true);
              timer->start();
              emit this->onLastRequestResult(group, taskServieItem, INT_MAX);

              dDebug() << item.getMethod() << ":" << taskServieItem.getUrl()
                       << "超时";
            });
    connect(task, &HttpServiceMonitorTask::error, this, [=](QString e) {
      // 任务超时
      auto timer = new QTimer(this);
      timer->setInterval(item.getCheckGapTimeInSec() * 1000);
      connect(timer, &QTimer::timeout, this, [=]() {
        this->addServiceItemToPool(group, item);
      });
      timer->setSingleShot(true);
      timer->start();
      emit this->onLastRequestResult(group, item, INT_MAX);

      dDebug() << item.getMethod() << ":" << item.getUrl() << ":" << e
               << "错误";
    });

    connect(task,
            &HttpServiceMonitorTask::onHttpRequestCompleted,
            this,
            [=](const ServiceItem& taskServiceItem, qint64 elapsed) {
              dDebug() << item.getMethod() << taskServiceItem.getUrl()
                       << "耗时：" << elapsed << "ms. ";
              emit this->onLastRequestResult(group, taskServiceItem, elapsed);
              auto timer = new QTimer(this);
              timer->setInterval(taskServiceItem.getCheckGapTimeInSec() * 1000);
              timer->setSingleShot(true);
              connect(timer, &QTimer::timeout, this, [=]() {
                this->addServiceItemToPool(group, taskServiceItem);
              });
              timer->start();
            });
    pool.start(task);
  }
}
