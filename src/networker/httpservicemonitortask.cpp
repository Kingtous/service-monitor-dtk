#include "httpservicemonitortask.h"

namespace networker {
namespace http {
HttpServiceMonitorTask::HttpServiceMonitorTask()
{

}
void HttpServiceMonitorTask::setServiceItem(ServiceItem *newServiceItem)
{
    serviceItem = newServiceItem;
}

QString *HttpServiceMonitorTask::getRes() const
{
    return res;
}

}
}
