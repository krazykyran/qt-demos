#include "worker.h"

extern QTextStream qout;

Worker::Worker(QObject *parent) : QObject(parent)
{
    m_name = "Worker";
    qout << m_name << ": constructor ..." << endl;
    m_shutdown = false;

    connect(this, SIGNAL(spit(QString)), this, SLOT(handleSpit(QString)));
}

Worker::~Worker()
{
    qout << m_name << ": destructor ..." << endl;
}

void Worker::process()
{
    qout << m_name << ": processing ..." << endl;

    int count = 0;

    while(!m_shutdown) {

        QString msg = QString("process count = %1").arg(count);
        emit spit(msg);
        count++;

        QThread::msleep(500);
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);    // this is required to receive shutdown signal
    }

    qout << m_name << ": processing ending ..." << endl;
    emit finished();
}

void Worker::handleSpit(QString msg)
{
    qout << m_name << ": " << msg << endl;
}

void Worker::handleShutdown()
{
    qout << m_name << ": handle shutdown ..." << endl;
    m_shutdown = true;
}
