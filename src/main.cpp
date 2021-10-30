#include "mainframe.h"
#include "ui_addservicegroup.h"

#include <DApplication>
#include <DApplicationSettings>
#include <DDesktopServices>
#include <DDialog>
#include <DFontSizeManager>
#include <DLog>
#include <DMainWindow>
#include <DProgressBar>
#include <DTitlebar>
#include <DToast>
#include <DWidget>
#include <DWidgetUtil>

#include <QDate>
#include <QDebug>
#include <QDesktopServices>
#include <QLayout>
#include <QMetaProperty>
#include <QPropertyAnimation>

#include <networker/servicegrouprepo.h>
DWIDGET_USE_NAMESPACE

extern DMainWindow* window;

DMainWindow* window;

void
initService();
void
initMenuTriggers();

int
main(int argc, char* argv[])
{
  QGuiApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
  DApplication a(argc, argv);
  a.setOrganizationName("kingtous");
  a.setApplicationName("service_monitor");
  a.setApplicationVersion("1.0");
  a.setProductIcon(QIcon(":/images/icon.svg"));
  a.setProductName("service-monitor");
  a.setApplicationDescription("Service API Monitor");

  a.loadTranslator();
  a.setApplicationDisplayName(
    QCoreApplication::translate("Main", "DTK Application"));
  Dtk::Core::DLogManager::registerFileAppender();
  Dtk::Core::DLogManager::registerConsoleAppender();

  // 保存程序的窗口主题设置
  DApplicationSettings as;
  Q_UNUSED(as)

  window = new DMainWindow();
  window->titlebar()->setIcon(QIcon(":/images/icon.svg"));
  window->titlebar()->setTitle("服务监控助手");
  // 设置标题，宽度不够会隐藏标题文字
  window->setMinimumSize(QSize(800, 300));

  DWidget* cw = new DWidget(window);
  QVBoxLayout* layout = new QVBoxLayout(cw);
  // process bar
  // main frame
  MainFrame* frame = new MainFrame();
  // 绑定字体大小
  DFontSizeManager::instance()->bind(frame, DFontSizeManager::T5);
  layout->addWidget(frame);
  window->setCentralWidget(cw);
  window->show();
  Dtk::Widget::moveToCenter(window);
  // 初始化服务
  initService();
  initMenuTriggers();
  return a.exec();
}

void
initService()
{
  ServiceGroupRepo::instance()->init();
}

void
initMenuTriggers()
{
  // 监控组变更提示
  QObject::connect(ServiceGroupRepo::instance(),
                   &ServiceGroupRepo::serviceChanged,
                   window,
                   [=]() {
                     DFloatingMessage message;
                     message.setMessage("监控组已更新");
                     window->sendMessage(&message);
                   });

  // set menubar
  auto mMonitor = window->titlebar()->menu()->addAction("添加监控组");
  QObject::connect(mMonitor, &QAction::triggered, window, [=]() {
    DDialog dialog{ "", "请输入监控组名称" };
    DWidget content;
    Ui::AddServiceGroup ui;
    ui.setupUi(&content);
    dialog.addContent(&content);
    dialog.addButton("确定", true, DDialog::ButtonType::ButtonRecommend);
    dialog.addButton("取消", true, DDialog::ButtonType::ButtonNormal);
    QString gname;
    QObject::connect(ui.groupNameEdit,
                     &DLineEdit::textChanged,
                     window,
                     [&](const QString& text) { gname = text; });
    // 确定进行添加
    QObject::connect(&dialog, &DDialog::buttonClicked, window, [&](int index) {
      if (index == 0) {
        auto res = ServiceGroupRepo::instance()->registerGroup(gname);
        if (!res) {
          DDialog dialog;
          dialog.setTitle("添加失败");
          dialog.setMessage("可能存在同名组，请检查");
          dialog.addButton("确定", true, DDialog::ButtonType::ButtonRecommend);
          dialog.exec();
        }
      }
    });

    dialog.exec();
  });

  // 打开日志
  auto mOpenLog = window->titlebar()->menu()->addAction("打开日志文件夹");
  QObject::connect(mOpenLog, &QAction::triggered, window, [=]() {
    DDesktopServices::showFolder(DLogManager::getlogFilePath());
  });

  // 打开日志
  auto mHelper = window->titlebar()->menu()->addAction("使用帮助");
  QObject::connect(mHelper, &QAction::triggered, window, [=]() {
    QDesktopServices::openUrl(
      QUrl(QLatin1String("http://service-monitor-wiki.kingtous.cn/")));
  });

  // 注册ServiceItem
  qRegisterMetaType<ServiceItem>("ServiceItem");
}
