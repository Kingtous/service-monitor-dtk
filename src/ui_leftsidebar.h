/********************************************************************************
** Form generated from reading UI file 'leftsidebar.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LEFTSIDEBAR_H
#define UI_LEFTSIDEBAR_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

#include <DPushButton>
#include <DWidget>

QT_BEGIN_NAMESPACE
DWIDGET_USE_NAMESPACE

class Ui_LeftSideBar
{
public:
  QGridLayout* gridLayout;
  QVBoxLayout* verticalLayout;
  QHBoxLayout* horizontalLayout;
  QVBoxLayout* sidebarLayout;
  DPushButton* btn_dashboard;
  DPushButton* btn_monitor_config;
  QButtonGroup* bg_sidebar;

  void setupUi(DWidget* LeftSideBar)
  {
    if (LeftSideBar->objectName().isEmpty())
      LeftSideBar->setObjectName(QString::fromUtf8("LeftSideBar"));
    LeftSideBar->resize(208, 510);
    QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(LeftSideBar->sizePolicy().hasHeightForWidth());
    LeftSideBar->setSizePolicy(sizePolicy);
    LeftSideBar->setMinimumSize(QSize(0, 400));
    gridLayout = new QGridLayout(LeftSideBar);
    gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
    verticalLayout = new QVBoxLayout();
    verticalLayout->setSpacing(0);
    verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
    horizontalLayout = new QHBoxLayout();
    horizontalLayout->setSpacing(0);
    horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
    horizontalLayout->setContentsMargins(0, 0, 0, 0);
    sidebarLayout = new QVBoxLayout();
    sidebarLayout->setSpacing(0);
    sidebarLayout->setObjectName(QString::fromUtf8("sidebarLayout"));
    btn_dashboard = new QPushButton(LeftSideBar);
    bg_sidebar = new QButtonGroup(LeftSideBar);
    bg_sidebar->setObjectName(QString::fromUtf8("bg_sidebar"));
    bg_sidebar->setExclusive(true);
    bg_sidebar->addButton(btn_dashboard);
    btn_dashboard->setObjectName(QString::fromUtf8("btn_dashboard"));
    QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
    sizePolicy1.setHorizontalStretch(0);
    sizePolicy1.setVerticalStretch(0);
    sizePolicy1.setHeightForWidth(
      btn_dashboard->sizePolicy().hasHeightForWidth());
    btn_dashboard->setSizePolicy(sizePolicy1);
    btn_dashboard->setMinimumSize(QSize(150, 50));
    QIcon icon;
    icon.addFile(QString::fromUtf8(":/images/icon.svg"),
                 QSize(),
                 QIcon::Normal,
                 QIcon::Off);
    btn_dashboard->setIcon(icon);
    btn_dashboard->setCheckable(true);

    sidebarLayout->addWidget(btn_dashboard, 0, Qt::AlignLeft);

    btn_monitor_config = new QPushButton(LeftSideBar);
    bg_sidebar->addButton(btn_monitor_config);
    btn_monitor_config->setObjectName(QString::fromUtf8("btn_monitor_config"));
    sizePolicy1.setHeightForWidth(
      btn_monitor_config->sizePolicy().hasHeightForWidth());
    btn_monitor_config->setSizePolicy(sizePolicy1);
    btn_monitor_config->setMinimumSize(QSize(150, 50));
    QIcon icon1;
    icon1.addFile(QString::fromUtf8(":/images/menu.svg"),
                  QSize(),
                  QIcon::Normal,
                  QIcon::Off);
    btn_monitor_config->setIcon(icon1);
    btn_monitor_config->setIconSize(QSize(16, 16));
    btn_monitor_config->setCheckable(true);

    sidebarLayout->addWidget(btn_monitor_config, 0, Qt::AlignLeft);

    horizontalLayout->addLayout(sidebarLayout);

    verticalLayout->addLayout(horizontalLayout);

    gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);

    retranslateUi(LeftSideBar);

    QMetaObject::connectSlotsByName(LeftSideBar);
  } // setupUi

  void retranslateUi(DWidget* LeftSideBar)
  {
    LeftSideBar->setWindowTitle(
      QCoreApplication::translate("LeftSideBar", "Form", nullptr));
    btn_dashboard->setText(QCoreApplication::translate(
      "LeftSideBar",
      "\347\233\221\346\216\247\351\235\242\346\235\277",
      nullptr));
    btn_monitor_config->setText(QCoreApplication::translate(
      "LeftSideBar",
      "\347\233\221\346\216\247\350\256\276\347\275\256",
      nullptr));
  } // retranslateUi
};

namespace Ui {
class LeftSideBar : public Ui_LeftSideBar
{};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LEFTSIDEBAR_H
