#include <DSpinBox>

#include "addservicedialog.h"
#include "ui_addservicedialog.h"

AddServiceDialog::AddServiceDialog(QWidget *parent)
    : DDialog(parent), ui(new Ui::AddServiceDialog) {

  this->setTitle("添加服务");
  this->setMessage("请在下方注册你的服务");
  auto content = new QWidget(this);
  ui->setupUi(content);
  this->addContent(content);
  connect(ui->serviceName, &QLineEdit::textChanged, this,
          [&](const QString &text) { this->item.setServiceName(text); });
  connect(ui->requestBody, &QLineEdit::textChanged, this,
          [&](const QString &text) { this->item.setBody(text); });
  connect(ui->url, &QLineEdit::textChanged, this,
          [&](const QString &text) { this->item.setUrl(text); });
  connect(ui->timeoutInSec, &QSpinBox::textChanged, this,
          [&](const QString &text) { item.setTimeOut(text.toInt()); });
  connect(ui->checkGap, &QSpinBox::textChanged, this, [&](const QString &text) {
    item.setCheckGapTimeInSec(text.toInt());
  });
  connect(ui->methodCombo, &QComboBox::textActivated, this,
          [&](const QString &text) { item.setMethod(text); });
  connect(this, &DDialog::accepted, this,
          [this]() { emit this->onServiceConfirm(this->item); });
}

AddServiceDialog::AddServiceDialog(const ServiceItem &item, QWidget *parent)
    : AddServiceDialog(parent) {
  this->ui->serviceName->setText(item.getServiceName());
  this->ui->requestBody->setText(item.getBody());
  this->ui->url->setText(item.getUrl());
  this->ui->timeoutInSec->setValue(item.getTimeOut());
  this->ui->checkGap->setValue(item.getCheckGapTimeInSec());
  this->ui->methodCombo->setCurrentText(item.getMethod());
}

AddServiceDialog::~AddServiceDialog() { delete ui; }
