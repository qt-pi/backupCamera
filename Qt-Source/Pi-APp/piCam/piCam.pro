QT += core network
QT -= gui

TARGET = piCam
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app
INCLUDEPATH+=$$[QT_SYSROOT]/usr/local/include
#LIBS+=  -L/usr/local/lib -lqmqtt
LIBS+=  -lqmqtt


SOURCES += main.cpp \
    mainworker.cpp

HEADERS += \
    mainworker.h

