#include "mainframe.h"

#include <QHBoxLayout>

MainFrame::MainFrame(QWidget *parent) : QWidget(parent)
{
    this->initUi();
}

void MainFrame::initUi()
{
    // panel <-> frame
    auto hlayout = new QHBoxLayout(this);
    hlayout->setMargin(16);




}
