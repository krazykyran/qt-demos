QT += core gui network
QT += widgets

TARGET = streams-vms
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
