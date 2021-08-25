#ifndef MAINFRAME_H
#define MAINFRAME_H

#include <QObject>
#include <QWidget>

class mainframe : public QWidget
{
    Q_OBJECT
public:
    explicit mainframe(QWidget *parent = nullptr);

signals:

public slots:
};

#endif // MAINFRAME_H