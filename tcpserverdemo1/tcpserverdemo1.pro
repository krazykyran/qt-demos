QT += core network
QT -= gui

CONFIG += c++11

TARGET = tcpserverdemo1
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    myserver.cpp

HEADERS += \
    myserver.h
