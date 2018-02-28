#ifndef MAINCLASS_H
#define MAINCLASS_H

#include <QCoreApplication>
#include <QObject>

class MainClass : public QObject
{
    Q_OBJECT
private:
    QCoreApplication *app;

public:
    explicit MainClass(QObject *parent = 0);
    /* call this to quit the application */
    void quit();

signals:
    /* signal to finish, this is connected to Application Quit */
    void finished();

public slots:
    /* This is the slot that gets called from main to start everything
     * but, everything is set up in the Constructor.
     */
    void run();

    /* slot that get signal when that application is about to quit */
    void aboutToQuitApp();

};

#endif // MAINCLASS_H
