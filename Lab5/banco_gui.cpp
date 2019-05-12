#include "banco_gui.h"
#include "ui_banco_gui.h"

banco_gui::banco_gui(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::banco_gui)
{
    ui->setupUi(this);
}

banco_gui::~banco_gui()
{
    delete ui;
}
