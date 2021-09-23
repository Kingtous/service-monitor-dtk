#include "httpservicemonitortask.h"

#include <DLog>
#include <QElapsedTimer>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QSslConfiguration>
#include <QThread>
#include <networker/servicemonitor.h>

DCORE_USE_NAMESPACE

namespace networker {
namespace http {
    HttpServiceMonitorTask::HttpServiceMonitorTask(
        const ServiceItem& newServiceItem, QObject* parent)
        : BaseServiceMonitorTask(parent)
    {
        serviceItem = newServiceItem;
    }

    void HttpServiceMonitorTask::run()
    {
        manager = new QNetworkAccessManager();
        auto loop = new QEventLoop();
        // connect(manager, &QNetworkAccessManager::finished, &loop, &QEventLoop::quit);
        QUrl url { getUrl() };
        auto req = new QNetworkRequest { url };
        //  if (url.scheme() == "https") {
        //    auto config = QSslConfiguration();
        //    config.setPeerVerifyMode(QSslSocket::VerifyNone);
        //    config.setProtocol(QSsl::TlsV1_2);
        //    req->setSslConfiguration(config);
        //  }
        //  auto schemelist = manager->supportedSchemes();
        req->setTransferTimeout(int(getTimeOutMs()));
        // req->setPriority(QNetworkRequest::Priority::HighPriority);
        auto m = getMethod();
        t.start();
        if (m == "GET") {
            auto r = manager->get(*req);
            connect(r, &QNetworkReply::finished, loop, &QEventLoop::quit);
            connect(r, &QNetworkReply::finished, ServiceMonitor::instance(), [=]() {
                if (r->error() == QNetworkReply::NetworkError::NoError) {
                    auto elapsed = this->t.elapsed();
                    emit this->onHttpRequestCompleted(this->serviceItem, elapsed);
                } else if (r->error() == QNetworkReply::NetworkError::TimeoutError) {
                    emit this->timeout(this->serviceItem);
                } else {
                    emit this->error(r->error());
                }
                r->deleteLater();
            });
            //            connect(r, &QNetworkReply::errorOccurred, &loop, &QEventLoop::quit);
            //            connect(r, &QNetworkReply::errorOccurred, this, [](QNetworkReply::NetworkError e) {
            //                dDebug() << "error" << e;
            //            });
            loop->exec();
        } else if (m == "POST") {
            auto bytes = new QByteArray;
            bytes->append(getBody().toUtf8());
            manager->post(*req, *bytes);
            loop->exec();
            free(bytes);
        }
        //free(loop);
        //free(manager);
        manager->deleteLater();
        //free(req)
        //        loop.exec();
        // dDebug() << "request " << getUrl() << "ended.";
    }

    const QString& HttpServiceMonitorTask::getName()
    {
        return this->serviceItem.getServiceName();
    }

    const QString& HttpServiceMonitorTask::getMethod()
    {
        return this->serviceItem.getMethod();
    }

    const QString& HttpServiceMonitorTask::getUrl()
    {
        return this->serviceItem.getUrl();
    }

    const QString& HttpServiceMonitorTask::getBody()
    {
        return this->serviceItem.getBody();
    }

    long HttpServiceMonitorTask::getTimeOutMs()
    {
        return this->serviceItem.getTimeOut() * 1000;
    }

} // namespace http
} // namespace networker
