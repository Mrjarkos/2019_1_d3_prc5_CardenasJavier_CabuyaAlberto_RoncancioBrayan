#ifndef BANCO_GUI_H
#define BANCO_GUI_H

#include <QMainWindow>

namespace Ui {
class banco_gui;
}

class banco_gui : public QMainWindow
{
    Q_OBJECT

public:
    explicit banco_gui(QWidget *parent = 0);
    ~banco_gui();

private:
    Ui::banco_gui *ui;
};

#endif // BANCO_GUI_H
