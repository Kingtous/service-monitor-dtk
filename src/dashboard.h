#ifndef DASHBOARD_H
#define DASHBOARD_H

#include "ui_dashboard.h"

#include <QWidget>

class DashBoardPage : public QWidget {
  Q_OBJECT
public:
  explicit DashBoardPage(QWidget *parent = nullptr);

public slots:
  void onServiceGroupChanged();

private:
  Ui::DashBoard *ui;
};

#endif // DASHBOARD_H
