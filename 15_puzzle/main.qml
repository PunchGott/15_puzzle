import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Dialogs 1.2
import QtQuick.Controls 2.0
import Game 1.0
import Style 1.0
import InfoElements 1.0
import GameBoard 1.0
import Win 1.0

Window {
    id: root
    visible: true
    width: 640
    height: 480
    title: qsTr("15_puzzle")
    color: Style.backgroundColor
    minimumWidth: 300
    minimumHeight: 300

    property var gameBoardModel: GameBoardModel {
        id: _gameBoardModel
        onStepCountChanged: isWin() ? winDialog.visible = true : winDialog.visible = false
    }

    InfoPanel {
        id: _infoPanel
        infoPanelWidth: root.width
        infoPanelHeight: root.height * 0.06
        displayStepCount: qsTr("Step ") + gameBoardModel.stepCount
    }

    GameBoard {
        model: gameBoardModel
        anchors.top: _infoPanel.bottom
        width: parent.width
        height: parent.height - _infoPanel.height
    }

    WinDialog {
        id: winDialog
    }
}
