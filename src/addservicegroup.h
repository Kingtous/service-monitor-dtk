#ifndef ADDSERVICEGROUP_H
#define ADDSERVICEGROUP_H

#include <DDialog>
#include <DWidget>

DWIDGET_USE_NAMESPACE

namespace Ui {
class AddServiceGroup;
}

class AddServiceGroup : public DDialog
{
  Q_OBJECT

public:
  explicit AddServiceGroup(DWidget* parent = nullptr);
  ~AddServiceGroup();

private:
  Ui::AddServiceGroup* ui;
};

#endif // ADDSERVICEGROUP_H
