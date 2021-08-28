#ifndef ADDSERVICEDIALOG_H
#define ADDSERVICEDIALOG_H

#include "serviceitem.h"

#include <QWidget>

namespace Ui {
class AddServiceDialog;
}

class AddServiceDialog : public QWidget {
  Q_OBJECT

public:
  explicit AddServiceDialog(QWidget *parent = nullptr);
  ~AddServiceDialog();

signals:
  void onServiceConfirm(ServiceItem item);

private:
  Ui::AddServiceDialog *ui;
};

#endif // ADDSERVICEDIALOG_H
