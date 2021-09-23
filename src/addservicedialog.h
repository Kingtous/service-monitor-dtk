#ifndef ADDSERVICEDIALOG_H
#define ADDSERVICEDIALOG_H

#include <DDialog>

#include <networker/serviceitem.h>

using namespace DTK_WIDGET_NAMESPACE;

namespace Ui {
class AddServiceDialog;
}

class AddServiceDialog : public DDialog {
  Q_OBJECT

public:
  explicit AddServiceDialog(QWidget *parent = nullptr);
  ~AddServiceDialog();

signals:
  void onServiceConfirm(const ServiceItem &item);

private:
  Ui::AddServiceDialog *ui;
  ServiceItem item{};
};

#endif // ADDSERVICEDIALOG_H
