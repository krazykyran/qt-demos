QT += core network
QT -= gui

CONFIG += c++11

TARGET = socketdemo0
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    sockettest.cpp

HEADERS += \
    sockettest.h
