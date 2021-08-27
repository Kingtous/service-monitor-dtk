#include "addservicegroup.h"
#include "ui_addservicegroup.h"

AddServiceGroup::AddServiceGroup(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddServiceGroup)
{
    ui->setupUi(this);
}

AddServiceGroup::~AddServiceGroup()
{
    delete ui;
}
