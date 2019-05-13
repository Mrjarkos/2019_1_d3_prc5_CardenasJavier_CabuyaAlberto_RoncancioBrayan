#include "threadingresarclientes.h"

ThreadIngresarClientes::ThreadIngresarClientes(QObject *parent) :  QThread(parent)
{

}

void ThreadDatos::run(){
    while (1) {
       emit signal(0);
    }
}
