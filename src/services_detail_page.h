#ifndef SERVICES_DETAIL_PAGE_H
#define SERVICES_DETAIL_PAGE_H

#include "latency_chart_list.h"

#include <QWidget>

#include <networker/servicegroup.h>

class ServicesDetailPage : public QWidget {
    Q_OBJECT
public:
    explicit ServicesDetailPage(ServiceGroup& group, QWidget* parent = nullptr);

signals:

public slots:
    void onLatencyUpdate(const ServiceGroup& group, const ServiceItem& item, qint64 latency);

private:
    ServiceGroup group;
    LatencyChartList* latencyChart;
};

#endif // SERVICES_DETAIL_PAGE_H
