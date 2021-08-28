#include "addservicedialog.h"
#include "ui_addservicedialog.h"

AddServiceDialog::AddServiceDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddServiceDialog)
{
    ui->setupUi(this);
}

AddServiceDialog::~AddServiceDialog()
{
    delete ui;
}
