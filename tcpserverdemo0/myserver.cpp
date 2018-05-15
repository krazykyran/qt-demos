#include "myserver.h"

extern QTextStream qout;
extern QTextStream qerr;

MyServer::MyServer(QObject *parent) : QObject(parent)
{
    m_server = nullptr;
}

void MyServer::init()
{
    m_server = new QTcpServer(this);

    connect(m_server, SIGNAL(newConnection()), this, SLOT(handleNewConnection()));

    if (!m_server->listen(QHostAddress::AnyIPv4, 2000)) {
        qerr << "Server could not start!" << endl;
        ::exit(EXIT_FAILURE);
        return;
    }
    else {
        qout << "Server started!" << endl;
    }

}

void MyServer::handleNewConnection()
{
    QTcpSocket *socket = m_server->nextPendingConnection();

    socket->write("hello client\r\n");
    socket->flush();

    socket->waitForBytesWritten(3000);
    socket->close();
}


