#include "Crc.h"

Crc::Crc(uint16_t& start)
: crc16{start}
{
}

uint16_t Crc::calculateCrc16(uint16_t& start, uint8_t& value)
{
    uint16_t crc = start;
    uint8_t i;
    crc = crc ^ (int16_t)value << 8;

    for (i = 0; i < 8; i++) {
        if (crc & 0x8000)
            crc = (crc << 1) ^ 0x1021;
        else
            crc = (crc << 1);
    }
    return crc;
}