import QtQuick 2.0

Rectangle {
    id: root

    property string displayStepCount

    Style {
        id: _style
    }

    color: _style.backgroundColor

    Text {
        anchors.centerIn: root
        text: root.displayStepCount
        color: _style.textColor
        font {
            family: "Verdana"
            bold: true
            pointSize: 14
        }
    }

}
