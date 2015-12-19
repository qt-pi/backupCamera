#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <qqml.h>
#include <QQuickItem>
#include <QQuickView>
#include <qqml.h>

#include "mainworker.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    qmlRegisterType<MainWorker>("PiCam", 1, 0, "MainWerker");
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}

