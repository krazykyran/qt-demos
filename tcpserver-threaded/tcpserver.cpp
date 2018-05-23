#include "tcpserver.h"

TcpServer::TcpServer(QObject *parent) : QTcpServer(parent)
{
    qDebug() << this << "constructor ...";
}

TcpServer::~TcpServer()
{
    qDebug() << this << "destructor ...";
}

bool TcpServer::listen(const QHostAddress &address, quint16 port)
{
    if (!QTcpServer::listen(address, port))
        return false;

    m_thread = new QThread(this);
    m_connections = new TcpConnections();

    qRegisterMetaType<qintptr>("qintptr");
    connect(m_thread, SIGNAL(started()), m_connections, SLOT(start()), Qt::QueuedConnection);
    connect(this, SIGNAL(accepting(qintptr,TcpConnection*)),
            m_connections, SLOT(accept(qintptr,TcpConnection*)), Qt::QueuedConnection);
    connect(this, SIGNAL(finished()), m_connections, SLOT(quit()), Qt::QueuedConnection);
    connect(m_connections, SIGNAL(finished()), this, SLOT(complete()), Qt::QueuedConnection);

    m_connections->moveToThread(m_thread);
    m_thread->start();

    return true;
}

void TcpServer::close()
{
    qDebug() << this << "closing server";
    emit finished();
    QTcpServer::close();
}

qint64 TcpServer::port()
{
    if (isListening()) {
        return this->serverPort();
    }
    else {
        return 1000;
    }
}

void TcpServer::incomingConnection(qintptr descriptor)
{
    qDebug() << this << "attempting to accept connection" << descriptor;
    TcpConnection *connection = new TcpConnection();
    accept(descriptor, connection);
}

void TcpServer::accept(qintptr descriptor, TcpConnection *connection)
{
    qDebug() << this << "accepting the connection" << descriptor;
    connection->moveToThread(m_thread);
    emit accepting(descriptor, connection);
}

void TcpServer::complete()
{
    if (!m_thread) {
        qWarning() << this << "exiting complete there was no thread!";
        return;
    }

    qDebug() << this << "complete called, destroying thread";
    delete m_connections;

    qDebug() << this << "quitting thread";
    m_thread->quit();
    m_thread->wait();
    delete m_thread;
    qDebug() << this << "complete";
}
