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
  auto chartView = new QChartView(this);
  chartView->setMinimumHeight(400);
  chartView->setMinimumWidth(400);
  auto chart = new QChart();
  chart->createDefaultAxes();
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
  // 1s刷新一次
  refreshTimer = new QTimer(this);
  refreshTimer->setInterval(1000);
  connect(refreshTimer, &QTimer::timeout, this, [=]() {
    dDebug() << "trigger latency chart list update";
    auto it = this->ss.values().begin();
    while (it != this->ss.values().end()) {
      (*it)->series->append(this->index, (*it)->y);
      it++;
    }

    this->index++;
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
