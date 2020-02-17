import QtQuick 2.0
import QtQuick.Controls 2.5
import Style 1.0

Text {
    id: root
    property string textStepCount: "Step 0"
    property alias stepCountSize: root.font.pointSize

    text: textStepCount
    color: Style.textColor
    font {
        family: "Verdana"
        bold: true
        pointSize: 16
    }
}
