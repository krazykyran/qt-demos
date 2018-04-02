#include <QCoreApplication>
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QSet>

#include "wifimanager.h"

QTextStream qout(stdout);
QTextStream qerr(stderr);


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);


    qout << "hello world!" << endl;

    WifiManager wm(&a);
    QObject::connect(&wm, SIGNAL(finished()), &a, SLOT(quit()));
    wm.init();

    return a.exec();

}
