#include "servicegroup.h"

#include <QJsonObject>

ServiceGroup::ServiceGroup(const QString &gname) { groupName = gname; }

QList<ServiceItem> ServiceGroup::getServices() const { return services; }

void ServiceGroup::setServices(const QList<ServiceItem> &value) {
  services = value;
}

QString ServiceGroup::getGroupName() const { return groupName; }

void ServiceGroup::setGroupName(const QString &value) { groupName = value; }

QJsonValue ServiceGroup::toJsonValue() const {
  QJsonObject obj;
  obj["groupName"] = getGroupName();
  QJsonArray serviceObjs;
  foreach (const ServiceItem &service, services) {
    serviceObjs.push_back(service.toJsonValue());
  }
  obj["services"] = serviceObjs;
  return obj;
}

ServiceGroup ServiceGroup::fromJsonValue(const QJsonValue v) {
  auto obj = v.toObject();
  ServiceGroup group{obj["groupName"].toString("解析失败")};
  QList<ServiceItem> services;
  auto arrs = obj["services"];
  if (!arrs.isArray()) {
    return group;
  }
  foreach (const QJsonValue &v, arrs.toArray()) {
    auto item = ServiceItem::fromJsonValue(v);
    services.append(item);
  }
  group.setServices(services);
  return group;
}
