#ifndef SERVICEMANAGEPAGE_H
#define SERVICEMANAGEPAGE_H

#include "ui_service_manage.h"

#include <QWidget>

class ServiceManagePage : public QWidget {
  Q_OBJECT
public:
  explicit ServiceManagePage(QWidget *parent = nullptr);

signals:

public slots:
  void onServiceGroupsChanged();
  // 服务
  void handleEditService(QModelIndex index);
  void handleRemoveService(QModelIndex index);
  // 组
  void handleAddService(QModelIndex index);
  void handleDeleteGroup(QModelIndex index);
  void handleRenameGroup(QModelIndex index);

private:
  Ui::ServiceManagePage *ui;
};

#endif // SERVICEMANAGEPAGE_H
