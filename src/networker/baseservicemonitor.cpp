#include "baseservicemonitor.h"

BaseServiceMonitor::BaseServiceMonitor()
{
    this->initServiceMonitor();
}

BaseServiceMonitor::~BaseServiceMonitor()
{

}

void BaseServiceMonitor::initServiceMonitor()
{

}

bool BaseServiceMonitor::isInService()
{
    return false;
}

bool BaseServiceMonitor::startService()
{
    return false;
}

bool BaseServiceMonitor::stopService()
{
    return false;
}
