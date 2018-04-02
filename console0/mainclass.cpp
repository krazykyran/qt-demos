#include "mainclass.h"

extern QTextStream qin;
extern QTextStream qout;
extern QTextStream qerr;

MainClass::MainClass(QObject *parent) : QObject(parent)
{
    m_name = "MainClass";
    qout << m_name << ": constructor ..." << endl;
    m_app = QCoreApplication::instance();
    m_shutdown = false;
    m_exitCode = 0;
}

MainClass::~MainClass()
{
    qout << m_name << ": destructor ..." << endl;
}

void MainClass::init()
{
    qout << m_name << ": initializing ..." << endl;

    // connect MainClass application specific signals and slots
    connect(this, SIGNAL(finished(int)), this, SLOT(handleFinished(int)));
    connect(m_app, SIGNAL(aboutToQuit()), this, SLOT(handleAboutToQuit()));

    // start QObject timer.
    m_timerId = startTimer(100);

    QTimer::singleShot(10500, this, SLOT(abortApp()));
}

// call this routine to quit the application
void MainClass::quit()
{
    // cleanup code goes here
    // then do emit finished to signal CoreApplication to quit
    emit finished(EXIT_SUCCESS);

}

// this is the event that executes every 100ms, started from init()
void MainClass::timerEvent(QTimerEvent *event)
{
    Q_UNUSED(event);
    static int i = 0;
    static int count = 0;

    if (m_shutdown) {
        qout << m_name << ": timerEvent is exiting ..." << endl;
        killTimer(m_timerId);
        emit finished(EXIT_SUCCESS);
        return;
    }

    if (count == 0) {
        qout << m_name << ": timerEvent is initializing " << i++ << " ..." << endl;
    }

    if (count == 1) {
        ;
    }

    if (count == 10) {
        qout << m_name << ": timerEvent is executing " << i++ << " ..." << endl;
        count = 0;
    }

    count++;
}

void MainClass::abortApp()
{
    qout << m_name << ": aborting app ..." << endl;
    // MainClass::run() or MainClass::timerEvent() will check m_abort,
    // and emit a finished() signal, which is handled by finishApp() slot.
    m_shutdown = true;
}

void MainClass::handleFinished(int e)
{
    qout << m_name << ": shutting down app ... " << endl;

    // app->exit() will stop the event handler and prevent
    // signals from tasks to get through (undesired), so use a singleshot timer
    // to signal an App Quit after 100ms.
    m_exitCode = e;
    QTimer::singleShot(100, this, SLOT(exitApp()));
}

void MainClass::exitApp()
{
    qout << m_name << ": quitting app ..." << endl;
    m_app->exit(m_exitCode);
}

// shortly after quit is called the CoreApplication will signal this routine
// this is a good place to delete any objects that were created in the
// constructor and/or to stop any threads
void MainClass::handleAboutToQuit()
{
    qout << m_name << ": about to quit ..." << endl;
}
