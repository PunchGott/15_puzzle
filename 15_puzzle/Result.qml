import QtQuick 2.0

Rectangle {
    id: root

    property string displayStepCount

    Text {
        color: "#34a3f4"
        text: root.displayStepCount
        anchors.centerIn: root
        font {
            family: "Impact"
            pointSize: 10
        }
    }

}
