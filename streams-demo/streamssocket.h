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

protected:
    void processFrame(QByteArray &frame);

    void writeResponse(QByteArray &data);

    // QByteArray hexDump(QByteArray &data, char separator);

    QByteArray m_buffer;
    int m_nr;
    int m_ns;

private:
    quint16 calcCrc(const char *data, int num_bytes, quint16 start_value);
    void initCrcTable();
    bool m_crcTableInit = false;
    quint16 m_crcTable[256];

    QString m_name;
    QHostAddress m_remoteIP;
    quint16 m_remotePort;

};

#endif // STREAMSSOCKET_H
