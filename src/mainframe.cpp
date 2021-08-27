#include "mainframe.h"
#include "dashboard.h"
#include "servicegrouprepo.h"
#include "ui_dashboard.h"
#include "ui_leftsidebar.h"
#include "ui_service_manage.h"

#include <DMenuBar>
#include <QButtonGroup>
#include <QHBoxLayout>
#include <QLine>

MainFrame::MainFrame(QWidget *parent)
    : QWidget(parent), leftSideBar(new Ui::LeftSideBar),
      serviceManagePage(new Ui::ServiceManagePage) {
  this->initUi();

  connect(btnGroup, &QButtonGroup::idClicked, this,
          &MainFrame::sidebarBtnClicked);

  connect(ServiceGroupRepo::instance(), &ServiceGroupRepo::serviceChanged,
          dashboard, &DashBoardPage::onServiceGroupChanged);
}

void MainFrame::initUi() {
  // panel <-> frame
  auto hlayout = new QHBoxLayout(this);
  hlayout->setMargin(4);
  auto sidebarWidget = new QWidget(this);
  leftSideBar->setupUi(sidebarWidget);
  hlayout->addWidget(sidebarWidget, 1, Qt::AlignTop);
  leftSideBar->sidebarLayout->setAlignment(Qt::AlignTop);
  leftSideBar->sidebarLayout->setSpacing(4);
  // import btns
  btnGroup = leftSideBar->bg_sidebar;
  // 设置id
  auto index = 0;
  foreach (QAbstractButton *btn, btnGroup->buttons()) {
    btnGroup->setId(btn, index);
    index++;
  }
  btnGroup->button(0)->setChecked(true);
  connect(btnGroup, &QButtonGroup::idClicked, this, [=](int index) {
    // 切换页面
    rightPanel->setCurrentIndex(index);
  });
  // 分割
  auto splitter = new QFrame(this);
  splitter->setLineWidth(1);
  splitter->setFrameShape(QFrame::VLine);
  splitter->setFrameShadow(QFrame::Shadow::Sunken);
  hlayout->addWidget(splitter);
  // 右侧
  rightPanel = new QStackedWidget(this);
  rightPanel->setMinimumHeight(500);
  hlayout->addWidget(rightPanel, 5, Qt::AlignTop);
  // 用来看总览
  dashboard = new DashBoardPage(this);
  rightPanel->addWidget(dashboard);
  // 用来管理
  auto manageWidget = new QWidget(this);
  serviceManagePage->setupUi(manageWidget);
  rightPanel->addWidget(manageWidget);
}
