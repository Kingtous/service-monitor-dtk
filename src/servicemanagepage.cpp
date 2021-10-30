#include "servicemanagepage.h"
#include "addservicedialog.h"

#include <DDialog>
#include <DLog>
#include <DMenu>
#include <DStandardItem>
#include <DTreeView>

#include <networker/servicegrouprepo.h>
#include <networker/serviceitem.h>
#include <networker/servicemonitor.h>

ServiceManagePage::ServiceManagePage(DWidget* parent)
  : DWidget(parent)
{
  ui = new Ui::ServiceManagePage;
  ui->setupUi(this);
  this->onServiceGroupsChanged();
  ui->treeView->setContextMenuPolicy(Qt::ContextMenuPolicy::CustomContextMenu);

  connect(
    ServiceMonitor::instance(), &ServiceMonitor::onStartService, this, [=]() {
      // 开始服务，不允许修改了
      ui->treeView->setDisabled(true);
    });

  connect(
    ServiceMonitor::instance(), &ServiceMonitor::onStopService, this, [=]() {
      // 结束服务
      ui->treeView->setDisabled(false);
    });

  connect(
    ui->treeView,
    &DTreeView::customContextMenuRequested,
    this,
    [=](const QPoint& p) {
      auto index = ui->treeView->indexAt(p);
      auto data = index.data();
      if (!data.isValid()) {
        return;
      }
      if (index.parent() == QModelIndex()) {
        auto menu = new Dtk::Widget::DMenu();
        menu
          ->addAction(
            "添加监控服务", this, [=]() { this->handleAddService(index); })
          ->setIcon(QIcon(":/images/icon.svg"));
        //        menu->addAction("重命名组", [=]() {
        //        this->handleRenameGroup(index); })
        //          ->setIcon(QIcon(":/images/eye.svg"));
        menu->addAction("删除该组", [=]() { this->handleDeleteGroup(index); })
          ->setIcon(QIcon(":/images/delete.svg"));
        menu->popup(ui->treeView->viewport()->mapToGlobal(p));
      } else if (index.parent() != QModelIndex()) {
        auto menu = new Dtk::Widget::DMenu();
        menu
          ->addAction(
            "编辑服务", this, [=]() { this->handleEditService(index); })
          ->setIcon(QIcon(":/images/icon.svg"));
        menu->addAction("删除服务", [=]() { this->handleRemoveService(index); })
          ->setIcon(QIcon(":/images/delete.svg"));
        menu->popup(ui->treeView->viewport()->mapToGlobal(p));
      }
    });
}

void
ServiceManagePage::onServiceGroupsChanged()
{
  // 获取service
  auto serviceGroups = ServiceGroupRepo::instance()->getServiceGroups();
  auto icon = QIcon(":/images/eye.svg");

  auto serviceViewRoot = new QStandardItemModel(this);
  serviceViewRoot->setHorizontalHeaderLabels({ "监控组", "方法", "URL" });

  auto serviceGroupIt = serviceGroups.begin();
  while (serviceGroupIt != serviceGroups.end()) {
    auto group = *serviceGroupIt;
    auto serviceGroupNode = new Dtk::Widget::DStandardItem();
    serviceGroupNode->setText(group.getGroupName());
    serviceGroupNode->setIcon(icon);
    serviceGroupNode->setEditable(false);
    serviceGroupNode->setData(group.getGroupName(), Qt::EditRole);
    foreach (const ServiceItem& item, *group.getServices()) {
      auto serviceNode = new Dtk::Widget::DStandardItem();
      serviceNode->setText(item.getServiceName());
      serviceNode->setIcon(icon);
      serviceNode->setEditable(false);
      serviceNode->setData(item.getServiceName(), Qt::EditRole);
      auto method = new Dtk::Widget::DStandardItem();
      method->setText(item.getMethod());
      method->setEditable(false);
      method->setData(item.getMethod(), Qt::EditRole);
      auto url = new Dtk::Widget::DStandardItem();
      url->setText(item.getUrl());
      url->setEditable(false);
      url->setData(item.getUrl(), Qt::EditRole);
      serviceGroupNode->appendRow({ serviceNode, method, url });
    }
    serviceViewRoot->appendRow(serviceGroupNode);
    serviceGroupIt++;
  }

  ui->treeView->setModel(serviceViewRoot);
  ui->treeView->expandAll();
}

