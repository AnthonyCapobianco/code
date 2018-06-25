import QtQuick 2.9
import QtQuick.Window 2.2

Window {
    id: window
    visible: true
    width: 580
    height: 870
    title: qsTr("Calculator")

    GridView {
        id: gridView
        y: 488
        height: 725
        boundsBehavior: Flickable.StopAtBounds
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        keyNavigationWraps: true
        interactive: false
        flow: GridView.FlowTopToBottom
        snapMode: GridView.SnapToRow
        contentHeight: 145
        contentWidth: 145
        cellWidth: 145
        model: ListModel {
            ListElement {
                name: "Grey"
                colorCode: "grey"
            }

            ListElement {
                name: "Red"
                colorCode: "red"
            }

            ListElement {
                name: "Blue"
                colorCode: "blue"
            }

            ListElement {
                name: "Green"
                colorCode: "green"
            }
        }
        delegate: Item {
            x: 5
            height: 50
            Column {
                Rectangle {
                    width: 40
                    height: 40
                    color: colorCode
                    anchors.horizontalCenter: parent.horizontalCenter
                }

                Text {
                    x: 5
                    text: name
                    font.bold: true
                    anchors.horizontalCenter: parent.horizontalCenter
                }
                spacing: 5
            }
        }
        cellHeight: 145
    }

    Text {
        id: text1
        height: 145
        text: qsTr("0123")
        padding: 20
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignRight
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0
        anchors.top: parent.top
        anchors.topMargin: 0
        font.pixelSize: 55
    }
}
