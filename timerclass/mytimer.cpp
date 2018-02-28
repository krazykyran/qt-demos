#include "mytimer.h"
#include <QtCore>
#include <QDebug>

MyTimer::MyTimer()
{
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(mySlot()));

    timer->start(1000);
}

void MyTimer::mySlot()
{
    qDebug() << "Timer executed...";
}
