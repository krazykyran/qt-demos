#include "sockettest.h"

extern QTextStream qout;

SocketTest::SocketTest(QObject *parent) : QObject(parent)
{

}

void SocketTest::connectSocket()
{
    m_socket = new QTcpSocket(this);
    m_socket->connectToHost("localhost", 80);

    if (m_socket->waitForConnected(3000))
    {
        qout << "connected!" << endl;

        m_socket->write("hello server\r\n\r\n\r\n\r\n");
        m_socket->waitForBytesWritten(1000);
        m_socket->waitForReadyRead(3000);
        qout << "Reading:" << m_socket->bytesAvailable() << endl;
        qout << m_socket->readAll() << endl;

        m_socket->close();

    } else {
        qout << "not connected!" << endl;
    }

    // connected

    // sent data

    // get data

    // closed
}
