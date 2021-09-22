#ifndef SERVICEMONITOR_H
#define SERVICEMONITOR_H

#include "baseservicemonitor.h"
#include "servicegroup.h"

#include <QWidget>

class ServiceMonitor : public BaseServiceMonitor
{
public:
    ServiceMonitor();
    ~ServiceMonitor();

private:
    std::shared_ptr<ServiceGroup> group;

    // BaseServiceMonitor interface
public:
    void initServiceMonitor();
    bool isInService();
    bool startService();
    bool stopService();
};

#endif // SERVICEMONITOR_H
