#ifndef HTTPSERVICEMONITORTASK_H
#define HTTPSERVICEMONITORTASK_H

#include <QElapsedTimer>
#include <QNetworkReply>

#include "baseservicemonitortask.h"

#include "serviceitem.h"

class QNetworkAccessManager;
class QElapsedTimer;

namespace networker {
namespace http {
class HttpServiceMonitorTask : public BaseServiceMonitorTask, public QRunnable {
  Q_OBJECT
public:
  HttpServiceMonitorTask(const ServiceItem &newServiceItem,
                         QObject *parent = nullptr);

signals:
  // http请求完成信号
  void onHttpRequestCompleted(const ServiceItem &item, qint64 elasped);
  void timeout(const ServiceItem &item);
  void error(QString e);

private:
  ServiceItem serviceItem{};
  // 服务端返回数据
  QNetworkAccessManager *manager;
  QElapsedTimer t{};

public:
  void run();
  const QString &getName();
  const QString &getMethod();
  const QString &getUrl();
  const QString &getBody();
  long getTimeOutMs();
};
} // namespace http
} // namespace networker

#endif // HTTPSERVICEMONITORTASK_H
