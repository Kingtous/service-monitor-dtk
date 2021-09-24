#include "dashboard.h"
#include "ui_dashboard.h"

#include <DLabel>
#include <DLog>
#include <DPushButton>
#include <DThemeManager>
#include <QtCharts/QtCharts>

#include <networker/servicegrouprepo.h>
#include <networker/servicemonitor.h>

DWIDGET_USE_NAMESPACE
DCORE_USE_NAMESPACE

DashBoardPage::DashBoardPage(QWidget* parent)
    : QWidget(parent)
{
    ui = new Ui::DashBoard;
    ui->setupUi(this);
    // 数量
    auto tv = ui->hl_topview;
    tv->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    ll_dis_totalnum = new DLabel(this);
    ll_totalnum = new DLabel(this);
    ll_dis_totalnum->setText("组监控数量");
    ll_totalnum->setNum(0);
    ll_totalnum->setAlignment(Qt::AlignLeft);
    tv->addWidget(ll_dis_totalnum);
    tv->addWidget(ll_totalnum);
    // 初始化折线图
    latencySeries = new QLineSeries(this);
    latencySeries->setName("延迟");
    //    latencySeries->setPointLabelsVisible(true);
    //    timeoutSeries = new QScatterSeries(this);
    //    timeoutSeries->setName("超时");
    QChart* chart = new QChart();
    chart->setTitle("延迟总图");
    chart->addSeries(latencySeries);
    //    chart->addSeries(timeoutSeries);
    chart->createDefaultAxes();
    chart->legend()->hide();
    chart->setAnimationOptions(QChart::AllAnimations);
    chart->setTheme(QChart::ChartThemeDark);
    auto axisX = new QValueAxis(this);
    axisX->setRange(0, 10);
    axisX->setTickCount(5);
    axisX->setLabelFormat("%d");
    chart->axisY()->setMin(0);
    chart->axisY()->setRange(0, 500);
    chart->setAxisX(axisX, latencySeries);
    //    chart->setAxisX(axisX, timeoutSeries);
    ui->graphicsView->setChart(chart);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    // 初->化数据
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
    connect(ServiceMonitor::instance(), &ServiceMonitor::onLastRequestResult, this, [=](const ServiceGroup& group, const ServiceItem& item, const qint64 latency) {
        if (latency == INT_MAX) {
            ui->ll_lastLag->setText("访问超时");
        } else {
            ui->ll_lastLag->setText(QString::number(latency) + "ms");
            if (latency > this->maxLatency) {
                chart->axisY()->setRange(0, latency + 200);
                this->maxLatency = latency;
            } else {
                chart->axisY()->setRange(0, maxLatency + 200);
            }
        }
        qreal indexStep = (axisX->max() - axisX->min()) / axisX->tickCount();
        index += indexStep;
        this->latencySeries->append(index, latency);
        ui->ll_prerequesturl->setText(item.getUrl());
        dDebug() << "index:" << index << ",latency:" << latency;
        // TODO: 上一次请求结果，包含group信息，可以发送到可视化窗口
        if (index >= axisX->tickCount()) {
            auto pos = chart->plotArea().width() / axisX->tickCount();
            dDebug() << "scroll to x:" << pos;
            chart->scroll(pos, 0);
        }
    });
    QComboBox box;
    connect(ui->comboBox, &QComboBox::currentTextChanged, this, [=](const QString& text) {
        this->loadGroup(text);
    });
}

void DashBoardPage::onServiceGroupChanged()
{
    auto serviceGroups = ServiceGroupRepo::instance()->getServiceGroups();
    auto length = serviceGroups.length();
    ui->comboBox->clear();
    for (int index = 0; index < length; index++) {
        auto serviceGroup = serviceGroups[index];
        ui->comboBox->addItem(serviceGroup.getGroupName());
        if (index == 0) {
            loadGroup(serviceGroup.getGroupName());
        }
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

void DashBoardPage::loadGroup(const QString& gname)
{
    int index = ServiceGroupRepo::instance()->findGroup(gname);
    if (index != -1) {
        auto group = ServiceGroupRepo::instance()->getServiceGroups()[index];
        ll_totalnum->setNum(group.getServices()->length());
    }
}
