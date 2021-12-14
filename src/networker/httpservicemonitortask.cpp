#include "httpservicemonitortask.h"

#include <DLog>
#include <QElapsedTimer>
#include <QMetaType>
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
  const ServiceItem& newServiceItem,
  QObject* parent)
  : BaseServiceMonitorTask(parent)
{
  serviceItem = newServiceItem;
}

void
HttpServiceMonitorTask::run()
{
  manager = new QNetworkAccessManager();
  QEventLoop loop;
  // connect(manager, &QNetworkAccessManager::finished, &loop,
  // &QEventLoop::quit);
  QUrl url{ getUrl() };
  auto req = QNetworkRequest{ url };
  //  if (url.scheme() == "https") {
  //    auto config = QSslConfiguration();
  //    config.setPeerVerifyMode(QSslSocket::VerifyNone);
  //    config.setProtocol(QSsl::TlsV1_2);
  //    req->setSslConfiguration(config);
  //  }
  //  auto schemelist = manager->supportedSchemes();
#if QT_VERSION >= QT_VERSION_CHECK(5,15,0)
  req.setTransferTimeout(int(getTimeOutMs()));
#endif
  // req->setPriority(QNetworkRequest::Priority::HighPriority);
  auto m = getMethod();
  t.start();
  if (m == "GET") {
    dDebug() <<"开始GET请求：" << serviceItem.getUrl();
    auto r = manager->get(req);
    QObject::connect(r, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    //            connect(r, &QNetworkReply::errorOccurred, &loop,
    //            &QEventLoop::quit); connect(r, &QNetworkReply::errorOccurred,
    //            this, [](QNetworkReply::NetworkError e) {
    //                dDebug() << "error" << e;
    //            });
#if QT_VERSION < QT_VERSION_CHECK(5,15,0)
    QTimer timer;
    timer.setSingleShot(true);
    connect(&timer,&QTimer::timeout,r,&QNetworkReply::abort);
    timer.start(int(getTimeOutMs()));
#endif
    loop.exec();
    if (r->error() == QNetworkReply::NetworkError::NoError) {
      auto elapsed = this->t.elapsed();
      emit this->onHttpRequestCompleted(this->serviceItem, elapsed);
    } else if (r->error() == QNetworkReply::NetworkError::TimeoutError ||
               r->error() ==
                 QNetworkReply::NetworkError::OperationCanceledError) {
      emit this->timeout(this->serviceItem);
    } else {
      emit this->error(r->errorString());
    }
    r->deleteLater();
  } else if (m == "POST") {
      dDebug() <<"开始POST请求：" << serviceItem.getUrl();
    QByteArray bytes;
    bytes.append(getBody().toUtf8());
    //    req.setHeader(req.ContentTypeHeader, "text/plain");
    auto r = manager->post(req, bytes);
    QObject::connect(r, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();
    if (r->error() == QNetworkReply::NetworkError::NoError) {
      auto elapsed = this->t.elapsed();
      emit this->onHttpRequestCompleted(this->serviceItem, elapsed);
    } else if (r->error() == QNetworkReply::NetworkError::TimeoutError ||
               r->error() ==
                 QNetworkReply::NetworkError::OperationCanceledError) {
      emit this->timeout(this->serviceItem);
    } else {
      emit this->error(r->errorString());
    }
    r->deleteLater();
  }
  manager->deleteLater();
  this->deleteLater();
  dDebug() << "request " << getUrl() << "ended.";
}

const QString&
HttpServiceMonitorTask::getName()
{
  return this->serviceItem.getServiceName();
}

const QString&
HttpServiceMonitorTask::getMethod()
{
  return this->serviceItem.getMethod();
}

const QString&
HttpServiceMonitorTask::getUrl()
{
  return this->serviceItem.getUrl();
}

const QString&
HttpServiceMonitorTask::getBody()
{
  return this->serviceItem.getBody();
}

long
HttpServiceMonitorTask::getTimeOutMs()
{
  return this->serviceItem.getTimeOut() * 1000;
}

} // namespace http
} // namespace networker
