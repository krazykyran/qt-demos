#include <QCoreApplication>
#include <QTextStream>

#include "mainclass.h"

QTextStream qout(stdout);

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    MainClass m(&a);
    m.init();
    m.printMessage();

    return a.exec();
}
