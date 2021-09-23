#ifndef SERVICEITEM_H
#define SERVICEITEM_H

#include "baseservicemonitortask.h"

#include <QJsonArray>
#include <QJsonDocument>
#include <QString>

/// 服务定义
/// TODO 增加header设置
class ServiceItem {
public:
  ServiceItem();

  const QString &getServiceName() const;
  void setServiceName(const QString &value);

  const QString &getMethod() const;
  void setMethod(const QString &value);

  const QString &getUrl() const;
  void setUrl(const QString &value);

  const QString &getBody() const;
  void setBody(const QString &value);

  int getCheckGapTimeInSec() const;
  void setCheckGapTimeInSec(int value);

  int getTimeOut() const;
  void setTimeOut(int value);

  QJsonValue toJsonValue() const;
  static ServiceItem fromJsonValue(const QJsonValue v);

private:
  QString serviceName{""};
  QString method{"GET"};
  QString url{""};
  QString body{""};
  int checkGapTimeInSec{300}; // 默认5分钟
  int timeOut{5};             // 默认5秒
};

#endif // SERVICEITEM_H
