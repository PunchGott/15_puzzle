import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Dialogs 1.2
import QtQuick.Controls 2.0
import Game 1.0

Window {
    id: root
    visible: true
    width: 640
    height: 480
    title: qsTr("15_puzzle")
    color: _style.backgroundColor

    Style {
        id: _style
    }

    GameBoardModel {
        id: gameBoardModel
        onStepCountChanged: isWin() ? winDialog.visible = true : winDialog.visible = false
    }


    Result {
        id: result
        width: root.width
        height: 20
        displayStepCount: qsTr("Step ") + gameBoardModel.stepCount
    }

    GameBoard {
        model: gameBoardModel
        anchors.top: result.bottom
        width: parent.width
        height: parent.height - result.height
    }

    Dialog {
        id: winDialog
        contentItem: Rectangle {
            color: root.color
            Column {
                anchors.centerIn: parent
                spacing: 20
                Text {
                    text: qsTr("You win!")
                    color:  _style.textColor
                    font {
                        family: "Arial Black"
                        bold: true
                        pointSize: 14
                    }
                }
                Button {
                    id: resetTheGame
                    text: qsTr("Reset the game")
                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            winDialog.close();
                            gameBoardModel.resetTheGame();
                        }
                    }
                }
                Button {
                    id: exitTheGame
                    text: qsTr("Exit the game")
                    MouseArea {
                        anchors.fill: parent
                        onClicked: Qt.quit()
                    }
                }
            }
        }
    }
}
