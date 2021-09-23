#include "dashboard.h"
#include "ui_dashboard.h"

#include <DLog>
#include <DPushButton>

#include <networker/servicegrouprepo.h>
#include <networker/servicemonitor.h>

DWIDGET_USE_NAMESPACE
DCORE_USE_NAMESPACE

DashBoardPage::DashBoardPage(QWidget* parent)
    : QWidget(parent)
{
    ui = new Ui::DashBoard;
    ui->setupUi(this);
    onServiceGroupChanged();
    // 初始化面板
    connect(ui->btnMonitor, &QPushButton::clicked, this, [=](bool checked) {
        if (ServiceMonitor::instance()->isInService()) {

            ServiceMonitor::instance()->stopService();
        } else {

            ServiceMonitor::instance()->startService();
        }
        this->updateSwitchStatus();
    });
    connect(ServiceMonitor::instance(), &ServiceMonitor::onLastRequestResult, this, [=](const ServiceItem& item, const qint64 latency) {
        ui->ll_lastLag->setText(QString::number(latency) + "ms");
        ui->ll_prerequesturl->setText(item.getUrl());
    });
}

void DashBoardPage::onServiceGroupChanged()
{
    auto serviceGroups = ServiceGroupRepo::instance()->getServiceGroups();
    auto length = serviceGroups.length();
    for (int index = 0; index < length; index++) {
        auto serviceGroup = serviceGroups[index];
        ui->comboBox->addItem(serviceGroup.getGroupName());
    }
}

void DashBoardPage::updateSwitchStatus()
{
    // update status
    if (ServiceMonitor::instance()->isInService()) {
        ui->btnMonitor->setChecked(true);
        ui->btnMonitor->setStyleSheet("background-color: rgb(240,49,104)");
        ui->btnMonitor->setText(tr("停止监控"));
    } else {
        ui->btnMonitor->setChecked(false);
        ui->btnMonitor->setStyleSheet("background-color: rgb(17,180,255)");
        ui->btnMonitor->setText(tr("开始监控"));
    }
}
