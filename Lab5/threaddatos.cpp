#include "threaddatos.h"
#include "banco_gui.h"

ThreadDatos::ThreadDatos(QObject *parent) : QThread(parent)
{

}

void ThreadDatos::run(){
    while (1) {
       emit signal(0);
    }
}
