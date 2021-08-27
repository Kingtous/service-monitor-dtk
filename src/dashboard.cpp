#include "dashboard.h"
#include "servicegrouprepo.h"
#include "ui_dashboard.h"

DashBoardPage::DashBoardPage(QWidget *parent) : QWidget(parent) {
  ui = new Ui::DashBoard;
  ui->setupUi(this);
}

void DashBoardPage::onServiceGroupChanged() {
  auto serviceGroups = ServiceGroupRepo::instance()->getServiceGroups();
  auto length = serviceGroups.length();
  for (int index = 0; index < length; index++) {
    auto serviceGroup = serviceGroups[index];
    ui->comboBox->addItem(serviceGroup.getGroupName());
  }
}
