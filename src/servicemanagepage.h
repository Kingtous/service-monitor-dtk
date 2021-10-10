#ifndef SERVICEMANAGEPAGE_H
#define SERVICEMANAGEPAGE_H

#include "ui_service_manage.h"

#include <DWidget>

DWIDGET_USE_NAMESPACE

class ServiceManagePage : public DWidget
{
  Q_OBJECT
public:
  explicit ServiceManagePage(DWidget* parent = nullptr);

signals:

public slots:
  void onServiceGroupsChanged();
  // 服务
  void handleEditService(const QModelIndex& index);
  void handleRemoveService(const QModelIndex& index);
  // 组
  void handleAddService(QModelIndex index);
  void handleDeleteGroup(QModelIndex index);
  void handleRenameGroup(QModelIndex index);

private:
  Ui::ServiceManagePage* ui;
};

#endif // SERVICEMANAGEPAGE_H
