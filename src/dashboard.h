#ifndef DASHBOARD_H
#define DASHBOARD_H

#include "ui_dashboard.h"

#include <DLabel>
#include <QLineSeries>
#include <QScatterSeries>
#include <QSplineSeries>
#include <QWidget>

DWIDGET_USE_NAMESPACE
QT_CHARTS_USE_NAMESPACE

class DashBoardPage : public QWidget {
    Q_OBJECT
public:
    explicit DashBoardPage(QWidget* parent = nullptr);

public slots:
    void onServiceGroupChanged();

private:
    void updateSwitchStatus();

private:
    Ui::DashBoard* ui;
    DLabel* ll_dis_totalnum;
    DLabel* ll_totalnum;
    volatile int index { 0 };
    int currentGroupIndex { 0 };
    qint64 maxLatency { 0 };
    // 总数据
    QLineSeries* latencySeries;
    QScatterSeries* timeoutSeries;
    void loadGroup(const QString& gname);
};

#endif // DASHBOARD_H
