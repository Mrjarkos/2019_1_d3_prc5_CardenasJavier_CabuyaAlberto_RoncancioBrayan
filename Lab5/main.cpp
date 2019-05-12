#include "banco_gui.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    banco_gui w;
    w.show();

    return a.exec();
}
