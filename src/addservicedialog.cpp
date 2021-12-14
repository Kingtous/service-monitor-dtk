#include <DLog>
#include <DSpinBox>

#include "addservicedialog.h"
#include "ui_addservicedialog.h"

DCORE_USE_NAMESPACE

AddServiceDialog::AddServiceDialog(QWidget* parent)
  : DDialog(parent)
  , ui(new Ui::AddServiceDialog)
{

  this->setTitle("添加服务");
  this->setMessage("请在下方注册你的服务");
  auto content = new QWidget(this);
  ui->setupUi(content);
  this->addContent(content);
  connect(
    ui->serviceName, &DLineEdit::textChanged, this, [&](const QString& text) {
      this->item.setServiceName(text);
      //      dDebug() << text;
    });
  connect(ui->requestBody,
          &DLineEdit::textChanged,
          this,
          [&](const QString& text) { this->item.setBody(text); });
  connect(ui->url, &DLineEdit::textChanged, this, [&](const QString& text) {
    this->item.setUrl(text);
  });
  connect(ui->timeoutInSec,
          QOverload<const QString&>::of(&QSpinBox::valueChanged),
          this,
          [&](const QString& text) { item.setTimeOut(text.toInt()); });
  connect(ui->checkGap, QOverload<const QString&>::of(&QSpinBox::valueChanged), this, [&](const QString& text) {
    item.setCheckGapTimeInSec(text.toInt());
  });
  connect(ui->methodCombo,
          &QComboBox::currentTextChanged,
          this,
          [&](const QString& text) { item.setMethod(text); });
}

AddServiceDialog::AddServiceDialog(const ServiceItem& item, QWidget* parent)
  : AddServiceDialog(parent)
{
  this->ui->serviceName->setText(item.getServiceName());
  this->ui->requestBody->setText(item.getBody());
  this->ui->url->setText(item.getUrl());
  this->ui->timeoutInSec->setValue(item.getTimeOut());
  this->ui->checkGap->setValue(item.getCheckGapTimeInSec());
  this->ui->methodCombo->setCurrentText(item.getMethod());
}

AddServiceDialog::~AddServiceDialog()
{
  delete ui;
}

void
AddServiceDialog::done(int r)
{
  if (r == DDialog::Accepted) {
    DDialog dialog("提示", "");
    dialog.addButton("确定", true);
    if (item.getServiceName().isEmpty()) {
      dialog.setMessage("服务名不能为空");
      dialog.exec();
      return;
    }
    QRegExp exp{ ServiceGroupRepo::instance()->urlRegex };
    if (!exp.exactMatch(item.getUrl())) {
      dialog.setMessage("URL不合法，请检查");
      dialog.exec();
      return;
    }
    // 确认
    emit this->onServiceConfirm(this->item);
  } else {
    DDialog::done(r);
  }
}
