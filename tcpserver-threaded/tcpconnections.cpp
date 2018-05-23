#include "tcpconnections.h"

TcpConnections::TcpConnections(QObject *parent) : QObject(parent)
{
    qDebug() << this << "constructor ...";
}

TcpConnections::~TcpConnections()
{
    qDebug() << this << "destructor ...";
}

int TcpConnections::count()
{
    QReadWriteLock lock;
    lock.lockForRead();
    int c = m_connections.count();
    lock.unlock();
    return c;
}

void TcpConnections::removeSocket(QTcpSocket *socket)
{
    if (!socket)
        return;
    if (!m_connections.contains(socket))
        return;
    qDebug() << this << "removing socket =" << socket;

    if (socket->isOpen()) {
        qDebug() << this << "socket is open, attempting to close it" << socket;
        socket->disconnect();
        socket->close();
    }
    qDebug() << this << "deleting socket from list" << socket;
    m_connections.remove(socket);
    socket->deleteLater();
    qDebug() << this << "client count =" << m_connections.count();
}

void TcpConnections::handleDisconnected()
{
    if (!sender())
        return;
    qDebug() << this << "disconnecting socket" << sender();

    QTcpSocket *socket = static_cast<QTcpSocket*>(sender());
    if (!socket)
        return;
    removeSocket(socket);
}

void TcpConnections::handleError(QAbstractSocket::SocketError socketError)
{
    if (!sender())
        return;
    qDebug() << this << "error in socket" << sender() << "error =" << socketError;

    QTcpSocket *socket = static_cast<QTcpSocket*>(sender());
    if (!socket)
        return;
    removeSocket(socket);
}

void TcpConnections::start()
{
    qDebug() << this << "connections started on" << QThread::currentThread();
}

void TcpConnections::quit()
{
    if (!sender())
        return;
    qDebug() << this << "connections quitting";
    foreach(QTcpSocket *socket, m_connections.keys()) {
        qDebug() << this << "closing socket" << socket;
        removeSocket(socket);
    }
    qDebug() << this << "finishing";
    emit finished();
}

void TcpConnections::accept(qintptr handle, TcpConnection *connection)
{
    QTcpSocket *socket = new QTcpSocket(this);
    if (!socket->setSocketDescriptor(handle)) {
        qWarning() << this << "could not accept connection" << handle;
        connection->deleteLater();
        return;
    }
    connect(socket, SIGNAL(disconnected()), this, SLOT(handleDisconnected()));
    connect (socket, SIGNAL(error(QAbstractSocket::SocketError)),
             this, SLOT(handleError(QAbstractSocket::SocketError)));

    connection->moveToThread(QThread::currentThread());
    connection->setSocket(socket);

    m_connections.insert(socket, connection);

    qDebug() << this << "clients =" << m_connections.count();
    emit socket->connected();
}
