#ifndef THREADINGRESARCLIENTES_H
#define THREADINGRESARCLIENTES_H

#include <QObject>

class ThreadIngresarClientes : public QThread
{
    Q_OBJECT
public:
    explicit ThreadIngresarClientes(QObject *parent = nullptr);

protected:
    void run();
signals:
    void signal(int);

public slots:
};

#endif // THREADINGRESARCLIENTES_H
