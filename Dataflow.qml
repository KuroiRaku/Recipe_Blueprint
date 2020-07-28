
import QtQuick                   2.8
import QtQuick.Controls          2.1
import QtQuick.Controls.Material 2.1
import QtQuick.Layouts           1.3
import QtQuick.Shapes            1.0

import QuickQanava          2.0 as Qan
import QuickQanava.Samples  1.0
import "qrc:/QuickQanava"   as Qan

ApplicationWindow {
    id: window
    visible: true
    width: 1280; height: 720
    title: "Dataflow sample"
    Pane { anchors.fill: parent }

    Qan.GraphView {
        id: graphView
        anchors.fill: parent
        navigable   : true
        graph: FlowGraph {
            id: graph
            connectorEnabled: true
            Component.onCompleted: {
                defaultEdgeStyle.lineType = Qan.EdgeStyle.Curved

                //var p1 = graph.insertFlowNode(FlowNode.Type.Percentage)
                //p1.label = "Percentage"; p1.item.x = 50; p1.item.y = 50
                //var p2 = graph.insertFlowNode(FlowNode.Type.Percentage)
                //p2.label = "Percentage"; p2.item.x = 50; p2.item.y = 200

                var o1 = graph.insertFlowNode(FlowNode.Type.Processes)
                o1.label = "Operation"; o1.item.x = 300; o1.item.y = 125
                var o1InPort1 = o1.item.findPort("IN1")
                var o1InPort2 = o1.item.findPort("IN2")
                var o1OutPort = o1.item.findPort("OUT")

                //var p1OutPort = p1.item.findPort("OUT")
                //var p2OutPort = p2.item.findPort("OUT")
                var e = graph.insertEdge(p1, o1)
                graph.bindEdge(e, p1OutPort, o1InPort1)
                e = graph.insertEdge(p2, o1)
                graph.bindEdge(e, p2OutPort, o1InPort2)



                var c1 = graph.insertFlowNode(FlowNode.Type.Ingredient)
                c1.label = "Ingredient"; c1.item.x = 300; c1.item.y = 300
                var c1OutPort = c1.item.findPort("OUT")

                var i1 = graph.insertFlowNode(FlowNode.Type.Ingredient)
                i1.label = "Image"; i1.item.x = 300; i1.item.y = 450
                var i1OutPort = i1.item.findPort("OUT")

                var t1 = graph.insertFlowNode(FlowNode.Type.Tint)
                t1.label = "Tint"; t1.item.x = 600; t1.item.y = 250
                var t1InFactor = t1.item.findPort("FACTOR")
                var t1InColor = t1.item.findPort("COLOR")
                var t1InImage = t1.item.findPort("IMAGE")

                e = graph.insertEdge(o1, t1)
                graph.bindEdge(e, o1OutPort, t1InFactor)
                e = graph.insertEdge(c1, t1)
                graph.bindEdge(e, c1OutPort, t1InColor)
                e = graph.insertEdge(i1, t1)
                graph.bindEdge(e, i1OutPort, t1InImage)
            }
        }
    }  // Qan.GraphView

    Pane { x: menu.x; y: menu.y; width: menu.width; height: menu.height; opacity: 0.8 } // Pane: menu transparent background
    RowLayout  {
        id: menu
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top; anchors.topMargin: 4
        ToolButton {
            text: "%"
            onClicked: {
                var r = graph.insertFlowNode(FlowNode.Type.Percentage)
                r.label = "Percentage"
            }
        }
        ToolButton {
            text: "+/*"
            font.bold: true
            onClicked: {
                var r = graph.insertFlowNode(FlowNode.Type.Operation)
                r.label = "Operation"
            }
        }
        ToolButton {
            text: "Img"
            font.bold: true
            onClicked: graph.insertFlowNode(FlowNode.Type.Image)
        }
        ToolButton {
            text: "Col"
            font.bold: true
            onClicked: {
                var r = graph.insertFlowNode(FlowNode.Type.Color)
                r.label = "Color"
            }
        }
        ToolButton {
            text: "Tint"
            font.bold: true
            onClicked: {
                var r = graph.insertFlowNode(FlowNode.Type.Tint)
                r.label = "Tint"
            }
        }
    }
    Label {
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        text: "When creating new processing nodes, connect output to input from top to bottom \n this is just a code sample, not a ful fledged flow engine"
        color: "red"
    }
}


