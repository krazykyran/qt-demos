QT += core
QT -= gui

CONFIG += c++11

TARGET = addinsight-test
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

HEADERS += \
    mainclass.h

SOURCES += \
    main.cpp \
    mainclass.cpp

target.path = /usr/local/bin
INSTALLS += target
