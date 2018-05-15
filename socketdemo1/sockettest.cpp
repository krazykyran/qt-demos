#include "sockettest.h"

extern QTextStream qout;
extern QTextStream qerr;

SocketTest::SocketTest(QObject *parent) : QObject(parent)
{
    m_socket = nullptr;
    m_loopCount = 0;
}

SocketTest::~SocketTest()
{
    if (m_socket) delete m_socket;
}

void SocketTest::init()
{
    m_socket = new QTcpSocket(this);

    connect(m_socket, SIGNAL(connected()), this, SLOT(handleConnected()));
    connect(m_socket, SIGNAL(disconnected()), this, SLOT(handleDisconnected()));
    connect(m_socket, SIGNAL(bytesWritten(qint64)), this, SLOT(handleBytesWritten(qint64)));
    connect(m_socket, SIGNAL(readyRead()), this, SLOT(handleReadyRead()));

    connect(m_socket, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(handleError(QAbstractSocket::SocketError)));

    qout << "TCP socket connecting ..." << endl;
    m_socket->connectToHost("localhost", 80);

    if (!m_socket->waitForConnected(3000))
    {
        qerr << "socket error: " << m_socket->errorString() << endl;
        ::exit(EXIT_FAILURE);
        return;
    }

    startTimer(1000);

}

void SocketTest::timerEvent(QTimerEvent *event)
{
    if (m_loopCount == 0) {
        ;
    }

    if (m_loopCount == 1) {
        ;
    }

}

void SocketTest::handleConnected()
{
    qout << "connected!" << endl;
    m_socket->write("HEAD / HTTP/1.0\r\n\r\n\r\n\r\n");
}

void SocketTest::handleDisconnected()
{
    qout << "disconnected!" << endl;
}

void SocketTest::handleBytesWritten(qint64 bytes)
{
    qout << "bytes written: " << bytes << endl;
}

void SocketTest::handleReadyRead()
{
    qout << "data received: " << m_socket->readAll() << endl;
}

void SocketTest::handleError(QAbstractSocket::SocketError error)
{
    ;
}
