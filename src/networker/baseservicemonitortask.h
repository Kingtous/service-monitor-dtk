#ifndef BASESERVICEMONITORTASK_H
#define BASESERVICEMONITORTASK_H

#include <DObject>
#include <QObject>
#include <QRunnable>
#include <QString>

DCORE_USE_NAMESPACE

class BaseServiceMonitorTask : public QObject
{
  Q_OBJECT
public:
  explicit BaseServiceMonitorTask(QObject* parent = nullptr);
  virtual ~BaseServiceMonitorTask() {}

  // 获取名称
  virtual const QString& getName() = 0;
  // 方法
  virtual const QString& getMethod() = 0;
  // 获取url
  virtual const QString& getUrl() = 0;
  // 获取Body
  virtual const QString& getBody() = 0;
  // 超时时间
  virtual long getTimeOutMs() = 0;

signals:
  void timeout();

private:
};

#endif // BASESERVICEMONITORTASK_H
