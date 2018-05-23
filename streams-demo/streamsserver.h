#ifndef STREAMSSERVER_H
#define STREAMSSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTextStream>
#include <QLinkedList>

#include "streamssocket.h"

class StreamsServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit StreamsServer(QObject *parent = 0);
    ~StreamsServer();

    virtual bool listen(const QHostAddress &address, quint16 port);
    virtual void close();

protected:
    QLinkedList<StreamsSocket*> m_connections;
    void closeSocket(StreamsSocket *socket);
    void removeSocket(StreamsSocket *socket);
private:
    void incomingConnection(qintptr descriptor);
    QString m_name;
signals:
    void finished();

public slots:

private slots:
    void handleDisconnectedSocket();
};

#endif // STREAMSSERVER_H
