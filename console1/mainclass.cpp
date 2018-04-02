#include "mainclass.h"

// needed to get an undefined reference to static members
int MainClass::sigINTfds[2];
int MainClass::sigTERMfds[2];

extern QTextStream qin;
extern QTextStream qout;
extern QTextStream qerr;

static int setup_unix_signal_handlers()
{
    struct sigaction sigint, sigterm;

    // register a signal handler for SIGINT
    // which is caught when ctrl-c sent from bash shell.
    sigint.sa_handler = MainClass::INTsignalHandler;
    sigemptyset(&sigint.sa_mask);
    sigint.sa_flags |= SA_RESTART;
    if (sigaction(SIGINT, &sigint, NULL) > 0)
        return EXIT_FAILURE;

    // register a signal handler for SIGTERM
    // which is caught when sent from OS (shutdown or reboot)
    sigterm.sa_handler = MainClass::TERMsignalHandler;
    sigemptyset(&sigterm.sa_mask);
    sigterm.sa_flags |= SA_RESTART;
    if (sigaction(SIGTERM, &sigterm, NULL) > 0)
        return EXIT_FAILURE;

    // all succeeded registering sigactions, return 0.
    return EXIT_SUCCESS;
}


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
    delete snINT;
    delete snTERM;
}

void MainClass::init()
{
    qout << m_name << ": initializing ..." << endl;

    // connect MainClass application specific signals and slots
    connect(this, SIGNAL(finished(int)), this, SLOT(handleFinished(int)));
    connect(this, SIGNAL(signalINT()), this, SLOT(abortApp()));
    connect(this, SIGNAL(signalTERM()), this, SLOT(abortApp()));
    connect(m_app, SIGNAL(aboutToQuit()), this, SLOT(handleAboutToQuit()));

    // configure socket pair for SIGINT signal, and connect it to SIGINT handler slot
    snINT = nullptr;
    if (::socketpair(AF_UNIX, SOCK_STREAM, 0, sigINTfds)) {
        qerr << m_name << ": couldn't create SIGINT socketpair" << endl;
        ::exit(EXIT_FAILURE);
    }
    snINT = new QSocketNotifier(sigINTfds[1], QSocketNotifier::Read, this);
    connect(snINT, SIGNAL(activated(int)),
            this, SLOT(handleSIGINT()));

    // configure socket pair for SIGTERM signal, and connect it to SIGINT handler slot
    snTERM = nullptr;
    if (::socketpair(AF_UNIX, SOCK_STREAM, 0, sigTERMfds)) {
        qerr << m_name << ": couldn't create SIGTERM socketpair" << endl;
        ::exit(EXIT_FAILURE);
    }
    snTERM = new QSocketNotifier(sigTERMfds[1], QSocketNotifier::Read, this);
    connect(snTERM, SIGNAL(activated(int)),
            this, SLOT(handleSIGTERM()));

    // setup unix signal handlers, OS system calls can only be done outside class members
    if (setup_unix_signal_handlers()) {
        qerr << m_name << ": failed to configure unix sigal handlers" << endl;
        ::exit(EXIT_FAILURE);
    }

//    QTimer::singleShot(100, this, SLOT(run()));
    // start QObject timer.
    m_timerId = startTimer(100);

    QTimer::singleShot(10500, this, SLOT(abortApp()));
}

void MainClass::run()
{
    qout << m_name << ": running, doing something exciting ..." << endl;

    qout << m_name << ": running, and looping ..." << endl;
    while (!m_shutdown) {
        QThread::msleep(10);
        m_app->processEvents();
    }

    qout << m_name << ": running, now finishing ..." << endl;
    emit finished(EXIT_SUCCESS);
}

// timerEvent overrides QObject QTimer handler,
// which was started by startTimer() in the init() member function
// use this override function to do loop tasks
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

void MainClass::INTsignalHandler(int unused)
{
    Q_UNUSED(unused);
    qout << " - caught SIGINT signal ..." << endl;
    char a = 1;
    write(sigINTfds[0], &a, sizeof(a));
}

void MainClass::TERMsignalHandler(int unused)
{
    Q_UNUSED(unused);
    qout << " - caught SIGTERM signal ..." << endl;
    char a = 1;
    write(sigTERMfds[0], &a, sizeof(a));
}

void MainClass::handleSIGINT()
{
    snINT->setEnabled(false);
    char tmp;
    read(sigINTfds[1], &tmp, sizeof(tmp));

    // do Qt stuff
    qout << m_name << ": received SIGINT signal..." << endl;
    m_exitCode = SIGINT;
    emit signalINT();

    snINT->setEnabled(true);
}

void MainClass::handleSIGTERM()
{
    snTERM->setEnabled(false);
    char tmp;
    read(sigTERMfds[1], &tmp, sizeof(tmp));

    // do Qt stuff
    qout << m_name << ": received SIGTERM signal..." << endl;
    m_exitCode = SIGTERM;
    emit signalTERM();

    snTERM->setEnabled(true);
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

void MainClass::handleAboutToQuit()
{
    qout << m_name << ": about to quit ..." << endl;
}
