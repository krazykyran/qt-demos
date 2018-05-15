#ifndef SOCKETTEST_H
#define SOCKETTEST_H

#include <QObject>
#include <QTcpSocket>
#include <QTextStream>

class SocketTest : public QObject
{
    Q_OBJECT
public:
    explicit SocketTest(QObject *parent = 0);
    ~SocketTest();

    void init();

signals:

public slots:
    void timerEvent(QTimerEvent *event);
    void handleConnected();
    void handleDisconnected();
    void handleBytesWritten(qint64 bytes);
    void handleReadyRead();
    void handleError(QAbstractSocket::SocketError error);

private:
    int m_loopCount;
    QTcpSocket *m_socket;

};

#endif // SOCKETTEST_H
