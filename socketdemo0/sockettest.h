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

    void connectSocket();

signals:

public slots:

private:

    QTcpSocket *m_socket;

};

#endif // SOCKETTEST_H
