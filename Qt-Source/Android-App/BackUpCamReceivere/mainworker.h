#ifndef MAINWORKER_H
#define MAINWORKER_H

#include <QObject>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDesktopServices>
#include <QUrl>
#include "qmqtt.h"
class MainWorker : public QObject
{
    Q_PROPERTY(QString serverIP READ serverIP NOTIFY serverIPChanged)
    Q_PROPERTY(QString serverPort READ serverPort NOTIFY serverPortChanged)
    Q_PROPERTY(QString camIP READ camIP WRITE setCamIP NOTIFY camIPChanged)
    Q_PROPERTY(bool isConnected READ isConnected WRITE setIsConnected NOTIFY isConnectedChanged)
    Q_OBJECT
public:
    explicit MainWorker(QObject *parent = 0);
    bool isConnected();
    QString camIP();
    QString serverIP();
    QString serverPort();

signals:
    void camIPChanged(QString camIP);
    void isConnectedChanged(bool isConnected);
    void serverIPChanged(QString serverIP);
    void serverPortChanged(QString serverPort);

public slots:
    void onMQTTConnection();
    void onSubbMessage(QMQTT::Message);
    void setParams(QString, QString);
    void startConn();
    void setCamIP(QString camIP);
    void setIsConnected(bool isConnected);
    void onMQTTDisconnected();
    bool startCam();
    bool endCam();
    void openPage();
    void reloadCam();
    void UV4LService();

private:
   QMQTT::Client *mConn;
    QString m_serverAddr;
    int m_serverPort;

    QString m_camIP;
    bool m_isconnected;
};

#endif // MAINWORKER_H
