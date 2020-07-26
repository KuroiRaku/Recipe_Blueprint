

#include <QtWidgets/QApplication>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QMenuBar>


#include <QGuiApplication>
#include <QtQml>

// QuickQanava headers
#include <QuickQanava.h>


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
