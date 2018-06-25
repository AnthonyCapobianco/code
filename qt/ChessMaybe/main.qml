import QtQuick 2.9
import QtQuick.Window 2.2

Window {
    visible: true
    width: 480
    height: 480
    property alias grid: grid
    title: qsTr("Chess")

    Grid {
        id: grid
        anchors.fill: parent
        rows: 8
        columns: 8

        Rectangle {
            id: rectangle
            width: 60
            height: 60
            color: "#ffffff"
            border.width: 0
            border.color: "#00000000"
            anchors.left: parent.left
            anchors.leftMargin: 0
            anchors.top: parent.top
            anchors.topMargin: 0
        }

        Rectangle {
            id: rectangle1
            y: 0
            width: 60
            height: 60
            color: "#272121"
            anchors.left: rectangle.right
            anchors.leftMargin: 0
            border.width: 0
            border.color: "#00000000"
        }

        Rectangle {
            id: rectangle2
            y: 0
            width: 60
            height: 60
            color: "#ffffff"
            anchors.left: rectangle1.right
            anchors.leftMargin: -120
            border.color: "#00000000"
            border.width: 0
        }

        Rectangle {
            id: rectangle3
            y: 0
            width: 60
            height: 60
            color: "#272121"
            anchors.left: rectangle2.right
            anchors.leftMargin: 120
            border.color: "#00000000"
            border.width: 0
        }

        Rectangle {
            id: rectangle4
            y: 0
            width: 60
            height: 60
            color: "#ffffff"
            anchors.left: rectangle3.right
            anchors.leftMargin: 0
            border.color: "#00000000"
            border.width: 0
        }

        Rectangle {
            id: rectangle5
            y: 0
            width: 60
            height: 60
            color: "#272121"
            border.color: "#00000000"
            border.width: 0
            anchors.left: rectangle4.right
            anchors.leftMargin: 0
        }

        Rectangle {
            id: rectangle6
            y: 0
            width: 60
            height: 60
            color: "#ffffff"
            border.color: "#00000000"
            border.width: 0
            anchors.left: rectangle5.right
            anchors.leftMargin: 0
        }

        Rectangle {
            id: rectangle7
            y: 0
            width: 60
            height: 60
            color: "#272121"
            border.color: "#00000000"
            border.width: 0
            anchors.left: rectangle6.right
            anchors.leftMargin: 0
        }
    }
}
