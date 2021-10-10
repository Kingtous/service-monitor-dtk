#ifndef LATENCY_CHART_LIST_H
#define LATENCY_CHART_LIST_H

#include <QChartView>
#include <QLineSeries>
#include <QTimer>
#include <QVBoxLayout>
#include <QValueAxis>
#include <QWidget>

#include <networker/servicegroup.h>
#include <networker/serviceitem.h>

QT_CHARTS_USE_NAMESPACE

struct LatencySeries;

class LatencyChartList : public QWidget
{
  Q_OBJECT
public:
  LatencyChartList(ServiceGroup& group, QWidget* parent = nullptr);

public slots:
  void appendLatency(const ServiceItem& item, qint64 latency);

private:
  QWidget* root;
  QVBoxLayout* layout;
  QString groupName{ "" };
  QList<ServiceItem>* serviceItems;
  QMap<QString, LatencySeries*> ss;
  volatile int index{ 0 };
  QTimer* refreshTimer;
  QChartView* chartView;
  QChart* chart;
  QColor color;

  // QWidget interface
protected:
  void closeEvent(QCloseEvent* event);
};

typedef struct LatencySeries
{
  QLineSeries* series = nullptr;
  qreal y = 0; // 上一次延迟
} LatencySeries;

#endif // LATENCY_CHART_LIST_H
