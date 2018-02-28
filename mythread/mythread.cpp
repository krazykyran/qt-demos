#include "mythread.h"
#include <QtCore>
#include <QDebug>

MyThread::MyThread()
{
}

void MyThread::run()
{
    qDebug() << this->name << "Running...";

    for (int i = 0; i < 1000; i++)
    {
        QMutex mutex;
        mutex.lock();
        if (this->Stop)
        {
            break;
        }
        mutex.unlock();
        qDebug() << this->name << i;
        // sleep(1);
    }
}
