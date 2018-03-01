#include <QCoreApplication>
#include <QTextStream>

#include "mainclass.h"

QTextStream qin(stdin);
QTextStream qout(stdout);
QTextStream qerr(stderr);

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    MainClass m(&a);
    m.init();

    return a.exec();
}
