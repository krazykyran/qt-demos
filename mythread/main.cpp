#include <QCoreApplication>
#include "mythread.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    MyThread mthread1;
    mthread1.name = "My Thread 1";

    MyThread mthread2;
    mthread2.name = "My Thread 2";

    MyThread mthread3;
    mthread3.name = "My Thread 3";

    mthread1.start(QThread::HighestPriority);
    mthread2.start(QThread::NormalPriority);
    mthread3.start(QThread::LowestPriority);

    return a.exec();
}
