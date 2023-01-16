/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;
    QDockWidget *leftDock;
    QWidget *leftDockWidgetContents;
    QDockWidget *boardDock;
    QWidget *boardDockWidgetContents;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(700, 464);
        MainWindow->setMinimumSize(QSize(0, 0));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 700, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);
        leftDock = new QDockWidget(MainWindow);
        leftDock->setObjectName(QString::fromUtf8("leftDock"));
        leftDock->setMinimumSize(QSize(200, 30));
        leftDock->setFloating(false);
        leftDockWidgetContents = new QWidget();
        leftDockWidgetContents->setObjectName(QString::fromUtf8("leftDockWidgetContents"));
        leftDock->setWidget(leftDockWidgetContents);
        MainWindow->addDockWidget(Qt::RightDockWidgetArea, leftDock);
        boardDock = new QDockWidget(MainWindow);
        boardDock->setObjectName(QString::fromUtf8("boardDock"));
        boardDock->setMinimumSize(QSize(450, 420));
        boardDock->setMaximumSize(QSize(450, 420));
        boardDockWidgetContents = new QWidget();
        boardDockWidgetContents->setObjectName(QString::fromUtf8("boardDockWidgetContents"));
        boardDock->setWidget(boardDockWidgetContents);
        MainWindow->addDockWidget(Qt::LeftDockWidgetArea, boardDock);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        leftDock->setWindowTitle(QCoreApplication::translate("MainWindow", "Previous moves", nullptr));
        boardDock->setWindowTitle(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
