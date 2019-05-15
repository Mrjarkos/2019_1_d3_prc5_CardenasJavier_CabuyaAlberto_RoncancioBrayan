#ifndef BANCO_GUI_H
#define BANCO_GUI_H

#include <QMainWindow>
#include <QPixmap>
#include <QtCore>
#include <QtGui>
#include <QMessageBox>
#include <signal.h>
#include "operation_bank.h"


#define H_Screen 800//563
#define W_Screen 1300//1000

#define Margin_X 20
#define Margin_Y 30

class ThreadDatos;

namespace Ui {
class banco_gui;
}

class banco_gui : public QMainWindow
{
    Q_OBJECT

public:
    explicit banco_gui(QWidget *parent = 0);
    ~banco_gui();
    void configurar_interfaz(int N_Cajeros);
    void Actualizar_Datos();
    void Ingresar_clientes();
    int N_Cajeros;
    const char* Bank_name = "Kranks Bank!";
    QLabel* Cajero_label_Estado[10];
    QLabel* Cliente_label_Estado[10];

private:
    Ui::banco_gui *ui;
    int freecash;

    volatile int in, out, clientes_banco;
    client* buffer_clientes;
    client* cajero_clientes;
    QLabel* label_buffer;
    QLabel* label_in;
    QLabel* label_out;
    QLabel* label_cajeros_abiertos;
    QLabel* label_cajeros_libres;
    QLabel* label_cajeros_ocupados;
    //QLabel* Cajero_label_Estado[N_Cajeros];
    Operation_Bank* Bank;
    ThreadDatos* Datos;

    void sigint(int a);

};
#endif // BANCO_GUI_H
