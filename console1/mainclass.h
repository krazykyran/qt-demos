#ifndef MAINCLASS_H
#define MAINCLASS_H

#include <QCoreApplication>
#include <QThread>
#include <QObject>
#include <QSocketNotifier>
#include <QTextStream>
#include <QTimer>

#include <signal.h>
#include <unistd.h>
#include <sys/socket.h>

class MainClass : public QObject
{
    Q_OBJECT
public:
    explicit MainClass(QObject *parent = 0);
    ~MainClass();

    void init();
public slots:
    void run();
    void timerEvent(QTimerEvent *event);

public:
    static void INTsignalHandler(int unused);
    static void TERMsignalHandler(int unused);

signals:
    void signalINT();
    void signalTERM();

    // signal to finish, this is connected to Application Quit
    void finished(int e);

public slots:
    void handleSIGINT();
    void handleSIGTERM();

    void abortApp();
    void handleFinished(int e = 0);
    void exitApp();
    void handleAboutToQuit();

private:
    const char *m_name;
    QCoreApplication *m_app;

    static int sigINTfds[2];
    static int sigTERMfds[2];

    QSocketNotifier *snINT;
    QSocketNotifier *snTERM;

    int m_timerId;
    bool m_shutdown;
    int m_exitCode;
};

#endif // MAINCLASS_H
