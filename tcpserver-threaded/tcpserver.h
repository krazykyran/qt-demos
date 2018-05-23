#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QObject>
#include <QDebug>
#include <QThread>
#include <QTcpServer>

#include "tcpconnection.h"
#include "tcpconnections.h"

class TcpServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit TcpServer(QObject *parent = 0);
    ~TcpServer();

    virtual bool listen(const QHostAddress &address, quint16 port);
    virtual void close();
    virtual qint64 port();

protected:
    TcpConnections *m_connections;
    QThread *m_thread;
    virtual void incomingConnection(qintptr descriptor);
    virtual void accept(qintptr descriptor, TcpConnection *connection);

signals:
    void accepting(qintptr handle, TcpConnection *connection);
    void finished();

public slots:
    void complete();
};

#endif // TCPSERVER_H
