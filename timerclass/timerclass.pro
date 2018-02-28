QT += core

QT -= gui

TARGET = timerclass
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    mytimer.cpp

HEADERS += \
    mytimer.h
