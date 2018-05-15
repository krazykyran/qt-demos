QT += core network
QT -= gui

CONFIG += c++11

TARGET = tcpserverdemo0
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    myserver.cpp

HEADERS += \
    myserver.h
