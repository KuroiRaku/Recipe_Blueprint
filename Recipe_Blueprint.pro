QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

#include(nodes/Connection)

SOURCES += \
    QtNodeEditor-master/examples/example2/TextDisplayDataModel.cpp \
    QtNodeEditor-master/examples/example2/TextSourceDataModel.cpp \
    QtNodeEditor-master/examples/example2/main.cpp \
    QtNodeEditor-master/src/Connection.cpp \
    QtNodeEditor-master/src/ConnectionBlurEffect.cpp \
    QtNodeEditor-master/src/ConnectionGeometry.cpp \
    QtNodeEditor-master/src/ConnectionGraphicsObject.cpp \
    QtNodeEditor-master/src/ConnectionPainter.cpp \
    QtNodeEditor-master/src/ConnectionState.cpp \
    QtNodeEditor-master/src/ConnectionStyle.cpp \
    QtNodeEditor-master/src/DataModelRegistry.cpp \
    QtNodeEditor-master/src/FlowScene.cpp \
    QtNodeEditor-master/src/FlowView.cpp \
    QtNodeEditor-master/src/FlowViewStyle.cpp \
    QtNodeEditor-master/src/Node.cpp \
    QtNodeEditor-master/src/NodeConnectionInteraction.cpp \
    QtNodeEditor-master/src/NodeDataModel.cpp \
    QtNodeEditor-master/src/NodeGeometry.cpp \
    QtNodeEditor-master/src/NodeGraphicsObject.cpp \
    QtNodeEditor-master/src/NodePainter.cpp \
    QtNodeEditor-master/src/NodeState.cpp \
    QtNodeEditor-master/src/NodeStyle.cpp \
    QtNodeEditor-master/src/Properties.cpp \
    QtNodeEditor-master/src/StyleCollection.cpp \
    connectwidget.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    QtNodeEditor-master/examples/example2/TextData.hpp \
    QtNodeEditor-master/examples/example2/TextDisplayDataModel.hpp \
    QtNodeEditor-master/examples/example2/TextSourceDataModel.hpp \
    QtNodeEditor-master/src/ConnectionBlurEffect.hpp \
    QtNodeEditor-master/src/ConnectionPainter.hpp \
    QtNodeEditor-master/src/NodeConnectionInteraction.hpp \
    QtNodeEditor-master/src/NodePainter.hpp \
    QtNodeEditor-master/src/Properties.hpp \
    QtNodeEditor-master/src/StyleCollection.hpp \
    connectwidget.h \
    mainwindow.h \
    nodes/internal/Compiler.hpp \
    nodes/internal/Connection.hpp \
    nodes/internal/ConnectionGeometry.hpp \
    nodes/internal/ConnectionGraphicsObject.hpp \
    nodes/internal/ConnectionState.hpp \
    nodes/internal/ConnectionStyle.hpp \
    nodes/internal/DataModelRegistry.hpp \
    nodes/internal/Export.hpp \
    nodes/internal/FlowScene.hpp \
    nodes/internal/FlowView.hpp \
    nodes/internal/FlowViewStyle.hpp \
    nodes/internal/Node.hpp \
    nodes/internal/NodeData.hpp \
    nodes/internal/NodeDataModel.hpp \
    nodes/internal/NodeGeometry.hpp \
    nodes/internal/NodeGraphicsObject.hpp \
    nodes/internal/NodePainterDelegate.hpp \
    nodes/internal/NodeState.hpp \
    nodes/internal/NodeStyle.hpp \
    nodes/internal/OperatingSystem.hpp \
    nodes/internal/PortType.hpp \
    nodes/internal/QStringStdHash.hpp \
    nodes/internal/QUuidStdHash.hpp \
    nodes/internal/Serializable.hpp \
    nodes/internal/Style.hpp \
    nodes/internal/TypeConverter.hpp \
    nodes/internal/memory.hpp

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    QtNodeEditor-master/resources/resources.qrc \
    resources.qrc
