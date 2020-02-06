import QtQuick 2.12
import QtQuick.Window 2.12
import Game 1.0

Window {
    id: root
    visible: true
    width: 640
    height: 480
    title: qsTr("15_puzzle")
    color: "#5de9ae"

    GameBoardModel {
        id: gameBoardModel
    }

    Result {
        id: _info
        width: root.width
        height: 20
        color: root.color
        displayStepCount: "Step " + gameBoardModel.stepCount
    }

    GameBoard {
        model: gameBoardModel
        anchors.top: _info.bottom
        width: parent.width
        height: parent.height - _info.height
    }
}
