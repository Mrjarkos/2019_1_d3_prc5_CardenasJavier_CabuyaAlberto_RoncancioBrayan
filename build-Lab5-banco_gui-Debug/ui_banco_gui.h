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
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_banco_gui
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *banco_gui)
    {
        if (banco_gui->objectName().isEmpty())
            banco_gui->setObjectName(QStringLiteral("banco_gui"));
        banco_gui->resize(400, 300);
        menuBar = new QMenuBar(banco_gui);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        banco_gui->setMenuBar(menuBar);
        mainToolBar = new QToolBar(banco_gui);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        banco_gui->addToolBar(mainToolBar);
        centralWidget = new QWidget(banco_gui);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        banco_gui->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(banco_gui);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        banco_gui->setStatusBar(statusBar);

        retranslateUi(banco_gui);

        QMetaObject::connectSlotsByName(banco_gui);
    } // setupUi

    void retranslateUi(QMainWindow *banco_gui)
    {
        banco_gui->setWindowTitle(QApplication::translate("banco_gui", "banco_gui", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class banco_gui: public Ui_banco_gui {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BANCO_GUI_H
