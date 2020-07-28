

#include <QtWidgets/QApplication>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QMenuBar>


//for this to get detected, check out the changes in .pro file on QT +=...
#include <QGuiApplication>
#include <QtQml>
#include <QQuickStyle>

// QuickQanava headers
#include <QuickQanava.h>

#include <QuickQanava>

#include "dataflow.h"


#include "mainwindow.h"
#include "connectwidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    /*
    QApplication a(argc, argv);
    MainWindow w;
    ConnectWidget connect;


    connect.show();
    return a.exec();
    */
    QGuiApplication app(argc, argv);
    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QQuickStyle::setStyle("Material");
    QQmlApplicationEngine engine;
    engine.addPluginPath(QStringLiteral("Vendor/QuickQanava/src")); // Necessary only for development when plugin is not installed to QTDIR/qml
    QuickQanava::initialize(&engine);
    qmlRegisterType< qan::FlowNode >( "QuickQanava.Samples", 1, 0, "FlowNode");
    qmlRegisterType< qan::ProcessesNode >( "QuickQanava.Samples", 1, 0, "ProcessesNode");
    qmlRegisterType< qan::FlowGraph >( "QuickQanava.Samples", 1, 0, "FlowGraph");

    engine.load(QUrl("qrc:/dataflow.qml"));
    return app.exec();

    //w.show();

}
