#include "httpservicemonitortask.h"

#include <DLog>
#include <QElapsedTimer>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QSslConfiguration>
#include <QThread>

DCORE_USE_NAMESPACE

namespace networker {
namespace http {
    HttpServiceMonitorTask::HttpServiceMonitorTask(
        const ServiceItem& newServiceItem, QObject* parent)
        : BaseServiceMonitorTask(parent)
    {
        serviceItem = newServiceItem;
    }

    QNetworkReply* HttpServiceMonitorTask::getRes() const { return res; }

    void HttpServiceMonitorTask::run()
    {
        manager = new QNetworkAccessManager();
        connect(
            manager, &QNetworkAccessManager::finished, this, [=](QNetworkReply* r) {
                if (r->error() == QNetworkReply::NetworkError::NoError) {
                    auto elapsed = t.elapsed();
                    emit this->onHttpRequestCompleted(r, this->serviceItem, elapsed);
                } else if (r->error() == QNetworkReply::NetworkError::TimeoutError) {
                    emit this->timeout(this->serviceItem);
                }
                res = r;
            });
        QUrl url { getUrl() };
        auto req = new QNetworkRequest { url };
        QEventLoop loop;
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
            auto reply = manager->get(*req);
            connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
            //            connect(reply, &QNetworkReply::errorOccurred, this, [](QNetworkReply::NetworkError err) {
            //                dWarning() << "error" << err;
            //            });
            loop.exec();
        } else if (m == "POST") {
            auto bytes = new QByteArray;
            bytes->append(getBody().toUtf8());
            manager->post(*req, *bytes);
            loop.exec();
        }
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
