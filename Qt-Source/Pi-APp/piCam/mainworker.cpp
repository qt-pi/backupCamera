#include "mainworker.h"

MainWorker::MainWorker(QObject *parent) : QObject(parent)
{

}

void MainWorker::setParams(QString mAddr, int mPort)
{
    m_addr = mAddr;
    m_port = mPort;
}

void MainWorker::startWork()
{
    mqttConn = new QMQTT::Client(m_addr, m_port, this);
    connect(mqttConn, SIGNAL(connected()), this, SLOT(mqttConnected()));
    connect(mqttConn, SIGNAL(received(QMQTT::Message)), this, SLOT(mqttSubscribed(QMQTT::Message)));
    mqttConn->connect();
}

void MainWorker::mqttConnected()
{
    qDebug() << "Connected!";
    qDebug() << "Sending message";
    mqttConn->subscribe("piCam",0);
}

void MainWorker::mqttSubscribed(QMQTT::Message message)
{
    qDebug() << "Received message: " << message.payload();
    if (message.payload().contains("\"type\":\"requestCam\""))
    {
        QString ipAddress = "{\"type\":\"camIP\",\"value\":\"";
        QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();

        for (int i = 0; i < ipAddressesList.size(); ++i) {
            if (ipAddressesList.at(i) != QHostAddress::LocalHost &&
                ipAddressesList.at(i).toIPv4Address()) {
                ipAddress.append(ipAddressesList.at(i).toString());
                break;
            }
        }

        if (ipAddress.isEmpty())
            ipAddress.append(QHostAddress(QHostAddress::LocalHost).toString());

        ipAddress.append("\"}");
        QMQTT::Message pushMessage(0, "piCam", ipAddress.toUtf8());
        mqttConn->publish(pushMessage);
    }

    if (message.payload().contains("\"type\":\"startProcess\""))
    {
        qDebug() << "Starting cam Process";
        startCamProcess();
    }

    if (message.payload().contains("\"type\":\"endProcess\""))
    {
        endCamProcess();
    }

    if (message.payload().contains("\type\":\"restartUV4L\""))
    {
        restartCamUV4L();
    }

    if (message.payload().contains("\"type\":\"exit\""))
    {
        mqttDisconnected();
    }
}

void MainWorker::mqttDisconnected()
{
    emit workDone();
}

void MainWorker::startCamProcess()
{
    mProcess = new QProcess(this);
    QString processCommand("mjpg_streamer -i \"/usr/lib/input_uvc.so -d /dev/video0 -y -r 640x480 -f 10\" -o \"/usr/lib/output_http.so -p 8090 -w /var/www\"");
    mProcess->start(processCommand);
}

void MainWorker::endCamProcess()
{
    mProcess = new QProcess(this);
    QString processCommand("killall mjpg_streamer");
    mProcess->start(processCommand);
}

void MainWorker::restartCamUV4L()
{
    mProcess = new QProcess(this);
    QString processCommand("sudo service uv4l_raspicam restart");
    mProcess->start(processCommand);
}
