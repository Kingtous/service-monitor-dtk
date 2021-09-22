#ifndef SERVICEMONITORSETTING_H
#define SERVICEMONITORSETTING_H

#include <DSingleton>
#include <QObject>
#include <QSettings>

class ServiceMonitorSetting
    : public QObject,
      public Dtk::Core::DSingleton<ServiceMonitorSetting> {
  Q_OBJECT
  friend class Dtk::Core::DSingleton<ServiceMonitorSetting>;

public:
  void init();

private:
  ServiceMonitorSetting();
};

#endif // SERVICEMONITORSETTING_H
