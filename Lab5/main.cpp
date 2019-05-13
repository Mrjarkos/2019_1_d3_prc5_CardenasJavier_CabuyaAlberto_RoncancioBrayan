#include <QApplication>
#include "banco_gui.h"
#include "threaddatos.h"

class ThreadDatos;

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  banco_gui* interfaz= new banco_gui();
  interfaz->show();

  return a.exec();
}
