#include "streamssocket.h"

extern QTextStream qout;
extern QTextStream qerr;

StreamsSocket::StreamsSocket(QObject *parent) : QTcpSocket(parent)
{
    this->setObjectName("StreamsSocket");
    m_name = this->objectName();

    connect(this, SIGNAL(readyRead()), this, SLOT(handleReadyRead()));
    connect(this, SIGNAL(disconnected()), this, SLOT(deleteLater()));
}

StreamsSocket::~StreamsSocket()
{

}

void StreamsSocket::handleReadyRead()
{
    QByteArray data = readAll();


    qout << m_name << ": incoming data from "
         << this->peerAddress().toString() << ":"
         << this->peerPort() << endl;

    qout << "--->" << data << endl;

    // echo it back
    // this->write(data);
}

