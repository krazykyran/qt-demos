#include <QCoreApplication>
#include <QTextStream>

#include "sockettest.h"

QTextStream qout(stdout);

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    SocketTest socket;
    socket.connectSocket();


    return a.exec();
}
