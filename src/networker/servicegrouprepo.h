#ifndef SERVICEGROUPREPO_H
#define SERVICEGROUPREPO_H

#include "servicegroup.h"
#include "serviceitem.h"

#include <DSingleton>

#include <QDir>
#include <QObject>

/// 服务DAO
class ServiceGroupRepo : public QObject,
                         public Dtk::Core::DSingleton<ServiceGroupRepo> {
  Q_OBJECT
  friend class DSingleton<ServiceGroupRepo>;

public:
  void init();

  const QList<ServiceGroup> &getServiceGroups();
  void registerGroup(const QString &gname);
  void readServiceGroupsFromJson(const QJsonDocument &doc);
  bool deleteGroup(const QString &gname);
  bool deleteItem(const QString &gname, const QString &itemName);

signals:
  void serviceChanged();

private:
  ServiceGroupRepo();
  void syncWithDisk();
  int findGroup(const QString &gname);

private:
  // items
  QList<ServiceGroup> serviceGroups;
  std::unique_ptr<QDir> configDir;
};

#endif // SERVICEGROUPREPO_H
