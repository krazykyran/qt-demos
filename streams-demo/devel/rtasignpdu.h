#ifndef RTASIGNPDU_H
#define RTASIGNPDU_H

#include "QCoreApplication"
#include <QByteArray>

class RtaSignPdu
{
public:
    enum MessageCode {
        Reject = 0x00,
        Acknowledge = 0x01,
        SessionStart = 0x02,
        PasswordSeed = 0x03,
        Password = 0x04,
        HeartbeatPoll = 0x05,
        SignStatusReply = 0x06,
        SessionEnd = 0x07,
        SystemReset = 0x08,
        TimeUpdate = 0x09,
        SignFrameTextSet = 0x0A,
        SignFrameGraphicsSet = 0x0B,
        SignMessageSet = 0x0C,
        SignPlanSet = 0x0D,
        SignFrameDisplay = 0x0E,
        SignMessageDisplay = 0x0F,
        SignPlanEnable = 0x10,
        SignPlanDisable = 0x11,
        SignPlanRequestEnabled = 0x12,
        SignPlanReportEnabled = 0x13,
        SignDimmingLevelSet = 0x14,
        SystemPower = 0x15,
        SystemDeviceGroupEnable = 0x16,
        SignFrameMessagePlanRequest = 0x17,
        FaultLogRequest = 0x18,
        FaultLogResponse = 0x19,
        FaultLogReset = 0x1A,
        SignStatusExtRequest = 0x1B,
        SignStatusExtResponse = 0x1C,
        DeviceManufMessageF1 = 0xF0,
        DeviceManufMessageF2 = 0xF1,
        DeviceManufMessageFF = 0xFF,

    };

    RtaSignPdu();
    ~RtaSignPdu();

    void frameDecode(QByteArray &frame);

protected:
    void setAddr(int addr) { m_addr = qBound(0, addr, 255); }
    int addr() { return m_addr; }
    void setNS(int ns) { m_ns = qBound(0x00, ns, 0xFF); }
    int ns() { return m_ns; }
    void setNR(int ns) { m_nr = qBound(0x00, nr, 0xFF); }
    int nr() { return m_nr; }

    bool frameCrcCheck(QByteArray &frame);

private:
    quint8 m_addr;  // address id of the sign
    quint8 m_nr;    //
    quint8 m_ns;
    quint16 m_crc;
};

#endif // RTASIGNPDU_H
