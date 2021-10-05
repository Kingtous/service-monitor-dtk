#include "services_detail_page.h"
#include "latency_chart_list.h"
#include <DLabel>
#include <DLog>
#include <QVBoxLayout>

DWIDGET_USE_NAMESPACE
DCORE_USE_NAMESPACE

ServicesDetailPage::ServicesDetailPage(ServiceGroup& group, QWidget* parent)
    : QWidget(parent)
    , group(group)
{
    auto layout = new QVBoxLayout(this);
    // label
    auto label = new DLabel(this);
    label->setText(group.getGroupName());
    // 添加list
    latencyChart = new LatencyChartList(group, this);
    layout->addWidget(label, Qt::AlignHCenter);
    layout->addWidget(latencyChart, Qt::AlignCenter);
}

void ServicesDetailPage::onLatencyUpdate(const ServiceGroup& group, const ServiceItem& item, qint64 latency)
{
    dDebug() << "ServiceDetailPage:" << group.getGroupName() << ":" << item.getUrl() << ", " << latency;
    if (this->group.getGroupName() == group.getGroupName()) {
        latencyChart->appendLatency(item, latency);
    } else {
        // ignore
    }
}
