#include "servicemanagepage.h"
#include "addservicedialog.h"
#include "servicegrouprepo.h"

#include <DDialog>
#include <DLog>
#include <DMenu>
#include <DStandardItem>

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
        if (data.userType() == QMetaType::QString) {
          auto menu = new Dtk::Widget::DMenu();
          menu->addAction("添加监控服务", this,
                          [=]() { this->handleAddService(index); })
              ->setIcon(QIcon(":/images/icon.svg"));
          menu->addAction("重命名组", [=]() { this->handleRenameGroup(index); })
              ->setIcon(QIcon(":/images/eye.svg"));
          menu->addAction("删除该组", [=]() { this->handleDeleteGroup(index); })
              ->setIcon(QIcon(":/images/delete.svg"));
          menu->popup(ui->treeView->viewport()->mapToGlobal(p));
        } else if (data.userType() == QMetaType::QJsonValue) {
          auto menu = new Dtk::Widget::DMenu();
          menu->addAction("编辑服务", this,
                          [=, &index]() { this->handleEditService(index); })
              ->setIcon(QIcon(":/images/icon.svg"));
          menu->addAction("删除服务",
                          [=, &index]() { this->handleRemoveService(index); })
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

  foreach (const ServiceGroup &group, serviceGroups) {
    auto serviceGroupNode = new Dtk::Widget::DStandardItem();
    serviceGroupNode->setText(group.getGroupName());
    serviceGroupNode->setIcon(icon);
    serviceGroupNode->setEditable(false);
    serviceGroupNode->setData(group.getGroupName(), Qt::EditRole);
    foreach (const ServiceItem &item, group.getServices()) {
      auto serviceNode = new Dtk::Widget::DStandardItem();
      serviceNode->setText(item.getServiceName());
      serviceNode->setIcon(icon);
      serviceGroupNode->appendRow(serviceNode);
      serviceNode->setEditable(false);
      serviceNode->setData(item.toJsonValue(), Qt::EditRole);
    }
    serviceViewRoot->appendRow(serviceGroupNode);
  }
  ui->treeView->setModel(serviceViewRoot);
}

void ServiceManagePage::handleAddService(QModelIndex index) {
  auto dialog = new Dtk::Widget::DDialog(this);
  dialog->setTitle("添加服务");
  dialog->setMessage("请在下方注册你的服务");
  auto addServiceDialog = new AddServiceDialog(dialog);
  dialog->addContent(addServiceDialog);
  dialog->addButton("确定", true,
                    Dtk::Widget::DDialog::ButtonType::ButtonRecommend);
  dialog->addButton("取消", false, Dtk::Widget::DDialog::ButtonNormal);
  connect(dialog, &Dtk::Widget::DDialog::buttonClicked, this,
          [](int index, const QString &text) {
            qDebug("%s", QString(index).toStdString().c_str());
          });
  dialog->exec();
}

void ServiceManagePage::handleEditService(QModelIndex index) {}

void ServiceManagePage::handleRemoveService(QModelIndex index) {
  auto service =
      ServiceItem::fromJsonValue(index.data(Qt::EditRole).toJsonValue());
  auto dialog = new Dtk::Widget::DDialog(this);
  dialog->setTitle("提示");
  dialog->setMessage("确定要删除 " + service.getServiceName() + " 服务吗？");
  dialog->addButton("确定", true, Dtk::Widget::DDialog::ButtonWarning);
  dialog->addButton("取消", false, Dtk::Widget::DDialog::ButtonRecommend);
  connect(dialog, &Dtk::Widget::DDialog::buttonClicked, this,
          [](int index, const QString &text) {
            qDebug("%s", QString(index).toStdString().c_str());
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
