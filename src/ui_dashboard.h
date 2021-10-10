/********************************************************************************
** Form generated from reading UI file 'dashboard.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DASHBOARD_H
#define UI_DASHBOARD_H

#include <DLabel>
#include <DWidget>
#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <qchartview.h>

QT_BEGIN_NAMESPACE
DWIDGET_USE_NAMESPACE

class Ui_DashBoard
{
public:
  QGridLayout* gridLayout;
  QVBoxLayout* verticalLayout;
  QVBoxLayout* dashboardFrame;
  QHBoxLayout* horizontalLayout;
  QLabel* label;
  QComboBox* comboBox;
  QPushButton* btnMonitor;
  QSpacerItem* verticalSpacer;
  QVBoxLayout* statusLayout;
  QHBoxLayout* hl_topview;
  QFrame* frame;
  QVBoxLayout* verticalLayout_3;
  QtCharts::QChartView* graphicsView;
  QVBoxLayout* verticalLayout_4;
  QHBoxLayout* horizontalLayout_4;
  DLabel* label_5;
  DLabel* ll_lastLag;
  QHBoxLayout* horizontalLayout_3;
  DLabel* label_3;
  DLabel* ll_prerequesturl;

  void setupUi(DWidget* DashBoard)
  {
    if (DashBoard->objectName().isEmpty())
      DashBoard->setObjectName(QString::fromUtf8("DashBoard"));
    DashBoard->resize(577, 1080);
    QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(DashBoard->sizePolicy().hasHeightForWidth());
    DashBoard->setSizePolicy(sizePolicy);
    DashBoard->setMinimumSize(QSize(400, 0));
    DashBoard->setStyleSheet(QString::fromUtf8(""));
    gridLayout = new QGridLayout(DashBoard);
    gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
    verticalLayout = new QVBoxLayout();
    verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
    verticalLayout->setSizeConstraint(QLayout::SetMaximumSize);
    dashboardFrame = new QVBoxLayout();
    dashboardFrame->setObjectName(QString::fromUtf8("dashboardFrame"));
    dashboardFrame->setSizeConstraint(QLayout::SetMaximumSize);
    horizontalLayout = new QHBoxLayout();
    horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
    horizontalLayout->setSizeConstraint(QLayout::SetMinimumSize);
    label = new QLabel(DashBoard);
    label->setObjectName(QString::fromUtf8("label"));
    QSizePolicy sizePolicy1(QSizePolicy::Maximum, QSizePolicy::Maximum);
    sizePolicy1.setHorizontalStretch(0);
    sizePolicy1.setVerticalStretch(0);
    sizePolicy1.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
    label->setSizePolicy(sizePolicy1);

    horizontalLayout->addWidget(label, 0, Qt::AlignLeft | Qt::AlignVCenter);

    comboBox = new QComboBox(DashBoard);
    comboBox->setObjectName(QString::fromUtf8("comboBox"));
    QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Fixed);
    sizePolicy2.setHorizontalStretch(0);
    sizePolicy2.setVerticalStretch(0);
    sizePolicy2.setHeightForWidth(comboBox->sizePolicy().hasHeightForWidth());
    comboBox->setSizePolicy(sizePolicy2);

    horizontalLayout->addWidget(comboBox, 0, Qt::AlignVCenter);

    btnMonitor = new QPushButton(DashBoard);
    btnMonitor->setObjectName(QString::fromUtf8("btnMonitor"));
    btnMonitor->setAutoFillBackground(false);
    btnMonitor->setStyleSheet(
      QString::fromUtf8("background-color:  rgb(17, 180, 255)"));

    horizontalLayout->addWidget(btnMonitor);

    horizontalLayout->setStretch(0, 1);
    horizontalLayout->setStretch(1, 10);

    dashboardFrame->addLayout(horizontalLayout);

    verticalSpacer =
      new QSpacerItem(20, 8, QSizePolicy::Minimum, QSizePolicy::Expanding);

    dashboardFrame->addItem(verticalSpacer);

    statusLayout = new QVBoxLayout();
    statusLayout->setObjectName(QString::fromUtf8("statusLayout"));
    hl_topview = new QHBoxLayout();
    hl_topview->setObjectName(QString::fromUtf8("hl_topview"));

    statusLayout->addLayout(hl_topview);

    frame = new QFrame(DashBoard);
    frame->setObjectName(QString::fromUtf8("frame"));
    frame->setFrameShape(QFrame::HLine);
    frame->setFrameShadow(QFrame::Sunken);

    statusLayout->addWidget(frame);

    verticalLayout_3 = new QVBoxLayout();
    verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
    graphicsView = new QtCharts::QChartView(DashBoard);
    graphicsView->setObjectName(QString::fromUtf8("graphicsView"));
    sizePolicy.setHeightForWidth(
      graphicsView->sizePolicy().hasHeightForWidth());
    graphicsView->setSizePolicy(sizePolicy);

    verticalLayout_3->addWidget(graphicsView);

    statusLayout->addLayout(verticalLayout_3);

    verticalLayout_4 = new QVBoxLayout();
    verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
    horizontalLayout_4 = new QHBoxLayout();
    horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
    horizontalLayout_4->setSizeConstraint(QLayout::SetMaximumSize);
    label_5 = new DLabel(DashBoard);
    label_5->setObjectName(QString::fromUtf8("label_5"));
    sizePolicy1.setHeightForWidth(label_5->sizePolicy().hasHeightForWidth());
    label_5->setSizePolicy(sizePolicy1);

    horizontalLayout_4->addWidget(label_5);

    ll_lastLag = new DLabel(DashBoard);
    ll_lastLag->setObjectName(QString::fromUtf8("ll_lastLag"));
    QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Maximum);
    sizePolicy3.setHorizontalStretch(0);
    sizePolicy3.setVerticalStretch(0);
    sizePolicy3.setHeightForWidth(ll_lastLag->sizePolicy().hasHeightForWidth());
    ll_lastLag->setSizePolicy(sizePolicy3);

    horizontalLayout_4->addWidget(ll_lastLag);

    verticalLayout_4->addLayout(horizontalLayout_4);

    horizontalLayout_3 = new QHBoxLayout();
    horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
    horizontalLayout_3->setSizeConstraint(QLayout::SetMaximumSize);
    label_3 = new DLabel(DashBoard);
    label_3->setObjectName(QString::fromUtf8("label_3"));
    sizePolicy1.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
    label_3->setSizePolicy(sizePolicy1);

    horizontalLayout_3->addWidget(label_3);

    ll_prerequesturl = new DLabel(DashBoard);
    ll_prerequesturl->setObjectName(QString::fromUtf8("ll_prerequesturl"));
    sizePolicy3.setHeightForWidth(
      ll_prerequesturl->sizePolicy().hasHeightForWidth());
    ll_prerequesturl->setSizePolicy(sizePolicy3);

    horizontalLayout_3->addWidget(ll_prerequesturl);

    verticalLayout_4->addLayout(horizontalLayout_3);

    statusLayout->addLayout(verticalLayout_4);

    dashboardFrame->addLayout(statusLayout);

    dashboardFrame->setStretch(0, 2);
    dashboardFrame->setStretch(2, 10);

    verticalLayout->addLayout(dashboardFrame);

    gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);

    retranslateUi(DashBoard);

    QMetaObject::connectSlotsByName(DashBoard);
  } // setupUi

  void retranslateUi(DWidget* DashBoard)
  {
    DashBoard->setWindowTitle(
      QCoreApplication::translate("DashBoard", "Form", nullptr));
    label->setText(QCoreApplication::translate(
      "DashBoard", "\345\275\223\345\211\215\347\273\204", nullptr));
    btnMonitor->setText(QCoreApplication::translate(
      "DashBoard",
      "\345\274\200\345\247\213\347\233\221\346\216\247",
      nullptr));
    label_5->setText(QCoreApplication::translate(
      "DashBoard",
      "\344\270\212\346\254\241\345\273\266\350\277\237",
      nullptr));
    ll_lastLag->setText(QString());
    label_3->setText(QCoreApplication::translate(
      "DashBoard",
      "\344\270\212\346\254\241\350\257\267\346\261\202",
      nullptr));
    ll_prerequesturl->setText(QString());
  } // retranslateUi
};

namespace Ui {
class DashBoard : public Ui_DashBoard
{};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DASHBOARD_H
