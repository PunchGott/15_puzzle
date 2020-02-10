import QtQuick 2.0
import QtQuick.Dialogs 1.2
import QtQuick.Controls 2.0


Dialog {
    id: winDialog
    Style {
        id: _style
    }
    contentItem: Rectangle {
        color: _style.backgroundColor
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
                onClicked: {
                    winDialog.close();
                    gm.resetTheGame();
                }
            }
            Button {
                id: exitTheGame
                text: qsTr("Exit the game")
                onClicked: Qt.quit()
            }
        }
    }
}
