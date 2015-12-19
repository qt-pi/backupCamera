#include "mainworker.h"

MainWorker::MainWorker(QObject *parent) : QObject(parent)
{
    m_serverAddr = "ohio-3dprint.com";
    m_serverPort = 8080;
    m_isconnected = false;
    m_camIP = "http://www.google.com";
}

void MainWorker::setParams(QString serverName, QString serverPort)
{
    if (!serverName.isEmpty())
    {
        m_serverAddr = serverName;
    }
    if (!serverPort.isEmpty())
    {
        m_serverPort = serverPort.toInt();

    }

    emit serverIPChanged(m_serverAddr);
    emit serverPortChanged(QString::number(m_serverPort));
}

void MainWorker::onMQTTConnection()
{
    mConn->subscribe("piCam", 0);
    QMQTT::Message pushMessage(0, "piCam", QString("{\"type\":\"requestCam\"}").toUtf8());
    mConn->publish(pushMessage);
    setIsConnected(true);
}

void MainWorker::startConn()
{
    if (m_isconnected == false)
    {
        mConn = new QMQTT::Client(m_serverAddr, m_serverPort, this);
        connect(mConn, SIGNAL(connected()), this, SLOT(onMQTTConnection()));
        connect(mConn, SIGNAL(received(QMQTT::Message)), this, SLOT(onSubbMessage(QMQTT::Message)));
        connect(mConn, SIGNAL(disconnected()), this, SLOT(onMQTTDisconnected()));
        mConn->connect();
    }
    else
    {
        mConn->disconnect();
    }
}

void MainWorker::onSubbMessage(QMQTT::Message message)
{
    if (message.payload().contains("\"type\":\"camIP\""))
    {
        setCamIP(QJsonDocument::fromJson(message.payload()).object().value("value").toString());
    }
}

QString MainWorker::camIP()
{
    return m_camIP;
}

void MainWorker::setCamIP(QString camIP)
{
    if (m_camIP != camIP)
    {
        m_camIP = QString("http://" + camIP + ":8090/javascript_simple.html");
        emit camIPChanged(m_camIP);
    }
}

bool MainWorker::isConnected()
{
    return m_isconnected;
}

void MainWorker::setIsConnected(bool isConnected)
{
    if (m_isconnected != isConnected)
    {
        m_isconnected = isConnected;
        emit isConnectedChanged(m_isconnected);
    }
}

void MainWorker::onMQTTDisconnected()
{
    setIsConnected(false);
}

bool MainWorker::startCam()
{
    if(m_isconnected)
    {
        QMQTT::Message pushMessage2(0, "piCam", QString("{\"type\":\"startProcess\"}").toUtf8());
        mConn->publish(pushMessage2);
    }
    return true;
}

bool MainWorker::endCam()
{
    if (m_isconnected)
    {
        QMQTT::Message pushMessage2(0, "piCam", QString("{\"type\":\"endProcess\"}").toUtf8());
        mConn->publish(pushMessage2);
    }

    return false;
}

void MainWorker::UV4LService()
{
    if (m_isconnected)
    {
        QMQTT::Message pushMessage2(0, "piCam", QString("{\"type\":\"restartUV4L\"}").toUtf8());
        mConn->publish(pushMessage2);
    }

}

void MainWorker::openPage()
{
    QUrl mUrl;
    mUrl.setUrl(m_camIP);
    QDesktopServices mService;
    mService.openUrl(mUrl);
}

void MainWorker::reloadCam()
{
    if (m_isconnected)
    {
        QMQTT::Message pushMessage2(0, "piCam", QString("{\"type\":\"requestCam\"}").toUtf8());
        mConn->publish(pushMessage2);
    }
}

QString MainWorker::serverIP()
{
    return m_serverAddr;
}

QString MainWorker::serverPort()
{
    return QString::number(m_serverPort);
}
