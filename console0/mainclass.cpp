#include "mainclass.h"
#include <QThread>
#include <QDebug>

MainClass::MainClass(QObject *parent) :
    QObject(parent)
{
    // get the instance of the main application
    app = QCoreApplication::instance();
    // setup everything here
    // create any global objects
    // setup debug and warning code

}

/* 10ms after the application starts this method will run
 * all Qt messaging is runnning at this point so threads, signals and slots
 * will all work as expected.
 */
void MainClass::run()
{
    qDebug() << "MainClass.run is executing...";

    QThread::msleep(200);

    quit();
}

/* call this routine to quit the application */
void MainClass::quit()
{
    /* cleanup code goes here
     * then do emit finished to signal CoreApplication to quit
     */
    emit finished();

}

/* shortly after quit is called the CoreApplication will signal this routine
 * this is a good place to delete any objects that were created in the
 * constructor and/or to stop any threads
 */
void MainClass::aboutToQuitApp()
{
    qDebug() << "about to quit app ...";
    // stop Threads
    QThread::msleep(100);   // wait for threads to stop.
    // delete any objects

}
