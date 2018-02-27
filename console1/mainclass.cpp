#include "mainclass.h"

extern QTextStream qout;

MainClass::MainClass(QObject *parent) : QObject(parent)
{
    qout << "MainClass: constructor ..." << endl;
    m_app = QCoreApplication::instance();
}

MainClass::~MainClass()
{
    qout << "MainClass: destructor ..." << endl;
}

void MainClass::init()
{
    connect(this, SIGNAL(finished(int)), SLOT(handleFinished(int)));

    m_timer = new QTimer(this);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(handleTimer()));
    m_timer->setInterval(1000);
    m_timer->start();
}

void MainClass::printMessage()
{
    qout << "MainClass: this is the message of the day ..." << endl;
}

void MainClass::handleTimer()
{
//    qout << "MainClass: timer timeout event ..." << endl;
    static int count = 5;
    if (count) {
        qout << "MainClass: timer timeout event ... " << count << endl;
    } else {
        qout << "MainClass: initiating shutdown ..." << endl;
        emit finished();
    }
    count--;
}

void MainClass::handleFinished(int exitCode)
{
    m_app->exit(exitCode);
}
