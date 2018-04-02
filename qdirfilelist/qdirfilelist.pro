QT += core
QT -= gui

CONFIG += c++11

TARGET = qdirfilelist
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    wifimanager.cpp

HEADERS += \
    wifimanager.h
