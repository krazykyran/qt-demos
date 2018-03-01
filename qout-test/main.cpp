#include <QCoreApplication>
#include <QTextStream>

int verbose = 1;
QTextStream qout(stdout);
#define VERBOSE(x)  if (verbose >= (x)) qout

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QString msg("hello world");

    VERBOSE(2) << msg << endl;

//    return a.exec();
}
