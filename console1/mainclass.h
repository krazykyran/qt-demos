#ifndef MAINCLASS_H
#define MAINCLASS_H

#include <QObject>
#include <QCoreApplication>
#include <QTextStream>
#include <QTimer>

class MainClass : public QObject
{
    Q_OBJECT
public:
    explicit MainClass(QObject *parent = 0);
    ~MainClass();

    void init();
    void printMessage();
signals:
    void finished(int exitCode = 0);

public slots:
    void handleTimer();
    void handleFinished(int exitCode = 0);

protected:
    QCoreApplication *m_app;
    QTimer *m_timer;
};

#endif // MAINCLASS_H
