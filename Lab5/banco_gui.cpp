#include "banco_gui.h"
#include "ui_banco_gui.h"
#include "operation_bank.h"
#include "threaddatos.h"
#include <iostream>

banco_gui::banco_gui(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::banco_gui)
{
    ui->setupUi(this);
    //signal(SIGINT,sigint);
    N_Cajeros = 2;
    Bank = new Operation_Bank(N_Cajeros);
    if(Bank->Crear_Memoria_Compartida()){
        QMessageBox::information(this, "Error", "Banco ya abierto");
        delete Bank;
        delete ui;
    }

    configurar_interfaz(N_Cajeros);
    Datos = new ThreadDatos(this);
    Datos->start(QThread::HighPriority);
    connect(Datos, &ThreadDatos::signal, [&](int n){
        this->Actualizar_Datos();
    });
    Bank->R_Mem();
    Bank->A_Cli();
}

banco_gui::~banco_gui()
{
    delete Bank;
    delete ui;
}

void banco_gui::sigint(int a){
        delete this;
    }

void banco_gui::configurar_interfaz(int N_Cajeros){
    int Col2=0;
    QPixmap kranklogo(":/Images/Kranks-Bank.png");
    QPixmap Cajeros(":/Images/Cajero.jpg");
    QLabel *Cajero_label[N_Cajeros];
    QLabel *Estado_Cajero_label[N_Cajeros];

    if(N_Cajeros>5){
        Col2 = N_Cajeros-5;
        N_Cajeros=5;
    }

    int cajero_h = H_Screen/3-2*Margin_Y;
    int cajero_w = (W_Screen*2)/(3*5)-2*Margin_X; //W_Screen*(2/3)*(1/5)-Margin_X;
    int cajero_x = ((W_Screen*2)/3-cajero_w*N_Cajeros)/2;
    int cajero_y = ((H_Screen*2)/3-cajero_h*5)/2;
    int krank_label_w = (W_Screen*2)/(3*3)-2*Margin_X;// W_Screen*(2/3)*(1/3)-2*Margin_X;
    int krank_label_h = H_Screen/3-2*Margin_Y;
    int nombre_label_w = (W_Screen*4)/(3*3)-3*Margin_X;
    int nombre_label_h = H_Screen/3-4*Margin_Y;

    this->setFixedSize(W_Screen, H_Screen+20);
    ui->Krank_label->setGeometry(Margin_X*6, Margin_Y/2, krank_label_w, krank_label_h);
    ui->Krank_label->setPixmap(kranklogo.scaled(krank_label_w, krank_label_h, Qt::KeepAspectRatio));

    QLabel* Nombre = new QLabel(this);
    Nombre->setGeometry(Margin_X*8 + krank_label_w, Margin_Y, nombre_label_w, nombre_label_h);
    Nombre->setText(Bank_name);
    QFont font("Impact", 60);
    Nombre->setFont(font);

    for(int i=0; i<N_Cajeros; i++){
        Cajero_label[i] = new QLabel(this);
        Cajero_label[i]->setGeometry(cajero_x+(cajero_w+cajero_x/2)*i, cajero_y+(H_Screen*2)/3-Margin_Y, cajero_w, cajero_h);
        Cajero_label[i]->setPixmap(Cajeros.scaled(cajero_w, cajero_h, Qt::KeepAspectRatio));
    }

    N_Cajeros = Col2;
    cajero_x = ((W_Screen*2)/3-cajero_w*N_Cajeros)/2;

    for(int i=0; i<N_Cajeros; i++){
        Cajero_label[i] = new QLabel(this);
        Cajero_label[i]->setGeometry(cajero_x+(cajero_w+cajero_x/2)*i, cajero_y+H_Screen, cajero_w, cajero_h);
        Cajero_label[i]->setPixmap(Cajeros.scaled(cajero_w, cajero_h, Qt::KeepAspectRatio));
    }

    QLabel *static_Text[8];
    QFont font_Static("Arial", 14);
    for(int i=0; i<8; i++){
       static_Text[i] = new QLabel(this);
       static_Text[i]->setGeometry((W_Screen*3)/4+Margin_X, Margin_Y+(H_Screen/32)*(i+1), W_Screen/3-Margin_X*2, 20);
       static_Text[i]->setFont(font_Static);
    }

    static_Text[0]->setText("Buffer Size = ");
    static_Text[1]->setText("Buffer in = ");
    static_Text[2]->setText("Buffer out = ");
    static_Text[3]->setText("Clientes en Espera:");

    for(int i=4; i<8; i++){
       static_Text[i]->setGeometry((W_Screen*3)/4+Margin_X, (H_Screen/3)+Margin_Y+(H_Screen/32)*(i+2), W_Screen/3-Margin_X*2, 20);
    }

    static_Text[4]->setText("Cajeros Abiertos = ");
    static_Text[5]->setText("Cajeros Libres = ");
    static_Text[6]->setText("Cajeros Ocupados = ");
    static_Text[7]->setText("Estado de Cajeros:");

    label_buffer = new QLabel(this);
    label_buffer->setGeometry((W_Screen*9)/10+Margin_X, Margin_Y+(H_Screen/32), W_Screen/3-Margin_X*2, 20);
    label_buffer->setFont(font_Static);

    label_in = new QLabel(this);
    label_in->setGeometry((W_Screen*9)/10+Margin_X, Margin_Y+(H_Screen/32)*2, W_Screen/3-Margin_X*2, 20);
    label_in->setFont(font_Static);

    label_out = new QLabel(this);
    label_out->setGeometry((W_Screen*9)/10+Margin_X, Margin_Y+(H_Screen/32)*3, W_Screen/3-Margin_X*2, 20);
    label_out->setFont(font_Static);

    ui->BufferClient_Widget->setGeometry((W_Screen*6)/8+Margin_X, Margin_Y+(H_Screen/32)*5,(W_Screen*3)/14, 250);

    label_cajeros_abiertos = new QLabel(this);
    label_cajeros_abiertos->setGeometry((W_Screen*9)/10+Margin_X, (H_Screen/3)+Margin_Y+(H_Screen/32)*6, W_Screen/3-Margin_X*2, 20);
    label_cajeros_abiertos->setFont(font_Static);

    label_cajeros_libres = new QLabel(this);
    label_cajeros_libres->setGeometry((W_Screen*9)/10+Margin_X, (H_Screen/3)+Margin_Y+(H_Screen/32)*7, W_Screen/3-Margin_X*2, 20);
    label_cajeros_libres->setFont(font_Static);

    label_cajeros_ocupados  = new QLabel(this);
    label_cajeros_ocupados->setGeometry((W_Screen*9)/10+Margin_X, (H_Screen/3)+Margin_Y+(H_Screen/32)*8, W_Screen/3-Margin_X*2, 20);
    label_cajeros_ocupados->setFont(font_Static);

    ui->BufferCajeros_Widget->setGeometry((W_Screen*6)/8+Margin_X, (H_Screen/3)+Margin_Y+(H_Screen/32)*10, (W_Screen*3)/14, 250);
    cajero_clientes = Bank->cajero_clientes;
}

