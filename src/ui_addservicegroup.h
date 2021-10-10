/********************************************************************************
** Form generated from reading UI file 'addservicegroup.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDSERVICEGROUP_H
#define UI_ADDSERVICEGROUP_H

#include <DWidget>
#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <dlabel.h>
#include <dlineedit.h>

QT_BEGIN_NAMESPACE
DWIDGET_USE_NAMESPACE

class Ui_AddServiceGroup
{
public:
  QGridLayout* gridLayout;
  QVBoxLayout* verticalLayout;
  QVBoxLayout* verticalLayout_2;
  QHBoxLayout* horizontalLayout;
  DLabel* label_2;
  DLineEdit* groupNameEdit;

  void setupUi(DWidget* AddServiceGroup)
  {
    if (AddServiceGroup->objectName().isEmpty())
      AddServiceGroup->setObjectName(QString::fromUtf8("AddServiceGroup"));
    AddServiceGroup->resize(491, 188);
    gridLayout = new QGridLayout(AddServiceGroup);
    gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
    verticalLayout = new QVBoxLayout();
    verticalLayout->setSpacing(4);
    verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
    verticalLayout->setContentsMargins(4, 4, 4, 4);
    verticalLayout_2 = new QVBoxLayout();
    verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
    horizontalLayout = new QHBoxLayout();
    horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
    horizontalLayout->setContentsMargins(16, 16, 16, 16);
    label_2 = new DLabel(AddServiceGroup);
    label_2->setObjectName(QString::fromUtf8("label_2"));

    horizontalLayout->addWidget(label_2);

    groupNameEdit = new DLineEdit(AddServiceGroup);
    groupNameEdit->setObjectName(QString::fromUtf8("groupNameEdit"));

    horizontalLayout->addWidget(groupNameEdit);

    verticalLayout_2->addLayout(horizontalLayout);

    verticalLayout->addLayout(verticalLayout_2);

    gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);

    retranslateUi(AddServiceGroup);

    QMetaObject::connectSlotsByName(AddServiceGroup);
  } // setupUi

  void retranslateUi(DWidget* AddServiceGroup)
  {
    AddServiceGroup->setWindowTitle(QCoreApplication::translate(
      "AddServiceGroup",
      "\350\257\267\350\276\223\345\205\245\347\233\221\346\216\247\347\273\204"
      "\345\220\215\347\247\260",
      nullptr));
    label_2->setText(QCoreApplication::translate(
      "AddServiceGroup",
      "\347\233\221\346\216\247\347\273\204\345\220\215\347\247\260",
      nullptr));
  } // retranslateUi
};

namespace Ui {
class AddServiceGroup : public Ui_AddServiceGroup
{};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDSERVICEGROUP_H
