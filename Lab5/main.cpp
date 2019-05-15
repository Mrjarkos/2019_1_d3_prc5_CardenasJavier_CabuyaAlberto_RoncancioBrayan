#include <QApplication>
#include "banco_gui.h"
#include "threaddatos.h"
#include <iostream>

class ThreadDatos;

int main(int argc, char *argv[])
{

  QApplication a(argc, argv);
  banco_gui* interfaz= new banco_gui();
  interfaz->show();

  int r = a.exec();

  //std::cout << "HOLA" << std::endl;
  delete interfaz;
  return r;

}


