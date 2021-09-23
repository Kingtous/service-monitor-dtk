#ifndef SERVICEGROUP_H
#define SERVICEGROUP_H

#include "serviceitem.h"

#include <QObject>

class ServiceGroup {
public:
  explicit ServiceGroup(const QString &gname);

  QList<ServiceItem> *getServices();
  void setServices(const QList<ServiceItem> &value);

  QString getGroupName() const;
  void setGroupName(const QString &value);

  QJsonValue toJsonValue() const;
  static ServiceGroup fromJsonValue(const QJsonValue v);

private:
  QList<ServiceItem> services{};
  QString groupName;
};

#endif // SERVICEGROUP_H
