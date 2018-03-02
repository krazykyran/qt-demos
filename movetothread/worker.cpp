#include "worker.h"

extern QTextStream qout;

Worker::Worker(QObject *parent) : QObject(parent)
{
    m_name = "Worker";
    qout << m_name << ": constructor ..." << endl;
    m_shutdown = false;

//    connect(this, SIGNAL(spit(QString&)), this, SLOT(handleSpit(QString&)));
}

Worker::~Worker()
{
    qout << m_name << ": destructor ..." << endl;
}

void Worker::process()
{
    qout << m_name << ": processing ..." << endl;
    int i = 0;
    int count = 0;
    QElapsedTimer timer;
    timer.start();
    while(!m_shutdown) {
        if (timer.elapsed() > 100) {
            QString msg = QString("process timer = %1ms")
                    .arg(timer.elapsed());
            emit spit(msg);
            timer.restart();
        }

//        qout << m_name << ": process timer elapsed " << timer.elapsed() << "ms" << endl;

        QThread::msleep(10);
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
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
    m_shutdown = true;
}
