/********************************************************************************
** Form generated from reading UI file 'banco_gui.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BANCO_GUI_H
#define UI_BANCO_GUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_banco_gui
{
public:
    QWidget *centralWidget;
    QLabel *Krank_label;
    QListWidget *BufferClient_Widget;
    QListWidget *BufferCajeros_Widget;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *banco_gui)
    {
        if (banco_gui->objectName().isEmpty())
            banco_gui->setObjectName(QStringLiteral("banco_gui"));
        banco_gui->resize(481, 375);
        centralWidget = new QWidget(banco_gui);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        Krank_label = new QLabel(centralWidget);
        Krank_label->setObjectName(QStringLiteral("Krank_label"));
        Krank_label->setGeometry(QRect(30, 20, 191, 141));
        BufferClient_Widget = new QListWidget(centralWidget);
        BufferClient_Widget->setObjectName(QStringLiteral("BufferClient_Widget"));
        BufferClient_Widget->setGeometry(QRect(290, -10, 181, 192));
        BufferCajeros_Widget = new QListWidget(centralWidget);
        BufferCajeros_Widget->setObjectName(QStringLiteral("BufferCajeros_Widget"));
        BufferCajeros_Widget->setGeometry(QRect(270, 190, 256, 192));
        banco_gui->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(banco_gui);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 481, 22));
        banco_gui->setMenuBar(menuBar);
        mainToolBar = new QToolBar(banco_gui);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        banco_gui->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(banco_gui);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        banco_gui->setStatusBar(statusBar);

        retranslateUi(banco_gui);

        QMetaObject::connectSlotsByName(banco_gui);
    } // setupUi

    void retranslateUi(QMainWindow *banco_gui)
    {
        banco_gui->setWindowTitle(QApplication::translate("banco_gui", "banco_gui", Q_NULLPTR));
        Krank_label->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class banco_gui: public Ui_banco_gui {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BANCO_GUI_H
