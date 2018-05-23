#ifndef STREAMSDEVICE_H
#define STREAMSDEVICE_H

#include <QObject>
#include <QSerialPort>

class StreamsDevice : public QObject
{
    Q_OBJECT
public:
    enum State {
        OffState,
        SleepState,
        ConnectedState,
        DisconnectedState
    };
    Q_ENUM(State)

    enum Error {
        NoError,
        ReadError,
        WriteError,
        ConnectionError,
        ConfigurationError,
        TimeoutError,
        ProtocolError,
        ReplyAbortedError,
        UnknownError
    };
    Q_ENUM(Error)

    enum ConnectionParameter {
        SerialPortNameParameter,
        SerialParityParameter,
        SerialBaudRateParameter,
        SerialDataBitsParameter,
        SerialStopBitsParameter,
        NetworkPortParameter,
        NetworkAddressParameter,
        // Reserved
        UserParameter = 0x100
    };
    Q_ENUM(ConnectionParameter)

    explicit StreamsDevice(QObject *parent = nullptr);
    ~StreamsDevice();


    QVariant connectionParameter(int parameter) const;
    void setConnectionParameter(int parameter, const QVariant &value);

    bool connectDevice();
    void disconnectDevice();

    State state() const;
    Error error() const;
    QString errorString() const;

signals:
    void errorOccurred(StreamsDevice::Error error);
    void stateChanged(StreamsDevice::State state);

protected:
    StreamsDevice(StreamsDevice &d, QObject *parent = nullptr);

    void setState(StreamsDevice::State state);
    void setError(StreamsDevice::Error error);

    virtual bool open() = 0;
    virtual bool close() = 0;


private:
    quint8 m_deviceId;
    State m_state;
    Error m_error;
    QString m_errorString;

    QString m_comPort;
    QSerialPort::DataBits m_dataBits = QSerialPort::Data8;
    QSerialPort::Parity m_parity = QSerialPort::NoParity;
    QSerialPort::StopBits m_stopBits = QSerialPort::OneStop;
    QSerialPort::BaudRate m_baudRate = QSerialPort::Baud9600;

    int m_networkPort = 2000;
    QString m_networkAddress = QStringLiteral("127.0.0.1");

    QHash<int, QVariant> m_connectionParams;

public slots:

};


Q_DECLARE_TYPEINFO(StreamsDevice::Error, Q_PRIMITIVE_TYPE);
Q_DECLARE_TYPEINFO(StreamsDevice::State, Q_PRIMITIVE_TYPE);
Q_DECLARE_TYPEINFO(StreamsDevice::ConnectionParameter, Q_PRIMITIVE_TYPE);

#endif // STREAMSDEVICE_H
