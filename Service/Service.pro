TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
QT += core

DEFINES += ZMQ_STATIC
LIBS += -L$$PWD/../lib -lzmq
INCLUDEPATH += $$PWD/../include

SOURCES += main.cpp \
    RunService.cpp \
    dice.cpp \
    player.cpp

HEADERS += \
    RunService.h \
    dice.h \
    player.h

DEFINES += DEBUG_ENABLE = 1
DEFINES += RUN_LOCAL = 0
