#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setFixedWidth(700);
    w.setFixedHeight(440);
    w.show();
    return a.exec();
}