void banco_gui::Actualizar_Datos(){
    //Actualizar datos

    ui->BufferClient_Widget->clear();
    ui->BufferCajeros_Widget->clear();
    in = Bank->in;
    out = Bank->out;
    freecash = Bank->freecash;

    label_buffer->setText(QString::number(BUFFER_SIZE));
    label_in->setText(QString::number(in));
    label_out->setText(QString::number(out));
    label_cajeros_abiertos->setText(QString::number(N_Cajeros));
    label_cajeros_libres->setText(QString::number(freecash));
    label_cajeros_ocupados->setText(QString::number(N_Cajeros - freecash));
    buffer_clientes = Bank->buffer_clientes;
    //ui->BufferClient_Widget->reset();
    char* cadena = new char[150];
    for(int i = out; i<in; i=(i+1)%BUFFER_SIZE){
        sprintf(cadena, "[%i] Nombre = %s, Id = %s", i-out+1, buffer_clientes[i].name_client, buffer_clientes[i].id_client);
        ui->BufferClient_Widget->addItem(cadena);
    }

     cajero_clientes = Bank->cajero_clientes;
     for(int i = 0; i<N_Cajeros; i++){
         if(cajero_clientes[i].pid_client!=NULL){
           sprintf(cadena, "[%i] Nombre = %s, Id = %s", i+1, cajero_clientes[i].name_client, cajero_clientes[i].id_client);
         }else{
           sprintf(cadena, "[%i] Cajero Disponible", i+1);
         }
         ui->BufferCajeros_Widget->addItem(cadena);
     }
  // usleep(1000*100);
}

void banco_gui::Ingresar_clientes(){

}
