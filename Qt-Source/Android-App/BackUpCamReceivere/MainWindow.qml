import QtQuick 2.2
import QtQuick.Layouts 1.2
import QtQuick.Controls 1.4
import QtQuick.Extras 1.4

Item {
    ColumnLayout {
        id: buttonLayout
        anchors.centerIn: parent

        Row {
            Text {
                id: connectionLabel
                color: "white"
                text: "Connection to MQTT: "
            }

            StatusIndicator {
                id: connectedStatusIndicator
                height: connectionLabel.height
                color: "#35e02f"
                on: {
                        if (mainwerker.isConnected === true)
                        {
                            true
                        }
                        else
                        {
                            false
                        }
                }
            }
        }
        Row {
            Button {
                id: disconnectButton
                text: {
                    if (mainwerker.isConnected === true)
                    {
                        "Disconnect"
                    }
                    if (mainwerker.isConnected === false)
                    {
                        "Connect"
                    }
                }

                onClicked: {
                    mainwerker.startConn();
                }
            }

            Button {
                id: settingsButton
                text: qsTr("Configure")
                onClicked: {
                    stackview.push(Qt.resolvedUrl("SettingsPage.qml"))
                }
            }
        }


        Text {
            id: iplabel
            text: mainwerker.camIP
        }

        Button {
            text: "Restart UV4L"
            onClicked: {
                mainwerker.UV4LService();
            }
        }
    }
}

