#include "servicemanagepage.h"
#include "addservicedialog.h"

#include <DDialog>
#include <DLog>
#include <DMenu>
#include <DStandardItem>

#include <networker/servicegrouprepo.h>
#include <networker/serviceitem.h>

ServiceManagePage::ServiceManagePage(QWidget *parent) : QWidget(parent) {
  ui = new Ui::ServiceManagePage;
  ui->setupUi(this);
  this->onServiceGroupsChanged();
  ui->treeView->setContextMenuPolicy(Qt::ContextMenuPolicy::CustomContextMenu);
  connect(
      ui->treeView, &QTreeView::customContextMenuRequested, this,
      [=](const QPoint &p) {
        auto index = ui->treeView->indexAt(p);
        auto data = index.data();
        if (index.parent() == QModelIndex()) {
          auto menu = new Dtk::Widget::DMenu();
          menu->addAction("添加监控服务", this,
                          [=]() { this->handleAddService(index); })
              ->setIcon(QIcon(":/images/icon.svg"));
          menu->addAction("重命名组", [=]() { this->handleRenameGroup(index); })
              ->setIcon(QIcon(":/images/eye.svg"));
          menu->addAction("删除该组", [=]() { this->handleDeleteGroup(index); })
              ->setIcon(QIcon(":/images/delete.svg"));
          menu->popup(ui->treeView->viewport()->mapToGlobal(p));
        } else if (index.parent() != QModelIndex()) {
          auto menu = new Dtk::Widget::DMenu();
          menu->addAction("编辑服务", this,
                          [=]() { this->handleEditService(index); })
              ->setIcon(QIcon(":/images/icon.svg"));
          menu->addAction("删除服务",
                          [=]() { this->handleRemoveService(index); })
              ->setIcon(QIcon(":/images/delete.svg"));
          menu->popup(ui->treeView->viewport()->mapToGlobal(p));
        }
      });
}

void ServiceManagePage::onServiceGroupsChanged() {
  // 获取service
  auto serviceGroups = ServiceGroupRepo::instance()->getServiceGroups();
  auto icon = QIcon(":/images/eye.svg");

  auto serviceViewRoot = new QStandardItemModel(this);
  serviceViewRoot->setHorizontalHeaderLabels({"监控组", "方法", "URL"});

  auto serviceGroupIt = serviceGroups.begin();
  while (serviceGroupIt != serviceGroups.end()) {
    auto group = *serviceGroupIt;
    auto serviceGroupNode = new Dtk::Widget::DStandardItem();
    serviceGroupNode->setText(group.getGroupName());
    serviceGroupNode->setIcon(icon);
    serviceGroupNode->setEditable(false);
    serviceGroupNode->setData(group.getGroupName(), Qt::EditRole);
    foreach (const ServiceItem &item, *group.getServices()) {
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
      serviceGroupNode->appendRow({serviceNode, method, url});
    }
    serviceViewRoot->appendRow(serviceGroupNode);
    serviceGroupIt++;
  }

  ui->treeView->setModel(serviceViewRoot);
  ui->treeView->expandAll();
}

void ServiceManagePage::handleAddService(QModelIndex index) {
  auto dialog = new AddServiceDialog(this);
  dialog->addButton("取消", false, Dtk::Widget::DDialog::ButtonNormal);
  dialog->addButton("确定", true,
                    Dtk::Widget::DDialog::ButtonType::ButtonRecommend);
  connect(dialog, &AddServiceDialog::onServiceConfirm, this,
          [&](const ServiceItem &item) {
            // item
            const auto groupName = index.data(Qt::EditRole).toString();
            ServiceGroupRepo::instance()->registerItem(groupName, item);
          });
  dialog->exec();
}

void ServiceManagePage::handleEditService(const QModelIndex &index) {}

void ServiceManagePage::handleRemoveService(const QModelIndex &index) {
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

void ServiceManagePage::handleDeleteGroup(QModelIndex index) {
  auto dialog = new Dtk::Widget::DDialog(this);
  auto data = index.data(Qt::EditRole);
  dialog->setTitle("提示");
  dialog->setMessage("确定要删除" + data.toString() + "组吗？");
  dialog->addButton("确定", true, Dtk::Widget::DDialog::ButtonWarning);
  dialog->addButton("取消", false, Dtk::Widget::DDialog::ButtonRecommend);
  connect(dialog, &Dtk::Widget::DDialog::buttonClicked, this,
          [=](int index, const QString &text) {
            if (index == 0) {
              ServiceGroupRepo::instance()->deleteGroup(data.toString());
            }
          });
  dialog->exec();
}

void ServiceManagePage::handleRenameGroup(QModelIndex index) {}