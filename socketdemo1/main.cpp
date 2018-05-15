#include <QCoreApplication>
#include <QTextStream>

#include "sockettest.h"

QTextStream qout(stdout);
QTextStream qerr(stderr);

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    SocketTest socket;
    socket.init();


    return a.exec();
}
