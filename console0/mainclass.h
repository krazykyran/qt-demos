#ifndef MAINCLASS_H
#define MAINCLASS_H

#include <QCoreApplication>
#include <QObject>
#include <QThread>

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
    void quit();
public slots:
    void timerEvent(QTimerEvent *event);

signals:
    // signal to finish, this is connected to Application Quit
    void finished(int e);

    // slot that get signal when that application is about to quit
public slots:
    void abortApp();
    void handleFinished(int e = 0);
    void exitApp();
    void handleAboutToQuit();

private:
    const char *m_name;
    QCoreApplication *m_app;

    int m_timerId;
    bool m_shutdown;
    int m_exitCode;
};

#endif // MAINCLASS_H
