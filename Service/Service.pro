TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
#CONFIG -= qt
QT += core

DEFINES += ZMQ_STATIC
LIBS += -L$$PWD/../lib -lzmq
INCLUDEPATH += $$PWD/../include

SOURCES += main.cpp