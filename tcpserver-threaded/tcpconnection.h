#ifndef TCPCONNECTION_H
#define TCPCONNECTION_H

#include <QObject>
#include <QTextStream>
#include <QDebug>
#include <QTcpSocket>

class TcpConnection : public QObject
{
    Q_OBJECT
public:
    explicit TcpConnection(QObject *parent = 0);
    ~TcpConnection();

    virtual void setSocket(QTcpSocket *socket);

protected:
    QTcpSocket *m_socket;
    QTcpSocket *getSocket();

signals:

public slots:
    virtual void handleConnected();
    virtual void handleDisconnected();
    virtual void handleReadyRead();
    virtual void handleBytesWritten(qint64 bytes);
    virtual void handleStateChanged(QAbstractSocket::SocketState socketState);
    virtual void handleError(QAbstractSocket::SocketError socketError);

};

#endif // TCPCONNECTION_H
