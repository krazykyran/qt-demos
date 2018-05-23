#include "rtasignpdu.h"

RtaSignPdu::RtaSignPdu()
{

}

RtaSignPdu::~RtaSignPdu()
{

}

void RtaSignPdu::frameDecode(QByteArray &frame)
{

}

bool RtaSignPdu::frameCrcCheck(QByteArray &frame)
{
    int c = 0;
    for (int c = 0; c <= (frame.length()-3); c++) {

    }
}
