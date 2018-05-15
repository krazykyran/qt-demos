#-------------------------------------------------
#
# Project created by QtCreator 2018-04-24T09:07:11
#
#-------------------------------------------------

QT += core gui network

QT += widgets

TARGET = tcpserver
TEMPLATE = app


SOURCES += main.cpp\
        dialog.cpp \
    tcpserver.cpp \
    tcpconnection.cpp \
    tcpconnections.cpp

HEADERS  += dialog.h \
    tcpserver.h \
    tcpconnection.h \
    tcpconnections.h

FORMS    += dialog.ui
