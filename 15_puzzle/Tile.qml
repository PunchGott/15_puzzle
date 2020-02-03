import QtQuick 2.0

Rectangle {
    id: root
    color: "lightgreen"
    radius: 5

    property string displayText: ""
    Text {
        id: _firstText
        anchors.centerIn: root
        text: root.displayText
        font {
            pointSize: Math.min(root.width, root.height) / 4
            bold:true
        }
    }

    border {
        color: "black"
        width: 1
    }
}

