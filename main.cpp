#include "mainwindow.h"
#include "connectwidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    ConnectWidget connect;


        connect.show();
    //w.show();
    return a.exec();
}
