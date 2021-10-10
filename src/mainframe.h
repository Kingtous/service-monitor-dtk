#ifndef MAINFRAME_H
#define MAINFRAME_H

#include "dashboard.h"
#include "servicemanagepage.h"

#include <DStackedWidget>
#include <DWidget>
#include <QButtonGroup>
#include <QObject>

DWIDGET_USE_NAMESPACE

namespace Ui {
class LeftSideBar;
class DashBoard;
class ServiceManagePage;
}; // namespace Ui

class MainFrame : public DWidget
{
  Q_OBJECT
public:
  explicit MainFrame(DWidget* parent = nullptr);

signals:
  void sidebarBtnClicked(int index);

private:
  Ui::LeftSideBar* leftSideBar;
  QStackedWidget* rightPanel;
  DashBoardPage* dashboard;
  ServiceManagePage* manageWidget;

  QButtonGroup* btnGroup;

private:
  void initUi();

public slots:
};

#endif // MAINFRAME_H
