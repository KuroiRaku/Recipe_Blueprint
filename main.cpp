#include "mainwindow.h"
#include "connectwidget.h"
#include <QApplication>

#include <nodes/NodeData>
#include <nodes/FlowScene>
#include <nodes/FlowView>
#include <nodes/ConnectionStyle>
#include <nodes/TypeConverter>
#include <nodes/DataModelRegistry>

using QtNodes::DataModelRegistry;
using QtNodes::FlowScene;
using QtNodes::FlowView;
using QtNodes::ConnectionStyle;
//using QtNodes::TypeConverter;
using QtNodes::TypeConverterId;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    ConnectWidget connect;


        connect.show();
    //w.show();
    return a.exec();
}
