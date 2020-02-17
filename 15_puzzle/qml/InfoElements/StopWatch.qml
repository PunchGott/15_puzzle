import QtQuick 2.0
import QtQuick.Controls 2.5

Label {
    id: root
    property int minute: 0
    property int seconds: 0
    property alias stopWatchSize: root.font.pointSize

    text: qsTr("%1:%2").arg(minute).arg(seconds)

    font {
        family: "Verdana"
        bold: true
        pointSize: 16
    }

    Timer {
        interval: 1000; running: true; repeat: true
        onTriggered: {
            seconds++;
        }
    }

    Timer {
        interval: 59000; running: true; repeat: true
        onTriggered: {
            minute++;
            seconds = -1;
        }
    }
}
