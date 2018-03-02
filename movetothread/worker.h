#ifndef WORKER_H
#define WORKER_H

#include <QCoreApplication>
#include <QObject>
#include <QTextStream>
#include <QThread>
#include <QElapsedTimer>

class Worker : public QObject
{
    Q_OBJECT
public:
    explicit Worker(QObject *parent = 0);
    ~Worker();

public slots:
    void process();
    void handleSpit(QString msg);
    void handleShutdown();
signals:
    void spit(QString msg);
    void finished();
private:
    const char *m_name;
    bool m_shutdown;
};

#endif // WORKER_H
