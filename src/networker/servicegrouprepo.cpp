#include "servicegrouprepo.h"

#include <DFloatingMessage>
#include <DMainWindow>
#include <DStandardPaths>
#include <QDir>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

DWIDGET_USE_NAMESPACE

#define KINGTOUS_SERVICEGROUP_CONFIG_FILENAME "services.json"

extern DMainWindow* window;

void
ServiceGroupRepo::init()
{
  getServiceGroups();
}

QList<ServiceGroup>&
ServiceGroupRepo::getServiceGroups()
{
  if (serviceGroups.length() == 0) {
    if (configDir == nullptr) {
      // 获取一下看看是不是没有读取
      auto path =
        DStandardPaths::writableLocation(QStandardPaths::AppConfigLocation);

      if (path.isEmpty()) {
        auto message = new Dtk::Widget::DFloatingMessage(
          Dtk::Widget::DFloatingMessage::MessageType::ResidentType);
        message->setMessage("无法获取设置目录");
        window->sendMessage(message);
      } else {
#ifdef QT_DEBUG
        auto message = new Dtk::Widget::DFloatingMessage(
          Dtk::Widget::DFloatingMessage::MessageType::TransientType);
        message->setMessage(path);
        window->sendMessage(message);
#endif
      }
      configDir = std::make_unique<QDir>(path);
    }

    if (!configDir->exists()) {
      configDir->mkpath(configDir->path());
    }
    QFile configFile(
      configDir->absoluteFilePath(KINGTOUS_SERVICEGROUP_CONFIG_FILENAME));
    configFile.open(QFile::ReadOnly);
    auto data = configFile.readAll();
    configFile.close();
    auto doc = QJsonDocument::fromJson(data);
    readServiceGroupsFromJson(doc);
  }
  return this->serviceGroups;
}

bool
ServiceGroupRepo::registerGroup(const QString& gname)
{
  ServiceGroup newGroup{ gname };
  auto it = this->serviceGroups.begin();
  while (it != this->serviceGroups.end()) {
    if (it->getGroupName() == gname) {
      return false;
    }
    it++;
  }
  this->serviceGroups.append(newGroup);
  emit serviceChanged();
  syncWithDisk();
  return true;
}

ServiceGroupRepo::ServiceGroupRepo() {}

void
ServiceGroupRepo::syncWithDisk()
{
  QFile configFile(
    configDir->absoluteFilePath(KINGTOUS_SERVICEGROUP_CONFIG_FILENAME));
  if (!configFile.open(QFile::WriteOnly)) {
    qCritical("配置文件无法写入");
    return;
  }
  QJsonObject newObj;
  QJsonArray array;
  foreach (const ServiceGroup& group, serviceGroups) {
    array.push_back(group.toJsonValue());
  }
  newObj["groups"] = array;
  // write newObj to file
  QJsonDocument newDoc(newObj);
  auto bytes = newDoc.toJson();
  configFile.write(bytes);
  configFile.close();
  qInfo("配置文件写入成功");
}

int
ServiceGroupRepo::findGroup(const QString& gname)
{
  int len = this->serviceGroups.length();
  for (int i = 0; i < len; i++) {
    if (serviceGroups[i].getGroupName() == gname) {
      return i;
    }
  }
  return -1;
}

void
ServiceGroupRepo::readServiceGroupsFromJson(const QJsonDocument& doc)
{
  if (doc.isNull()) {
    return;
  }
  if (doc.isObject()) {
    auto obj = doc.object();
    QJsonValue v = obj["groups"];
    if (v.isNull() || v.isObject()) {
      return;
    } else {
      auto arr = v.toArray();
      if (!arr.isEmpty()) {
        foreach (const QJsonValue& group, arr) {
          auto newGroup = ServiceGroup::fromJsonValue(group);
          serviceGroups.append(newGroup);
        }
        emit serviceChanged();
      }
    }
  }
}

bool
ServiceGroupRepo::deleteGroup(const QString& gname)
{
  auto pointer = findGroup(gname);
  if (pointer != -1) {
    serviceGroups.removeAt(pointer);
    // 判断是否为空了，为空先sync Disk
    syncWithDisk();
    emit serviceChanged();
    return true;
  }
  return false;
}

int
ServiceGroupRepo::findItem(const QString& gname, const QString& itemName)
{
  auto pointer = findGroup(gname);
  if (pointer != -1) {
    auto services = serviceGroups[pointer].getServices();
    auto len = services->length();
    for (int i = 0; i < len; i++) {
      auto service = services->at(i);
      if (service.getServiceName() == itemName) {
        return i;
      }
    }
  }
  return -1;
}

bool
ServiceGroupRepo::deleteItem(const QString& gname, const QString& itemName)
{
  auto pointer = findGroup(gname);
  if (pointer != -1) {
    auto services = serviceGroups[pointer].getServices();
    auto len = services->length();
    for (int i = 0; i < len; i++) {
      auto service = services->at(i);
      if (service.getServiceName() == itemName) {
        services->removeAt(i);
        emit serviceChanged();
        syncWithDisk();
        return true;
      }
    }
  }
  return false;
}

bool
ServiceGroupRepo::registerItem(const QString& gname, const ServiceItem& item)
{
  auto pointer = findGroup(gname);
  if (pointer != -1) {
    auto services = serviceGroups[pointer].getServices();
    auto it = services->begin();
    while (it != services->end()) {
      if (it->getServiceName() == item.getServiceName()) {
        return false;
      }
      it++;
    }
    services->append(item);
    emit serviceChanged();
    syncWithDisk();
    return true;
  } else {
    return false;
  }
}

bool
ServiceGroupRepo::updateItem(const QString& gname,
                             const QString& itemName,
                             const ServiceItem& item)
{
  auto pointer = findGroup(gname);
  if (pointer != -1) {
    auto services = serviceGroups[pointer].getServices();
    auto sz = services->length();
    int i = 0;
    for (; i < sz; i++) {
      if (services->at(i).getServiceName() == itemName) {
        break;
      }
    }
    if (i != sz) {
      services->removeAt(i);
      services->insert(i, item);
    } else {
      return false;
    }
    emit serviceChanged();
    syncWithDisk();
    return true;
  }
  return false;
}
