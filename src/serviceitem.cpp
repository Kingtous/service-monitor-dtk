#include "serviceitem.h"

#include <QJsonObject>

ServiceItem::ServiceItem() {}

QString ServiceItem::getServiceName() const { return serviceName; }

void ServiceItem::setServiceName(const QString &value) { serviceName = value; }

QString ServiceItem::getMethod() const { return method; }

void ServiceItem::setMethod(const QString &value) { method = value; }

QString ServiceItem::getUrl() const { return url; }

void ServiceItem::setUrl(const QString &value) { url = value; }

QString ServiceItem::getBody() const { return body; }

void ServiceItem::setBody(const QString &value) { body = value; }

int ServiceItem::getCheckGapTimeInSec() const { return checkGapTimeInSec; }

void ServiceItem::setCheckGapTimeInSec(int value) { checkGapTimeInSec = value; }

int ServiceItem::getTimeOut() const { return timeOut; }

void ServiceItem::setTimeOut(int value) { timeOut = value; }

QJsonValue ServiceItem::toJsonValue() const {
  QJsonObject obj;
  obj["serviceName"] = getServiceName();
  obj["method"] = getMethod();
  obj["url"] = getUrl();
  obj["body"] = getBody();
  obj["checkGapTimeInSec"] = getCheckGapTimeInSec();
  obj["timeOut"] = getTimeOut();
  return obj;
}

ServiceItem ServiceItem::fromJsonValue(const QJsonValue obj) {
  ServiceItem item;
  item.setServiceName(obj["serviceName"].toString());
  item.setMethod(obj["method"].toString());
  item.setUrl(obj["url"].toString());
  item.setBody(obj["body"].toString());
  item.setCheckGapTimeInSec(obj["checkGapTimeInSec"].toInt());
  item.setTimeOut(obj["timeOut"].toInt());
  return item;
}
