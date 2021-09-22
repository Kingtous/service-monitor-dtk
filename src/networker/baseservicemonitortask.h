#ifndef BASESERVICEMONITORTASK_H
#define BASESERVICEMONITORTASK_H

#include <QObject>
#include <QRunnable>
#include <QString>

class BaseServiceMonitorTask : public QObject
{
    Q_OBJECT
public:
    BaseServiceMonitorTask();
    virtual ~BaseServiceMonitorTask() = 0;

    enum Method {
        HTTP,
        HTTPS,
        TCP,
        UDP
    };

    // 运行
    virtual void run() = 0;
    // 获取名称
    virtual const QString& getName()= 0;
    // 方法
    virtual const Method& getMethod()= 0;
    // 获取url
    virtual const QString& getUrl()= 0;
    // 获取Body
    virtual const QString& getBody()= 0;
    // 超时时间
    virtual const long& getTimeOutMs()= 0;

signals:



private:

};

#endif // BASESERVICEMONITORTASK_H
