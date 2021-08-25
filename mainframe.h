#ifndef MAINFRAME_H
#define MAINFRAME_H

#include <QObject>
#include <QWidget>

class MainFrame : public QWidget
{
    Q_OBJECT
public:
    explicit MainFrame(QWidget *parent = nullptr);

signals:


private:
    void initUi();

public slots:
};

#endif // MAINFRAME_H
