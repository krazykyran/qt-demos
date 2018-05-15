#ifndef MYSERVER_H
#define MYSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QTextStream>

class MyServer : public QObject
{
    Q_OBJECT
public:
    explicit MyServer(QObject *parent = 0);

    void init();
signals:

public slots:
    void handleNewConnection();

private:
    QTcpServer *m_server;

};

#endif // MYSERVER_H
