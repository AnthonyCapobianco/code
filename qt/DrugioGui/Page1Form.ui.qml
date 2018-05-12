import QtQuick 2.9
import QtQuick.Controls 2.2

Page {
    id: page
    width: 600
    height: 400
    property alias buttonText: button.text

    Grid {
        id: grid
        rows: 3
        columns: 3
        anchors.fill: parent

        Pane {
            id: pane
            width: 200
            height: 200

            Button {
                id: button
                width: 200
                height: 200
                text: "Button"
                padding: 0
                rightPadding: 0
                leftPadding: 0
                wheelEnabled: true
                spacing: 0
                antialiasing: true
                anchors.top: parent.top
                anchors.right: parent.right
                anchors.bottom: parent.bottom
                anchors.left: parent.left
                anchors.topMargin: 0
                bottomPadding: 0
                topPadding: 0
                focusPolicy: Qt.NoFocus
            }
        }

        Pane {
            id: pane1
            width: 200
            height: 200
            Button {
                id: button1
                width: 200
                height: 200
                text: "Button"
                anchors.right: parent.right
                leftPadding: 0
                focusPolicy: Qt.NoFocus
                wheelEnabled: true
                anchors.bottom: parent.bottom
                rightPadding: 0
                antialiasing: true
                anchors.topMargin: 0
                bottomPadding: 0
                padding: 0
                topPadding: 0
                spacing: 0
                anchors.left: parent.left
                anchors.top: parent.top
            }
        }

        Pane {
            id: pane2
            width: 200
            height: 200
            Button {
                id: button2
                width: 200
                height: 200
                text: "Button"
                anchors.right: parent.right
                leftPadding: 0
                focusPolicy: Qt.NoFocus
                wheelEnabled: true
                anchors.bottom: parent.bottom
                rightPadding: 0
                antialiasing: true
                anchors.topMargin: 0
                bottomPadding: 0
                padding: 0
                topPadding: 0
                spacing: 0
                anchors.left: parent.left
                anchors.top: parent.top
            }
        }

        Pane {
            id: pane3
            width: 200
            height: 200
            Button {
                id: button3
                width: 200
                height: 200
                text: "Button"
                anchors.right: parent.right
                leftPadding: 0
                focusPolicy: Qt.NoFocus
                wheelEnabled: true
                anchors.bottom: parent.bottom
                rightPadding: 0
                antialiasing: true
                anchors.topMargin: 0
                bottomPadding: 0
                padding: 0
                topPadding: 0
                spacing: 0
                anchors.left: parent.left
                anchors.top: parent.top
            }
        }

        Pane {
            id: pane4
            width: 200
            height: 200
            Button {
                id: button4
                width: 200
                height: 200
                text: "Button"
                anchors.right: parent.right
                leftPadding: 0
                focusPolicy: Qt.NoFocus
                wheelEnabled: true
                anchors.bottom: parent.bottom
                rightPadding: 0
                antialiasing: true
                anchors.topMargin: 0
                bottomPadding: 0
                padding: 0
                topPadding: 0
                spacing: 0
                anchors.left: parent.left
                anchors.top: parent.top
            }
        }

        Pane {
            id: pane5
            width: 200
            height: 200
            Button {
                id: button5
                width: 200
                height: 200
                text: "Button"
                anchors.right: parent.right
                leftPadding: 0
                focusPolicy: Qt.NoFocus
                wheelEnabled: true
                anchors.bottom: parent.bottom
                rightPadding: 0
                antialiasing: true
                anchors.topMargin: 0
                bottomPadding: 0
                padding: 0
                topPadding: 0
                spacing: 0
                anchors.left: parent.left
                anchors.top: parent.top
            }
        }
    }
}
