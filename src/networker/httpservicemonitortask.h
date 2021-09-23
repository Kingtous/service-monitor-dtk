#ifndef HTTPSERVICEMONITORTASK_H
#define HTTPSERVICEMONITORTASK_H

#include <QElapsedTimer>

#include "baseservicemonitortask.h"

#include "serviceitem.h"

class QNetworkAccessManager;
class QNetworkReply;
class QElapsedTimer;

namespace networker {
namespace http {
    class HttpServiceMonitorTask : public BaseServiceMonitorTask, public QRunnable {
        Q_OBJECT
    public:
        HttpServiceMonitorTask(const ServiceItem& newServiceItem,
            QObject* parent = nullptr);
        // 获取服务返回数据
        QNetworkReply* getRes() const;

    signals:
        // http请求完成信号
        void onHttpRequestCompleted(QNetworkReply* rep, const ServiceItem& item,
            qint64 elasped);
        void timeout(const ServiceItem& item);

    private:
        ServiceItem serviceItem {};
        // 服务端返回数据
        QNetworkReply* res;
        QNetworkAccessManager* manager;
        QElapsedTimer t {};

    public:
        void run();
        const QString& getName();
        const QString& getMethod();
        const QString& getUrl();
        const QString& getBody();
        long getTimeOutMs();
    };
} // namespace http
} // namespace networker

#endif // HTTPSERVICEMONITORTASK_H
