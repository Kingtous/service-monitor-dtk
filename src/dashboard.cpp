#include "dashboard.h"
#include "services_detail_page.h"
#include "ui_dashboard.h"

#include <DDialog>
#include <DFrame>
#include <DGraphicsView>
#include <DLabel>
#include <DLog>
#include <DPushButton>
#include <DThemeManager>
#include <QtCharts/QtCharts>

#include <networker/servicegrouprepo.h>
#include <networker/servicemonitor.h>

DWIDGET_USE_NAMESPACE
DCORE_USE_NAMESPACE

DashBoardPage::DashBoardPage(DWidget* parent)
  : DWidget(parent)
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
  tv->addWidget(ll_dis_totalnum, 0, Qt::AlignBaseline);
  tv->addWidget(ll_totalnum, 0, Qt::AlignBaseline);
  // 详情按钮
  auto groupDetailBtn = new DPushButton(this);
  groupDetailBtn->setText(tr("详情"));
  connect(groupDetailBtn, &DPushButton::clicked, this, [=]() {
    // TODO 增加越界检查
    auto groups = ServiceGroupRepo::instance()->getServiceGroups();
    if (groups.empty()) {
      DDialog dialog;
      dialog.setTitle("提示");
      dialog.setMessage("还未添加任何组哦～请到右上角先添加组");
      dialog.addButton("确定", true, DDialog::ButtonType::ButtonRecommend);
      dialog.exec();
      return;
    }
    auto group = groups[this->currentGroupIndex];
    DDialog dialog;
    dialog.setTitle("组监控面板");
    auto widget = new ServicesDetailPage(group, &dialog);
    dialog.addContent(widget);
    auto conn = connect(ServiceMonitor::instance(),
                        &ServiceMonitor::onLastRequestResult,
                        widget,
                        &ServicesDetailPage::onLatencyUpdate);
    dialog.exec();
  });
  tv->addWidget(groupDetailBtn, 0, Qt::AlignBaseline);

  auto splitter = new DFrame(this);
  splitter->setLineWidth(1);
  splitter->setFrameShape(DFrame::HLine);
  splitter->setFrameShadow(DFrame::Shadow::Sunken);
  tv->insertWidget(2, splitter);
  // 初始化折线图

  latencySeries = new QLineSeries(this);
  latencySeries->setName("延迟");
  latencySeries->setColor(QColor(240, 240, 240));
  latencySeries->setPointLabelsVisible();
  latencySeries->setPointLabelsFormat("@yPoint ms");
  latencySeries->setPointLabelsVisible(true);
  //  latencySeries->setUseOpenGL();
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
  chart->axisY()->setRange(0, 2000);
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
  connect(ServiceMonitor::instance(),
          &ServiceMonitor::onLastRequestResult,
          this,
          [=](const ServiceGroup& group,
              const ServiceItem& item,
              const qint64 latency) {
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
            qreal indexStep =
              (axisX->max() - axisX->min()) / axisX->tickCount();
            index += indexStep;
            this->latencySeries->append(index, latency);
            ui->ll_prerequesturl->setText(item.getUrl());
            //        dDebug() << "index:" << index << ",latency:" << latency;
            // TODO: 上一次请求结果，包含group信息，可以发送到可视化窗口
            if (index >= axisX->tickCount()) {
              auto pos = chart->plotArea().width() / axisX->tickCount();
              chart->scroll(pos, 0);
            }
          });

  QComboBox box;
  connect(ui->comboBox,
          &QComboBox::currentTextChanged,
          this,
          [=](const QString& text) { this->loadGroup(text); });
}

void
DashBoardPage::onServiceGroupChanged()
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
  // reset
  currentGroupIndex = 0;
}

void
DashBoardPage::updateSwitchStatus()
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

void
DashBoardPage::loadGroup(const QString& gname)
{
  int index = ServiceGroupRepo::instance()->findGroup(gname);
  if (index != -1) {
    auto group = ServiceGroupRepo::instance()->getServiceGroups()[index];
    ll_totalnum->setNum(group.getServices()->length());
    // reset index to index
    currentGroupIndex = index;
  } else {
    currentGroupIndex = 0;
  }
}
