#include "tcpconnection.h"

extern QTextStream qout;
extern QTextStream qerr;

TcpConnection::TcpConnection(QObject *parent) : QObject(parent)
{
    qDebug() << this << ": constructor ...";
}

TcpConnection::~TcpConnection()
{
    qDebug() << this << ": destructor ...";
}

void TcpConnection::setSocket(QTcpSocket *socket)
{
    m_socket = socket;
    connect(m_socket, SIGNAL(connected()), this, SLOT(handleConnected()));
    connect(m_socket, SIGNAL(disconnected()), this, SLOT(handleDisconnected()));
    connect(m_socket, SIGNAL(readyRead()), this, SLOT(handleReadyRead()));
    connect(m_socket, SIGNAL(bytesWritten(qint64)), this, SLOT(handleBytesWritten(qint64)));
    connect(m_socket, SIGNAL(stateChanged(QAbstractSocket::SocketState)),
            this, SLOT(handleStateChanged(QAbstractSocket::SocketState)));
    connect(m_socket, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(handleError(QAbstractSocket::SocketError)));
}

QTcpSocket *TcpConnection::getSocket()
{
    if (!sender())
        return 0;
    return static_cast <QTcpSocket*>(sender());
}

void TcpConnection::handleConnected()
{
    if (!sender())
        return;
    qDebug() << this << ": connected ... " << getSocket();
}

void TcpConnection::handleDisconnected()
{
    if (!sender())
        return;
    qDebug() << this << ": disconnected ... " << getSocket();
}

void TcpConnection::handleReadyRead()
{
    if (!sender())
        return;
    QTcpSocket *socket = getSocket();
    QByteArray data = socket->readAll();

    qDebug() << this << ": readyRead ... " << getSocket();
    qDebug() << this << data;


    socket->write(data);
}

void TcpConnection::handleBytesWritten(qint64 bytes)
{
    if (!sender())
        return;
    qDebug() << this << ": bytes Written ... " << getSocket() << " number of bytes = " << bytes;
}

void TcpConnection::handleStateChanged(QAbstractSocket::SocketState socketState)
{
    if (!sender())
        return;
    qDebug() << this << ": stateChanged ... " << getSocket() << " state = " << socketState;
}

void TcpConnection::handleError(QAbstractSocket::SocketError socketError)
{
    if (!sender())
        return;
    qDebug() << this << ": stateChanged ... " << getSocket() << " error = " << socketError;
}
