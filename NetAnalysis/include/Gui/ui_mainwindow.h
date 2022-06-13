/********************************************************************************
** Form generated from reading UI file 'mainwindowscbLRc.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef MAINWINDOWSCBLRC_H
#define MAINWINDOWSCBLRC_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>
#include <iostream>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionOpen_Graph;
    QAction *actionCalculateBtw;
    QWidget *centralwidget;
    QMenuBar *menubar;
    QMenu *menuFile;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        actionOpen_Graph = new QAction(MainWindow);
        actionOpen_Graph->setObjectName(QString::fromUtf8("actionOpen_Graph"));
        actionCalculateBtw = new QAction(MainWindow);
        actionCalculateBtw->setObjectName(QString::fromUtf8("actionCalculateBtw"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 21));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuFile->menuAction());
        menuFile->addAction(actionOpen_Graph);

        retranslateUi(MainWindow);
        QObject::connect(actionOpen_Graph, SIGNAL(toggled(bool)), actionCalculateBtw, SLOT(toggle()));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        actionOpen_Graph->setText(QCoreApplication::translate("MainWindow", "Open Graph", nullptr));
        actionCalculateBtw->setText(QCoreApplication::translate("MainWindow", "CalculateBtw", nullptr));
        menuFile->setTitle(QCoreApplication::translate("MainWindow", "File", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {
    public:
        void setupUi(QMainWindow* MainWindow) 
        {
            Ui_MainWindow::setupUi(MainWindow);
            actionCalculateBtw->connect(actionCalculateBtw, QAction::toggle, CalculateBtw);
        }
    private slots:

        void CalculateBtw()
        {
            std::cout << "Calculus Enabled" << std::endl;
        }
    
    };
} // namespace Ui

QT_END_NAMESPACE

#endif // MAINWINDOWSCBLRC_H
