#ifndef SERVICEMONITORSETTING_H
#define SERVICEMONITORSETTING_H

#include <DSettings>
#include <DSingleton>
#include <QObject>

DCORE_USE_NAMESPACE

class ServiceMonitorSetting
  : public QObject
  , public Dtk::Core::DSingleton<ServiceMonitorSetting>
{
  Q_OBJECT
  friend class Dtk::Core::DSingleton<ServiceMonitorSetting>;

public:
  void init();

private:
  ServiceMonitorSetting();
};

#endif // SERVICEMONITORSETTING_H
