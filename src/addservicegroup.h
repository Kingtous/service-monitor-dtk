#ifndef ADDSERVICEGROUP_H
#define ADDSERVICEGROUP_H

#include <QDialog>

namespace Ui {
class AddServiceGroup;
}

class AddServiceGroup : public QDialog
{
    Q_OBJECT

public:
    explicit AddServiceGroup(QWidget *parent = nullptr);
    ~AddServiceGroup();

private:
    Ui::AddServiceGroup *ui;
};

#endif // ADDSERVICEGROUP_H
