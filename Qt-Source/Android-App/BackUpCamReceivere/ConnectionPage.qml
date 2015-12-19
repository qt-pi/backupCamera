import QtQuick 2.2
import QtQuick.Layouts 1.2
import QtQuick.Controls 1.4
import QtQuick.Extras 1.4

Item {
    ToggleButton {
        id: toggleButton
        anchors.centerIn: parent
        text: {
            if (mainwerker.isConnected === true)
            {
                qsTr("Disconnect");
            }
            if (mainwerker.isConnected === false)
            {
                qsTr("Connect");
            }
        }
        checked: {
            if (mainwerker.isConnected === true) {
                true
            }
            else {
                false
            }
        }
        onCheckedChanged: {
            if( checked === true )
            {
                stackview.pop();
                stackview.push(Qt.resolvedUrl("MainWindow.qml"));
            }
        }

        onClicked: {
            mainwerker.startConn();
        }
    }
}

