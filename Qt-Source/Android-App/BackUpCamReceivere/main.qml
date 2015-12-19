import QtQuick 2.5
import QtWebView 1.0
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.4
import PiCam 1.0

Window {
    id: root
    visible: true
    width: 1920; height: 1080
    property bool aBool: false


    MainWerker {
        id: mainwerker
    }

    Image {
        id: backgroundImage
        source: Qt.resolvedUrl("blackBackground.jpg")
        anchors.fill: parent
    }

    Rectangle {
        id: mainHolder
        color: Qt.rgba(0,0,0,0)
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: bottomDock.top
        anchors.bottomMargin: 10
        clip: true
        StackView {
            id: stackview
            visible: true
            anchors.fill: parent
            initialItem: Qt.resolvedUrl("ConnectionPage.qml")
        }

        WebView {
            id: mwebview
            anchors.fill: parent
            visible: false
            url: mainwerker.camIP
        }

        states: [
            State { name: "activateStackView"
                    PropertyChanges { target: mwebview; visible: false}
                    PropertyChanges { target: stackview; visible: true} },
            State { name: "activateWebView"
                    PropertyChanges { target: mwebview; visible: true}
                    PropertyChanges { target: stackview; visible: false} }
        ]

        state: "activateStackView"
    }

    Rectangle {
        id: bottomDock
        color: Qt.rgba(0,0,0,0)
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom; anchors.bottomMargin: 10
        height: parent.height/5
        Row{
            anchors.centerIn: bottomDock
            spacing: (10 * parent.width/150)

            Image {
                id: cameraButton
                height: bottomDock.height
                width: height
                source: {
                    if (mainwerker.isConnected === true)
                    {
                        Qt.resolvedUrl("cameraButton.png")
                    }
                    else
                    {
                        Qt.resolvedUrl("cameraButtonPressed.png")
                    }
                }

                fillMode: Image.PreserveAspectFit
                opacity: {
                    if (mainwerker.isConnected === true)
                    {
                        0.6
                    }
                    else
                    {
                        0.4
                    }
                }

                MouseArea {
                    anchors.fill: parent
                    onPressedChanged:{
                        if (mainwerker.isConnected === true)
                        {
                            if (pressed === true)
                            {
                                cameraButton.source = Qt.resolvedUrl("cameraButtonPressed.png")
                            }
                            if (pressed === false)
                            {
                                cameraButton.source = Qt.resolvedUrl("cameraButton.png");
                                mainHolder.state = "activateWebView"
                            }
                        }
                    }
                }
            }

            Image {
                id: toggleButton
                height: bottomDock.height
                width: height
                source: {
                    if (mainwerker.isConnected === true)
                    {
                        Qt.resolvedUrl("toggleButton.png")
                    }
                    else
                    {
                        Qt.resolvedUrl("toggleButtonPressed.png")
                    }
                }
                fillMode: Image.PreserveAspectFit
                opacity: {
                    if (mainwerker.isConnected === true)
                    {
                        0.6
                    }
                    else
                    {
                        0.4
                    }
                }
                MouseArea {
                    anchors.fill: parent
                    onPressedChanged: {
                        if (mainwerker.isConnected === true)
                        {
                            if (pressed === true)
                            {
                                toggleButton.source = Qt.resolvedUrl("toggleButtonPressed.png");
                            }
                            if (pressed === false)
                            {
                                toggleButton.source = Qt.resolvedUrl("toggleButton.png");
                                aBool = mainwerker.endCam();
                                aBool = mainwerker.startCam();
                            }
                        }
                    }
                }
            }

            Image {
                id: refreshButton
                height: bottomDock.height
                width: height
                source: {
                    if (mainwerker.isConnected === false)
                    {
                        Qt.resolvedUrl("refreshButtonPressed.png")
                    }
                    if (mainwerker.isConnected === true)
                    {
                        Qt.resolvedUrl("refreshButton.png");
                    }
                }

                fillMode: Image.PreserveAspectFit
                opacity: {
                    if (mainwerker.isConnected === false)
                    {
                        0.4
                    }
                    if (mainwerker.isConnected === true)
                    {
                        0.6
                    }
                }
                MouseArea {
                    anchors.fill: parent
                    onPressedChanged: {
                        if (mainHolder.state === "activateWebView")
                        {
                            if (pressed === true)
                            {
                                refreshButton.source = Qt.resolvedUrl("refreshButtonPressed.png");
                            }
                            if (pressed === false)
                            {
                                refreshButton.source = Qt.resolvedUrl("refreshButton.png");
                                mwebview.reload();
                            }
                        }
                        if ((mainHolder.state === "activateStackView") && (mainwerker.isConnected === true))
                        {
                            if (pressed === true)
                            {
                                refreshButton.source = Qt.resolvedUrl("refreshButtonPressed.png");
                            }
                            if (pressed === false)
                            {
                                refreshButton.source = Qt.resolvedUrl("refreshButton.png");
                                mainwerker.reloadCam();
                            }
                        }
                    }
                }
            }

            Image {
                id: settingsButton
                height: bottomDock.height
                width: height
                source: Qt.resolvedUrl("settingsButton.png")
                fillMode: Image.PreserveAspectFit
                opacity: 0.6
                MouseArea {
                    anchors.fill: parent
                    onPressedChanged: {
                        if (pressed === true)
                        {
                            settingsButton.source = Qt.resolvedUrl("settingsButtonPressed.png");
                        }
                        if (pressed === false)
                        {
                            settingsButton.source = Qt.resolvedUrl("settingsButton.png");
                            mainHolder.state = "activateStackView";
                        }
                    }
                }
            }

            Image {
                id: powerButton
                height: bottomDock.height
                width: height
                source: Qt.resolvedUrl("powerButton.png")
                fillMode: Image.PreserveAspectFit
                opacity: 0.6
                MouseArea {
                    anchors.fill: parent
                    onPressedChanged: {
                        if (pressed === true)
                        {
                            powerButton.source = Qt.resolvedUrl("powerButtonPressed.png");
                        }
                        if (pressed === false)
                        {
                            powerButton.source = Qt.resolvedUrl("powerButton.png");
                            Qt.quit();
                        }
                    }
                }
            }
        }
    }
}

