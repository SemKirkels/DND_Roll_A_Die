TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
QT += core

DEFINES += ZMQ_STATIC
LIBS += -L$$PWD/../lib -lzmq
INCLUDEPATH += $$PWD/../include

SOURCES += main.cpp \
    RunClient.cpp \
    createplayer.cpp

HEADERS += \
    RunClient.h \
    createplayer.h \
    defines.h