void
ServiceManagePage::handleAddService(QModelIndex index)
{
  auto dialog = new AddServiceDialog(this);
  dialog->addButton("取消", false, Dtk::Widget::DDialog::ButtonNormal);
  dialog->addButton(
    "确定", true, Dtk::Widget::DDialog::ButtonType::ButtonRecommend);
  connect(dialog,
          &AddServiceDialog::onServiceConfirm,
          this,
          [&, dialog](const ServiceItem& item) {
            // item
            const auto groupName = index.data(Qt::EditRole).toString();
            if (ServiceGroupRepo::instance()->registerItem(groupName, item)) {
              dialog->close();
            } else {
              DDialog dialog{ "提示", "含有重名的记录，请更换名称" };
              dialog.addButton("确定", true);
              dialog.exec();
            }
          });
  dialog->exec();
}

void
ServiceManagePage::handleEditService(const QModelIndex& index)
{
  auto serviceName = index.data(Qt::EditRole).toString();
  auto gname = index.parent().data(Qt::EditRole).toString();
  int gid = ServiceGroupRepo::instance()->findGroup(gname);
  int sid = ServiceGroupRepo::instance()->findItem(gname, serviceName);
  if (gid == -1 || sid == -1) {
    return;
  }
  auto originItem =
    ServiceGroupRepo::instance()->getServiceGroups()[gid].getServices()->at(
      sid);
  auto dialog = new AddServiceDialog(originItem, this);
  dialog->addButton("取消", false, Dtk::Widget::DDialog::ButtonNormal);
  dialog->addButton(
    "确定", true, Dtk::Widget::DDialog::ButtonType::ButtonRecommend);
  connect(
    dialog,
    &AddServiceDialog::onServiceConfirm,
    this,
    [&, serviceName, gname, dialog](const ServiceItem& item) {
      // item
      if (ServiceGroupRepo::instance()->updateItem(gname, serviceName, item)) {
        dialog->close();
      } else {
        DDialog dialog{ "提示", "更新失败，未找到记录" };
        dialog.addButton("确定", true);
        dialog.exec();
      }
    });
  dialog->exec();
}

void
ServiceManagePage::handleRemoveService(const QModelIndex& index)
{
  auto serviceName = index.data(Qt::EditRole).toString();
  auto gname = index.parent().data(Qt::EditRole).toString();
  auto dialog = new Dtk::Widget::DDialog(this);
  dialog->setTitle("提示");
  dialog->setMessage("确定要删除 " + serviceName + " 服务吗？");
  dialog->addButton("取消", false, Dtk::Widget::DDialog::ButtonRecommend);
  dialog->addButton("确定", true, Dtk::Widget::DDialog::ButtonWarning);
  connect(dialog, &Dtk::Widget::DDialog::accepted, this, [=]() {
    ServiceGroupRepo::instance()->deleteItem(gname, serviceName);
  });
  dialog->exec();
}

void
ServiceManagePage::handleDeleteGroup(QModelIndex index)
{
  auto dialog = new Dtk::Widget::DDialog(this);
  auto data = index.data(Qt::EditRole);
  dialog->setTitle("提示");
  dialog->setMessage("确定要删除" + data.toString() + "组吗？");
  dialog->addButton("确定", true, Dtk::Widget::DDialog::ButtonWarning);
  dialog->addButton("取消", false, Dtk::Widget::DDialog::ButtonRecommend);
  connect(dialog,
          &Dtk::Widget::DDialog::buttonClicked,
          this,
          [=](int index, const QString& text) {
            if (index == 0) {
              ServiceGroupRepo::instance()->deleteGroup(data.toString());
            }
          });
  dialog->exec();
}

void
ServiceManagePage::handleRenameGroup(QModelIndex index)
{}
