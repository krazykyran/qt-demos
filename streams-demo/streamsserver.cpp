#include "streamsserver.h"

extern QTextStream qout;
extern QTextStream qerr;

StreamsServer::StreamsServer(QObject *parent) : QTcpServer(parent)
{
    this->setObjectName("StreamsServer");
    m_name = this->objectName();
}

StreamsServer::~StreamsServer()
{

}

bool StreamsServer::listen(const QHostAddress &address, quint16 port)
{
    if (!QTcpServer::listen(address, port))
        return false;

    qout << m_name << ": server started" << endl;

    return true;
}

void StreamsServer::close()
{
    qout << m_name << ": closing connections ..." << endl;

    foreach(StreamsSocket *socket, m_connections)
        closeSocket(socket);

    QTcpServer::close();
    qout << m_name << ": server stopped" << endl;
    emit finished();
}

void StreamsServer::closeSocket(StreamsSocket *socket)
{
    if (!socket)
        return;

    if (socket->isOpen()) {
        qout << m_name << ": closing connection to "
             << socket->peerAddress().toString() << ":"
             << socket->peerPort() << endl;
        socket->close();
    }
}

void StreamsServer::removeSocket(StreamsSocket *socket)
{
    if (!socket)
        return;

    if (!m_connections.contains(socket))
        return;

    m_connections.removeOne(socket);
    socket->deleteLater();
    qout << m_name << ": number of connections = " << m_connections.count() << endl;
}

void StreamsServer::incomingConnection(qintptr descriptor)
{
    StreamsSocket *socket = new StreamsSocket(this);
    socket->setSocketDescriptor(descriptor);
    qout << m_name << ": incoming connection from "
         << socket->peerAddress().toString() << ":"
         << QString::number(socket->peerPort()) << endl;

    connect(socket, SIGNAL(disconnected()), this, SLOT(handleDisconnectedSocket()));

    m_connections.append(socket);
    qout << m_name << ": number of connections = " << QString::number(m_connections.count()) << endl;
}

void StreamsServer::handleDisconnectedSocket()
{
    if (!sender())
        return;

    StreamsSocket *socket = static_cast <StreamsSocket*>(sender());

    qout << m_name << ": connection closed to "
         << socket->peerAddress().toString() << ":"
         << socket->peerPort() << endl;

    removeSocket(socket);
}
