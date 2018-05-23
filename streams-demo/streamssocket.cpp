#include "streamssocket.h"

extern QTextStream qout;
extern QTextStream qerr;

StreamsSocket::StreamsSocket(QObject *parent) : QTcpSocket(parent)
{
    this->setObjectName("StreamsSocket");
    m_name = this->objectName();

    connect(this, SIGNAL(readyRead()), this, SLOT(handleReadyRead()));
    connect(this, SIGNAL(disconnected()), this, SLOT(deleteLater()));

    m_ns = 0;
    m_nr = 0;
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

    qout << "--->" << data.toHex() << endl;

    // append read data to buffer
    m_buffer += data;

    // check buffer for start of header <SOH> byte, (0x01)
    int soh = m_buffer.indexOf(0x01);
    if (soh < 0)
        return;

    // check buffer end of text <ETX> byte, (0x03)
    int etx = m_buffer.indexOf(0x03, soh);
    if (etx < 0)
        return;

    // sanity check etx is after soh byte, if so clean out buffer before <SOH> byte
    if (etx <= soh) {
        m_buffer = m_buffer.remove(0, soh);
        return;
    }

    qout << m_name << ": found frame to process" << endl;
    // buffer contains a streams frame so process it
    QByteArray frame = m_buffer.mid(soh, etx-soh+1);
    processFrame(frame);

    // remove last frame from buffer up to the end of frame <ETX>
    m_buffer = m_buffer.remove(0, etx+1);
    // echo it back
    // this->write(data);
}

void StreamsSocket::processFrame(QByteArray &frame)
{
    // TODO: parse connection layer (sequence numbers, crc, and message)

    // 1. Every packet starts with a start of header <SOH> byte, (0x01)

    int soh_pos = 0;
    char soh = frame.at(soh_pos);
    if (soh != 0x01)
        return;
    // 2. Every packet ends with a end of text <ETX> byte, (0x03)
    int frame_length = frame.length();
    int etx_pos = frame_length-1;
    char etx = frame.at(etx_pos);
    if (etx != 0x03)
        return;

    // 3. check that end > start + a few bytes. What is the minimum message size?
    // we expect 5 bytes before the message, plus 3 bytes at the end. 1 byte minimum for the msg.
    if ( frame_length < 5 ) {
        qerr << m_name << ": message length error! - received " << (etx_pos-soh_pos) << " bytes" << endl;
        return;
    }

    // 4. Every packet has a start of text <STX> byte (0x02)
    int stx_pos = frame.indexOf(0x02, 0);
    if (stx_pos < 0) {
        qerr << m_name << ": start of text byte not found!" << endl;
        return;
    }

    QByteArray header_ascii = frame.mid(soh_pos+1, (stx_pos-1)-(soh_pos+1)+1);
    QByteArray header = QByteArray::fromHex(header_ascii);
    QByteArray packet_ascii = frame.mid(stx_pos+1, (etx_pos-5)-(stx_pos+1)+1);
    QByteArray packet = QByteArray::fromHex(packet_ascii);
    QByteArray crc_ascii = frame.mid(etx_pos-4, 4);
    QByteArray crc = QByteArray::fromHex(crc_ascii);

    qout << "  packet = <SOH>" << header.toHex() << "<STX>" << packet.toHex() << "[" << crc.toHex() << "]<ETX>" << endl;

    // 5. calculate the CRC on all bytes up to (not including) <ETX> byte. Result should be 0x0000.

    quint16 crc_num = (quint8)(crc.at(0)) * 256 + (quint8)(crc.at(1));
    quint16 crc_calc = calcCrc(frame.constData(), frame_length - 5, 0x0000);
    if (crc_calc != crc_num)
        qout << m_name << ": crc error! "
             << "- received " << QByteArray::number(crc_num,16)
             << ", calculated " << QByteArray::number(crc_calc,16) << endl;

    // 6. check the sequence numbers
    int ns = header.at(0);
    int nr = header.at(1);

    if (m_ns == 0)  // start of link - if both m_nr and m_ns are zero, set to first frame from master.
        m_ns = ns;
    if (m_nr == 0)
        m_nr = nr;


    // if packet contains incorrect ns, respond with NAK
    if (ns != m_ns)
        qerr << m_name << ": N(S) sequence error! - received " << ns << ", expected " << m_ns << endl;

    if (nr != m_nr)
        qerr << m_name << ": N(R) sequence error! - recieved " << nr << ", expected " << m_nr << endl;

    // with all frame checks okay, pass on packet for processing.


}

void StreamsSocket::writeResponse(QByteArray &data)
{

    this->write(data);
}

quint16 StreamsSocket::calcCrc(const char *data, int num_bytes, quint16 start_value)
{
    quint16 crc;
    const char *ptr;
    int a;

    if ( ! m_crcTableInit ) initCrcTable();

    crc = start_value;
    ptr = data;

    if ( ptr != NULL ) for (a=0; a<num_bytes; a++) {

        crc = (crc << 8) ^ m_crcTable[ ((crc >> 8) ^ (uint16_t) *ptr++) & 0x00FF ];
    }

    return crc;
}

void StreamsSocket::initCrcTable()
{
    quint16 i;
    quint16 j;
    quint16 crc;
    quint16 c;

    for (i=0; i<256; i++) {

        crc = 0;
        c   = i << 8;

        for (j=0; j<8; j++) {

            if ( (crc ^ c) & 0x8000 ) crc = ( crc << 1 ) ^ 0x1021;  // 0x1021 is the CRC-CCITT polynomian
            else                      crc =   crc << 1;

            c = c << 1;
        }

        m_crcTable[i] = crc;
    }

    m_crcTableInit = true;
}
