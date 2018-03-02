QT += core
QT -= gui

CONFIG += c++11

TARGET = movetothread
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    mainclass.cpp \
    worker.cpp

HEADERS += \
    mainclass.h \
    worker.h
