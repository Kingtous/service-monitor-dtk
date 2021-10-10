#include "mainframe.h"
#include "dashboard.h"
#include "servicemanagepage.h"
#include "ui_dashboard.h"
#include "ui_leftsidebar.h"
#include "ui_service_manage.h"

#include <DFrame>
#include <DMenuBar>
#include <DPushButton>
#include <DWidget>
#include <QButtonGroup>
#include <QHBoxLayout>
#include <QLine>

#include <networker/servicegrouprepo.h>

MainFrame::MainFrame(QWidget* parent)
  : QWidget(parent)
  , leftSideBar(new Ui::LeftSideBar)
{
  this->initUi();

  connect(
    btnGroup, &QButtonGroup::idClicked, this, &MainFrame::sidebarBtnClicked);

  connect(ServiceGroupRepo::instance(),
          &ServiceGroupRepo::serviceChanged,
          dashboard,
          &DashBoardPage::onServiceGroupChanged);
  connect(ServiceGroupRepo::instance(),
          &ServiceGroupRepo::serviceChanged,
          this->manageWidget,
          &ServiceManagePage::onServiceGroupsChanged);
}

void
MainFrame::initUi()
{
  // panel <-> frame
  auto hlayout = new QHBoxLayout(this);
  hlayout->setMargin(4);
  auto sidebarWidget = new DWidget(this);
  leftSideBar->setupUi(sidebarWidget);
  hlayout->addWidget(sidebarWidget, 1, Qt::AlignTop);
  leftSideBar->sidebarLayout->setAlignment(Qt::AlignTop);
  leftSideBar->sidebarLayout->setSpacing(4);
  // import btns
  btnGroup = leftSideBar->bg_sidebar;
  // 设置id
  auto index = 0;
  foreach (QAbstractButton* btn, btnGroup->buttons()) {
    btnGroup->setId(btn, index);
    index++;
  }
  btnGroup->button(0)->setChecked(true);
  connect(btnGroup, &QButtonGroup::idClicked, this, [=](int index) {
    // 切换页面
    rightPanel->setCurrentIndex(index);
  });
  // 分割
  auto splitter = new DFrame(this);
  splitter->setLineWidth(1);
  splitter->setFrameShape(DFrame::VLine);
  splitter->setFrameShadow(DFrame::Shadow::Sunken);
  hlayout->addWidget(splitter);
  // 右侧
  rightPanel = new DStackedWidget(this);
  rightPanel->setMinimumHeight(500);
  rightPanel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  hlayout->addWidget(rightPanel, 5, Qt::AlignTop);
  // 用来看总览
  dashboard = new DashBoardPage(this);
  rightPanel->addWidget(dashboard);
  dashboard->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  // 用来管理
  manageWidget = new ServiceManagePage(this);
  rightPanel->addWidget(manageWidget);
}
