/********************************************************************************
** Form generated from reading UI file 'addservicedialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDSERVICEDIALOG_H
#define UI_ADDSERVICEDIALOG_H

#include <DComboBox>
#include <DWidget>
#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <dlabel.h>
#include <dlineedit.h>
#include <dspinbox.h>
#include <networker/servicegrouprepo.h>

QT_BEGIN_NAMESPACE
DWIDGET_USE_NAMESPACE

class Ui_AddServiceDialog
{
public:
  QGridLayout* gridLayout;
  QHBoxLayout* horizontalLayout_4;
  DLabel* label_4;
  DLineEdit* requestBody;
  QVBoxLayout* verticalLayout;
  QHBoxLayout* horizontalLayout;
  DLabel* label;
  DLineEdit* serviceName;
  QHBoxLayout* horizontalLayout_2;
  DLabel* label_2;
  DComboBox* methodCombo;
  QHBoxLayout* horizontalLayout_5;
  DLabel* label_5;
  DLabel* label_9;
  DSpinBox* checkGap;
  DComboBox* comboBox_2;
  QHBoxLayout* horizontalLayout_6;
  DLabel* label_6;
  DSpinBox* timeoutInSec;
  DLabel* label_7;
  QHBoxLayout* horizontalLayout_3;
  DLabel* label_3;
  DLineEdit* url;
  QRegExp* regExp;
  QRegExpValidator* urlValidator;

  void setupUi(DWidget* AddServiceDialog)
  {
    regExp = new QRegExp(ServiceGroupRepo::instance()->urlRegex);
    urlValidator = new QRegExpValidator(*regExp, AddServiceDialog);

    if (AddServiceDialog->objectName().isEmpty())
      AddServiceDialog->setObjectName(QString::fromUtf8("AddServiceDialog"));
    AddServiceDialog->resize(600, 521);
    gridLayout = new QGridLayout(AddServiceDialog);
    gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
    horizontalLayout_4 = new QHBoxLayout();
    horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
    label_4 = new DLabel(AddServiceDialog);
    label_4->setObjectName(QString::fromUtf8("label_4"));

    horizontalLayout_4->addWidget(label_4);

    requestBody = new DLineEdit(AddServiceDialog);
    requestBody->setObjectName(QString::fromUtf8("requestBody"));
    requestBody->setPlaceholderText("{\"code:0\"}");

    horizontalLayout_4->addWidget(requestBody);

    gridLayout->addLayout(horizontalLayout_4, 4, 0, 1, 1);

    verticalLayout = new QVBoxLayout();
    verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
    horizontalLayout = new QHBoxLayout();
    horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
    label = new DLabel(AddServiceDialog);
    label->setObjectName(QString::fromUtf8("label"));

    horizontalLayout->addWidget(label);

    serviceName = new DLineEdit(AddServiceDialog);
    serviceName->setObjectName(QString::fromUtf8("serviceName"));
    serviceName->setPlaceholderText("测试地址名");

    horizontalLayout->addWidget(serviceName);

    verticalLayout->addLayout(horizontalLayout);

    gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);

    horizontalLayout_2 = new QHBoxLayout();
    horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
    label_2 = new DLabel(AddServiceDialog);
    label_2->setObjectName(QString::fromUtf8("label_2"));

    horizontalLayout_2->addWidget(label_2);

    methodCombo = new DComboBox(AddServiceDialog);
    methodCombo->addItem(QString());
    methodCombo->addItem(QString());
    methodCombo->setObjectName(QString::fromUtf8("methodCombo"));
    QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(methodCombo->sizePolicy().hasHeightForWidth());
    methodCombo->setSizePolicy(sizePolicy);

    horizontalLayout_2->addWidget(methodCombo);

    gridLayout->addLayout(horizontalLayout_2, 2, 0, 1, 1);

    horizontalLayout_5 = new QHBoxLayout();
    horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
    label_5 = new DLabel(AddServiceDialog);
    label_5->setObjectName(QString::fromUtf8("label_5"));

    horizontalLayout_5->addWidget(label_5);

    label_9 = new DLabel(AddServiceDialog);
    label_9->setObjectName(QString::fromUtf8("label_9"));

    horizontalLayout_5->addWidget(label_9);

    checkGap = new DSpinBox(AddServiceDialog);
    checkGap->setObjectName(QString::fromUtf8("checkGap"));
    sizePolicy.setHeightForWidth(checkGap->sizePolicy().hasHeightForWidth());
    checkGap->setSizePolicy(sizePolicy);
    checkGap->setMinimum(1);
    checkGap->setMaximum(999999999);
    checkGap->setValue(5);

    horizontalLayout_5->addWidget(checkGap);

    comboBox_2 = new DComboBox(AddServiceDialog);
    comboBox_2->addItem(QString());
    comboBox_2->setObjectName(QString::fromUtf8("comboBox_2"));

    horizontalLayout_5->addWidget(comboBox_2);

    gridLayout->addLayout(horizontalLayout_5, 5, 0, 1, 1);

    horizontalLayout_6 = new QHBoxLayout();
    horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
    label_6 = new DLabel(AddServiceDialog);
    label_6->setObjectName(QString::fromUtf8("label_6"));

    horizontalLayout_6->addWidget(label_6);

    timeoutInSec = new DSpinBox(AddServiceDialog);
    timeoutInSec->setObjectName(QString::fromUtf8("timeoutInSec"));
    sizePolicy.setHeightForWidth(
      timeoutInSec->sizePolicy().hasHeightForWidth());
    timeoutInSec->setSizePolicy(sizePolicy);
    timeoutInSec->setMinimum(1);
    timeoutInSec->setMaximum(60);

    horizontalLayout_6->addWidget(timeoutInSec);

    label_7 = new DLabel(AddServiceDialog);
    label_7->setObjectName(QString::fromUtf8("label_7"));

    horizontalLayout_6->addWidget(label_7);

    gridLayout->addLayout(horizontalLayout_6, 6, 0, 1, 1);

    horizontalLayout_3 = new QHBoxLayout();
    horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
    label_3 = new DLabel(AddServiceDialog);
    label_3->setObjectName(QString::fromUtf8("label_3"));

    horizontalLayout_3->addWidget(label_3);

    url = new DLineEdit(AddServiceDialog);
    url->setPlaceholderText("http://baidu.com");
    url->setObjectName(QString::fromUtf8("url"));
    url->lineEdit()->setValidator(urlValidator);

    horizontalLayout_3->addWidget(url);

    gridLayout->addLayout(horizontalLayout_3, 1, 0, 1, 1);

    QWidget::setTabOrder(serviceName, url);
    QWidget::setTabOrder(url, methodCombo);
    QWidget::setTabOrder(methodCombo, requestBody);
    QWidget::setTabOrder(requestBody, checkGap);
    QWidget::setTabOrder(checkGap, comboBox_2);
    QWidget::setTabOrder(comboBox_2, timeoutInSec);

    retranslateUi(AddServiceDialog);

    QMetaObject::connectSlotsByName(AddServiceDialog);
  } // setupUi

  void retranslateUi(DWidget* AddServiceDialog)
  {
    AddServiceDialog->setWindowTitle(
      QCoreApplication::translate("AddServiceDialog", "Form", nullptr));
    label_4->setText(QCoreApplication::translate(
      "AddServiceDialog", "\350\257\267\346\261\202\344\275\223", nullptr));
    label->setText(QCoreApplication::translate(
      "AddServiceDialog", "\345\220\215\347\247\260", nullptr));
    label_2->setText(QCoreApplication::translate(
      "AddServiceDialog", "\346\226\271\346\263\225", nullptr));
    methodCombo->setItemText(
      0, QCoreApplication::translate("AddServiceDialog", "GET", nullptr));
    methodCombo->setItemText(
      1, QCoreApplication::translate("AddServiceDialog", "POST", nullptr));

    label_5->setText(QCoreApplication::translate(
      "AddServiceDialog",
      "\346\243\200\346\237\245\346\226\271\345\274\217",
      nullptr));
    label_9->setText(QCoreApplication::translate(
      "AddServiceDialog", "\351\227\264\351\232\224", nullptr));
    comboBox_2->setItemText(
      0,
      QCoreApplication::translate("AddServiceDialog", "\347\247\222", nullptr));

    label_6->setText(QCoreApplication::translate(
      "AddServiceDialog",
      "\350\266\205\346\227\266\346\227\266\351\227\264",
      nullptr));
    label_7->setText(
      QCoreApplication::translate("AddServiceDialog", "\347\247\222", nullptr));
    label_3->setText(
      QCoreApplication::translate("AddServiceDialog", "URL", nullptr));
  } // retranslateUi
};

namespace Ui {
class AddServiceDialog : public Ui_AddServiceDialog
{};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDSERVICEDIALOG_H
