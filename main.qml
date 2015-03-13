import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2

ApplicationWindow {
    id: topLevel
    title: qsTr("Birthday Alarms")
    width: 640
    height: 480
    visible: true

    Dialog {
        id: addAlarmDialog
        title: qsTr("Add birthday")
        standardButtons: StandardButton.Ok | StandardButton.Cancel
        width: topLevel.width * 0.8
        height: topLevel.height * 0.8

        Item {
            id: content

            width: topLevel.width * 0.6
            height: topLevel.height * 0.6

            TextField {
                id: nameField
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.top: parent.top
                anchors.topMargin: 10
                placeholderText: qsTr("Enter name")
            }

            Calendar {
                id: calendar
                anchors.top: nameField.bottom
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.bottom: parent.bottom
            }
        }

        onAccepted: {
            if (nameField.text.length > 0) {
                alarmModel.addAlarm(calendar.selectedDate, nameField.text)
            }
        }

    }

    Rectangle {
        anchors.fill: parent
        color: "#c8c4c4"

        ListView {
            id: alarms
            model: alarmModel
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.bottom: button.top
            visible: count > 0

            delegate: Text {
                text: display
                font.pixelSize: topLevel.height / 20
                fontSizeMode: Text.HorizontalFit
                anchors.horizontalCenter: parent.horizontalCenter
            }
        }

        Text {
            anchors.fill: alarms
            font.pixelSize: height
            fontSizeMode: Text.Fit
            visible: !alarms.visible
            text: qsTr("No alarms registered yet")
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            color: "#7d7b7b"
        }

        Button {
            id: button
            text: qsTr("+")
            anchors.bottom: parent.bottom
            anchors.horizontalCenter: parent.horizontalCenter

            onClicked: addAlarmDialog.open()
        }
    }
}
