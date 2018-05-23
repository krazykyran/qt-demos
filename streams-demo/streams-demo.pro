QT += core gui network serialport
QT += widgets

TARGET = streams-demo
TEMPLATE = app

SOURCES += main.cpp\
        dialog.cpp \
    streamsserver.cpp \
    streamssocket.cpp \
    streamstcpserver.cpp \
    streamsdevice.cpp

HEADERS  += dialog.h \
    streamsserver.h \
    streamssocket.h \
    streamstcpserver.h \
    streamsdevice.h

FORMS    += dialog.ui
