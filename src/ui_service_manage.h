/********************************************************************************
** Form generated from reading UI file 'service_manage.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SERVICE_MANAGE_H
#define UI_SERVICE_MANAGE_H

#include <DLabel>
#include <DTreeView>
#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE
DWIDGET_USE_NAMESPACE

class Ui_ServiceManagePage
{
public:
  QGridLayout* gridLayout;
  QVBoxLayout* verticalLayout;
  DLabel* label;
  DTreeView* treeView;

  void setupUi(QWidget* ServiceManagePage)
  {
    if (ServiceManagePage->objectName().isEmpty())
      ServiceManagePage->setObjectName(QString::fromUtf8("ServiceManagePage"));
    ServiceManagePage->resize(400, 300);
    gridLayout = new QGridLayout(ServiceManagePage);
    gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
    verticalLayout = new QVBoxLayout();
    verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
    label = new DLabel(ServiceManagePage);
    label->setObjectName(QString::fromUtf8("label"));

    verticalLayout->addWidget(label, 0, Qt::AlignHCenter | Qt::AlignVCenter);

    treeView = new DTreeView(ServiceManagePage);
    treeView->setObjectName(QString::fromUtf8("treeView"));

    verticalLayout->addWidget(treeView);

    gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);

    retranslateUi(ServiceManagePage);

    QMetaObject::connectSlotsByName(ServiceManagePage);
  } // setupUi

  void retranslateUi(DWidget* ServiceManagePage)
  {
    ServiceManagePage->setWindowTitle(
      QCoreApplication::translate("ServiceManagePage", "Form", nullptr));
    label->setText(QCoreApplication::translate(
      "ServiceManagePage",
      "\350\256\276\347\275\256\351\241\265\351\235\242",
      nullptr));
  } // retranslateUi
};

namespace Ui {
class ServiceManagePage : public Ui_ServiceManagePage
{};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SERVICE_MANAGE_H
