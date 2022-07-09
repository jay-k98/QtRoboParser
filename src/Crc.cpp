#include "Crc.h"

Crc::Crc(uint16_t& start)
: crc16{start}
{
}

uint8_t Crc::highByte() const {
    return crc16 & 0xff;;
}

uint8_t Crc::lowByte() const {
    return (crc16 >> 8);;
}

Crc& Crc::operator+=(const uint8_t& rhs)
{
    uint8_t i;
    crc16 = crc16 ^ (int16_t)rhs << 8;

    for (i = 0; i < 8; i++)
    {
        if (crc16 & 0x8000)
            crc16 = (crc16 << 1) ^ 0x1021;
        else
            crc16 = (crc16 << 1);
    }
    return *this;
}
