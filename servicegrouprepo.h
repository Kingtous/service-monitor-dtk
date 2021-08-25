#ifndef SERVICEGROUPREPO_H
#define SERVICEGROUPREPO_H

#include "servicegroup.h"
#include "serviceitem.h"

#include <DSingleton>

#include <QObject>

/// 服务DAO
class ServiceGroupRepo : public QObject,
                         public Dtk::Core::DSingleton<ServiceGroupRepo> {
  Q_OBJECT
  friend class DSingleton<ServiceGroupRepo>;

public:
  const QList<ServiceGroup> &getServiceGroups();

private:
  ServiceGroupRepo();
  // items
  QList<ServiceGroup> serviceGroups;
};

#endif // SERVICEGROUPREPO_H
