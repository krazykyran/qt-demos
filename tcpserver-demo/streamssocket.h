#ifndef STREAMSSOCKET_H
#define STREAMSSOCKET_H

#include <QObject>
#include <QTcpSocket>
#include <QHostAddress>

class StreamsSocket : public QTcpSocket
{
    Q_OBJECT
public:
    explicit StreamsSocket(QObject *parent = 0);
    ~StreamsSocket();

signals:


public slots:
    void handleReadyRead();

private:
    QString m_name;
    QHostAddress m_remoteIP;
    quint16 m_remotePort;

};

#endif // STREAMSSOCKET_H
