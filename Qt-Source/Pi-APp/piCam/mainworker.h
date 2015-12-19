#ifndef MAINWORKER_H
#define MAINWORKER_H

#include <QObject>
#include <QDebug>
#include <QtNetwork>
#include <QProcess>
#include "RPiIncludes/qmqtt.h"
//#include "qmqtt/qmqtt.h"
class MainWorker : public QObject
{
    Q_OBJECT
public:
    explicit MainWorker(QObject *parent = 0);
    void startWork();
    void setParams(QString mAddr, int mPort);
    void startCamProcess();
    void endCamProcess();
    void restartCamUV4L();
signals:
    void workDone();

public slots:
    void mqttConnected();
    void mqttDisconnected();
    void mqttSubscribed(QMQTT::Message);
private:
    QMQTT::Client *mqttConn;
    QString m_addr;
    QProcess *mProcess;
    int m_port;
};

#endif // MAINWORKER_H
