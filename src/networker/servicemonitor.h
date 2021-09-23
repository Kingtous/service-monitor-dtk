#ifndef SERVICEMONITOR_H
#define SERVICEMONITOR_H
#include <DThreadUtils>
#include <QThreadPool>

#include "baseservicemonitor.h"
#include "servicegroup.h"

#include <DSingleton>
#include <QWidget>

DCORE_USE_NAMESPACE

class ServiceMonitor : public BaseServiceMonitor,
                       public DSingleton<ServiceMonitor> {
    Q_OBJECT
    friend class DSingleton<ServiceMonitor>;

public:
    ServiceMonitor();
    ~ServiceMonitor();

private:
    volatile bool inService { false };

    // BaseServiceMonitor interface
public:
    void initServiceMonitor();
    bool isInService();
    bool startService();
    bool stopService();

signals:
    void onLastRequestResult(const ServiceItem& item, const qint64 latency);

private:
    // 线程池控制
    QThreadPool pool {};
    // 添加服务到线程池
    void addServiceItemToPool(const ServiceItem& item);
};

#endif // SERVICEMONITOR_H
