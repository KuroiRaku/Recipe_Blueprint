import QtQuick              2.7
import QtQuick.Controls     2.0
import QtQuick.Layouts      1.3
import QtGraphicalEffects   1.0

import QuickQanava          2.0 as Qan
import "qrc:/QuickQanava"   as Qan
import QuickQanava.Samples  1.0

Qan.NodeItem {
    id: operationNodeItem
    Layout.preferredWidth: 150
    Layout.preferredHeight: 70
    width: Layout.preferredWidth
    height: Layout.preferredHeight
    connectable: Qan.NodeItem.UnConnectable // Do not show visual edge connector, use out port instead

    Connections {       // Observe "node item" "node" ouput value changes andupdate out port label
        target: node
        onOutputChanged: {
            if ( ports.itemCount > 0 )
                ports.listReference.itemAt(0).label = "OUT=" + node.output.toFixed(1)
        }
    }

    Qan.RectNodeTemplate {
        anchors.fill: parent
        nodeItem : parent
        ComboBox {
            anchors.left: parent.left;
            anchors.right: parent.right
            anchors.verticalCenter: parent.verticalCenter
            anchors.margins: 4
            model: [ "frying", "* operator"]
            currentIndex: node.operation === OperationNode.Add ? 0 : 1
            onCurrentIndexChanged: {
                node.operation = currentIndex === 0 ? OperationNode.Add : OperationNode.Multiply
            }
        }
    }

}
