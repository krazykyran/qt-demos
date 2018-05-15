#include <QCoreApplication>
#include <QTextStream>

#include "myserver.h"

QTextStream qout(stdout);
QTextStream qerr(stderr);

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    MyServer server(&a);
    server.init();

    return a.exec();
}
