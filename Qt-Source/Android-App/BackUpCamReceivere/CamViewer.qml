import QtQuick 2.2
import QtWebView 1.0
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Dialogs 1.0
import QtQuick.Extras 1.4
import QtQuick.Layouts 1.0
import QtQuick.Window 2.1

Item {
    visible: true
    id: root
    WebView {
        id: camview
        anchors.fill: parent
        url: mainwerker.camIP
    }
}

