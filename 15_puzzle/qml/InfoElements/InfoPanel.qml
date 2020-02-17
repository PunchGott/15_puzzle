import QtQuick 2.0
import InfoElements 1.0
import Style 1.0

Rectangle {
    id: _infoPanel
    property alias infoPanelWidth: _infoPanel.width
    property alias infoPanelHeight: _infoPanel.height
    property string displayStepCount: textStepCount

    color: Style.backgroundColor

    StopWatch {
        id: _stopWatch
        stopWatchSize: Math.min(_infoPanel.width, _infoPanel.height) / 2
        anchors {
          left: _infoPanel.left
          horizontalCenter: _infoPanel.horizontalCenter
          verticalCenter: _infoPanel.verticalCenter
          leftMargin: 10
        }
    }

    StepCount {
        id: _stepCount
        textStepCount: displayStepCount
        stepCountSize: Math.min(_infoPanel.width, _infoPanel.height) / 2

        anchors {
            horizontalCenter: _infoPanel.horizontalCenter
            verticalCenter: _infoPanel.verticalCenter
        }
    }
}
