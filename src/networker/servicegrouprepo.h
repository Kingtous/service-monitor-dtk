#ifndef SERVICEGROUPREPO_H
#define SERVICEGROUPREPO_H

#include "servicegroup.h"
#include "serviceitem.h"

#include <DSingleton>

#include <QDir>
#include <QObject>

/// 服务DAO
class ServiceGroupRepo
  : public QObject
  , public Dtk::Core::DSingleton<ServiceGroupRepo>
{
  Q_OBJECT
  friend class DSingleton<ServiceGroupRepo>;

public:
  void init();

  QList<ServiceGroup>& getServiceGroups();
  bool registerGroup(const QString& gname);
  void readServiceGroupsFromJson(const QJsonDocument& doc);
  bool deleteGroup(const QString& gname);

  int findItem(const QString& gname, const QString& itemName);
  bool deleteItem(const QString& gname, const QString& itemName);
  bool registerItem(const QString& gname, const ServiceItem& item);
  bool updateItem(const QString& gname,
                  const QString& itemName,
                  const ServiceItem& item);

  int findGroup(const QString& gname);

  QString urlRegex{
    "https?://[-A-Za-z0-9+&@#/%?=~_|!:,.;]+[-A-Za-z0-9+&@#/%=~_|]"
  };

signals:
  void serviceChanged();

private:
  ServiceGroupRepo();
  void syncWithDisk();

private:
  // items
  QList<ServiceGroup> serviceGroups;
  std::unique_ptr<QDir> configDir;
};

#endif // SERVICEGROUPREPO_H
