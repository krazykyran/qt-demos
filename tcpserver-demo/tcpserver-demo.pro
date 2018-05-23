QT += core gui network
QT += widgets

TARGET = tcpserver-demo
TEMPLATE = app


SOURCES += main.cpp\
        dialog.cpp \
    streamsserver.cpp \
    streamssocket.cpp

HEADERS  += dialog.h \
    streamsserver.h \
    streamssocket.h

FORMS    += dialog.ui
