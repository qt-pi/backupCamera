#include <QCoreApplication>
#include "mainworker.h"
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    MainWorker *mWorker;
    mWorker = new MainWorker;

    QObject::connect(mWorker, SIGNAL(workDone()), &a, SLOT(quit()));

    QCommandLineParser parser;


    QCommandLineOption mqttServer(QStringList() << "s" << "set-server",
            QCoreApplication::translate("main", "Set MQTT Server Address"),
            QCoreApplication::translate("main", "server"));
    parser.addOption(mqttServer);

    QCommandLineOption mqttPort(QStringList() << "p" << "port",
            QCoreApplication::translate("main", "Set MQTT Port"),
            QCoreApplication::translate("main", "port"));
    parser.addOption(mqttPort);
    parser.process(a);

    if (!(parser.isSet(mqttServer)) || !(parser.isSet(mqttPort)))
    {
        qDebug() << "Please set MQTT server address and port.";
        qDebug() << "-s serverAddress -p PortNumber(int)";
        return 1;
    }

    mWorker->setParams(parser.value(mqttServer), parser.value(mqttPort).toInt());
    mWorker->startWork();
    return a.exec();
}

