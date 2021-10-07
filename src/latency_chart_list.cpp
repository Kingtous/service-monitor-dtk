#include "latency_chart_list.h"

#include <DGraphicsView>
#include <DLog>
#include <QtCharts/QtCharts>

DCORE_USE_NAMESPACE

LatencyChartList::LatencyChartList(ServiceGroup &group, QWidget *parent)
    : QWidget(parent) {
  this->serviceItems = group.getServices();
  this->groupName = group.getGroupName();
  // init ui
  layout = new QVBoxLayout(this);
  auto it = this->serviceItems->begin();

  chartView = new QChartView(this);
  chartView->setMinimumHeight(400);
  chartView->setMinimumWidth(400);
  chartView->setRenderHint(QPainter::Antialiasing);

  chart = new QChart();
  chart->setTheme(QChart::ChartThemeDark);
  chartView->setChart(chart);
  layout->addWidget(chartView);

  auto axisX = new QValueAxis(this);
  axisX->setRange(0, 10);
  axisX->setTickCount(5);
  axisX->setLabelFormat("%d");

  while (it != this->serviceItems->end()) {
    auto model = new LatencySeries(); // TODO series parent
    auto series = new QLineSeries(this);
    model->series = series;
    series->setName(it->getServiceName());
    this->ss.insert(it->getServiceName(), model);
    it++;
    chart->addSeries(series);
    chart->setAxisX(axisX, series);
  }
  // 创建坐标
  chart->createDefaultAxes();
  chart->axisY()->setRange(0, 5000);
  chart->axisY()->setMin(0);

  // 1s刷新一次
  refreshTimer = new QTimer(this);
  refreshTimer->setInterval(1000);
  connect(refreshTimer, &QTimer::timeout, this, [=]() {
    auto it = this->ss.keyValueBegin();
    while (it != this->ss.keyValueEnd()) {
      auto latency = it->second->y;
      it->second->series->append(this->index, latency);
      dDebug() << "append (" << this->index << "," << latency << ")";
      it++;
    }

    // range 10,到了5才继续scroll
    if (this->index > 5) {
      this->chart->scroll(chart->plotArea().width() / axisX->tickCount(), 0);
    }
    // 计算坐标
    auto indexStep = (axisX->max() - axisX->min()) / axisX->tickCount();
    this->index += indexStep;
  });
  refreshTimer->start();
}

void LatencyChartList::appendLatency(const ServiceItem &item, qint64 latency) {
  dDebug() << "LatencyChartList:"
           << ":" << item.getUrl() << ", " << latency;
  auto name = item.getServiceName();
  auto it = this->ss.find(name);
  if (it != this->ss.end()) {
    dDebug() << "LatencyChartList APPEND:"
             << ":" << item.getUrl() << ", " << latency;
    it.value()->y = latency;
  }
}

void LatencyChartList::closeEvent(QCloseEvent *event) { refreshTimer->stop(); }
