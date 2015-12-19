import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.2
Item {
    ColumnLayout {
        anchors.centerIn: parent
        TextField {
            id: serverText
            placeholderText: mainwerker.serverIP
        }

        TextField {
            id: portText
            placeholderText: mainwerker.serverPort
        }
        Button {
            id: connectButton
            text: qsTr("Confirm")
            onClicked: {
                mainwerker.setParams(serverText.text, portText.text);
                stackview.pop()
            }
        }
    }
}

