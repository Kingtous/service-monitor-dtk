#ifndef MAINFRAME_H
#define MAINFRAME_H

#include "dashboard.h"
#include "servicemanagepage.h"

#include <QButtonGroup>
#include <QObject>
#include <QStackedWidget>
#include <QWidget>

namespace Ui {
class LeftSideBar;
class DashBoard;
class ServiceManagePage;
}; // namespace Ui

class MainFrame : public QWidget {
  Q_OBJECT
public:
  explicit MainFrame(QWidget *parent = nullptr);

signals:
  void sidebarBtnClicked(int index);

private:
  Ui::LeftSideBar *leftSideBar;
  QStackedWidget *rightPanel;
  DashBoardPage *dashboard;
  ServiceManagePage *manageWidget;

  QButtonGroup *btnGroup;

private:
  void initUi();

public slots:
};

#endif // MAINFRAME_H
