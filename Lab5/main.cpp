#include <QApplication>
#include "banco_gui.h"
#include "threaddatos.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

class ThreadDatos;

int main(int argc, char *argv[])
{
    int N_cajeros;
    if(argc == 1){
        N_cajeros = 2;
    }else if(argc == 2){
        std::cout << "(int)*argv[1] = " << std::atoi(argv[1])<< std::endl;
        if(std::atoi(argv[1]) > 10){
            std::cout << "Error argumentos invalidos\nFormato ./Lab5 'NCajeros' " << std::endl;
            std::cout << "Numero maximo de cajeros 10" << std::endl;
            return 0;
        }
        N_cajeros = std::atoi(argv[1]);
    }else{
        std::cout << "Numero invalido de argumentos\nFormato ./Lab5 'NCajeros' " << std::endl;
        return 0;
    }

  QApplication a(argc, argv);
  banco_gui* interfaz= new banco_gui();
  interfaz->inicializacion(N_cajeros);
  interfaz->show();

  int r = a.exec();

  //std::cout << "HOLA" << std::endl;
  delete interfaz;
  return r;

}


