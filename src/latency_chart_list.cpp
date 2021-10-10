#include "latency_chart_list.h"

#include <DGraphicsView>
#include <DLabel>
#include <DLog>
#include <QtCharts/QtCharts>

DCORE_USE_NAMESPACE
DWIDGET_USE_NAMESPACE

LatencyChartList::LatencyChartList(ServiceGroup& group, QWidget* parent)
  : QWidget(parent)
{
  this->serviceItems = group.getServices();
  this->groupName = group.getGroupName();
  // init ui
  layout = new QVBoxLayout(this);
  auto it = this->serviceItems->begin();

  chartView = new QChartView(this);
  chartView->setMinimumHeight(500);
  chartView->setMinimumWidth(400);
  chartView->setRenderHint(QPainter::Antialiasing);

  auto label = new DLabel(this);
  label->setText(tr("提示：延迟线在图顶部，表示访问出现超时或出现错误"));
  layout->addWidget(label);

  chart = new QChart();
  chart->setAnimationOptions(chart->AllAnimations);
  chart->setTheme(QChart::ChartThemeDark);

  chartView->setChart(chart);
  layout->addWidget(chartView);

  auto axisX = new QValueAxis(this);
  axisX->setRange(0, 10);
  axisX->setTickCount(10);
  axisX->setLabelFormat("%d");

  while (it != this->serviceItems->end()) {
    auto model = new LatencySeries(); // TODO series parent
    auto series = new QLineSeries(this);
    model->series = series;
    series->setName(it->getServiceName());
    this->ss.insert(it->getServiceName(), model);
    it++;
    //    series->setPointLabelsVisible();
    series->setPointLabelsFormat("@yPoint ms");
    chart->addSeries(series);
    chart->setAxisX(axisX, series);
  }
  // 创建坐标
  chart->createDefaultAxes();
  chart->axisY()->setRange(0, this->maximumLatency);
  chart->axisY()->setMin(0);
  chart->axisY()->setLabelsVisible(true);

  // 1s刷新一次
  refreshTimer = new QTimer(this);
  refreshTimer->setInterval(1000);

  connect(refreshTimer, &QTimer::timeout, this, [=]() {
    auto it = this->ss.keyValueBegin();
    while (it != this->ss.keyValueEnd()) {
      auto latency = it->second->y;
      if (latency == INT_MAX) {
        dWarning() << it->first << "访问出现错误！";
        it->second->series->append(this->index, 2000);
      } else {
        it->second->series->append(this->index, latency);
      }
      //      dDebug() << "append (" << this->index << "," << latency << ")";
      it++;
    }
    // range 10,到了8才继续scroll
    if (this->index > (axisX->max() - axisX->min() - 2)) {
      this->chart->scroll(chart->plotArea().width() / axisX->tickCount(), 0);
    }
    // 计算坐标
    auto indexStep = (axisX->max() - axisX->min()) / axisX->tickCount();
    this->index += indexStep;
  });
  refreshTimer->start();
}

void
LatencyChartList::appendLatency(const ServiceItem& item, qint64 latency)
{
  //  dDebug() << "LatencyChartList:"
  //           << ":" << item.getUrl() << ", " << latency;
  auto name = item.getServiceName();
  auto it = this->ss.find(name);
  if (it != this->ss.end()) {
    //    dDebug() << "LatencyChartList APPEND:"
    //             << ":" << item.getUrl() << ", " << latency;
    if (latency == INT_MAX) {
      latency = this->maximumLatency;
    }
    it.value()->y = latency;
  }
}

void
LatencyChartList::closeEvent(QCloseEvent* event)
{
  refreshTimer->stop();
}
