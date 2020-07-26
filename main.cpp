

#include <QtWidgets/QApplication>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QMenuBar>


//for this to get detected, check out the changes in .pro file on QT +=...
#include <QGuiApplication>
#include <QtQml>
#include <QQuickStyle>

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
