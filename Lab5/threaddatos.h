#ifndef THREADDATOS_H
#define THREADDATOS_H

#include <QObject>
#include "banco_gui.h"


class ThreadDatos : public QThread
{
    Q_OBJECT
public:
    explicit ThreadDatos(QObject *parent = 0);

protected:
    void run();
signals:
    void signal(int);
public slots:
};

#endif // THREADDATOS_H
