#ifndef HTTPSERVICEMONITORTASK_H
#define HTTPSERVICEMONITORTASK_H

#include "baseservicemonitortask.h"

#include "serviceitem.h"

namespace networker {
namespace http {
class HttpServiceMonitorTask : protected BaseServiceMonitorTask
{
public:
    HttpServiceMonitorTask();
    // 设置服务item
    void setServiceItem(ServiceItem *newServiceItem);
    // 获取服务返回数据
    QString *getRes() const;

signals:
    // http请求完成信号
    int onHttpRequestCompleted();

private:
    ServiceItem *serviceItem;
    // 服务端返回数据
    QString * res;
};
}
}

#endif // HTTPSERVICEMONITORTASK_H
