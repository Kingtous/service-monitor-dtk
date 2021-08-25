#ifndef BASESERVICEMONITOR_H
#define BASESERVICEMONITOR_H

#include <QObject>



class BaseServiceMonitor : public QObject
{
    Q_OBJECT
public:
    BaseServiceMonitor();
    virtual ~BaseServiceMonitor();

private:
    virtual void initServiceMonitor();
    // 是否在服务中
    virtual bool isInService();
    virtual bool startService();
    virtual bool stopService();
};

#endif // BASESERVICEMONITOR_H
