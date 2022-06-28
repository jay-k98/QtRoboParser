#include "Sender.h"
#include "Util.h"
#include <iostream>

using namespace std;

const string Sender::readBufferAsBytes(const uint8_t funcCode) {
    string sumdBytes {""};
    return sumdBytes;
}

void send(const array<uint8_t, 41> eventFrame) {
    cout << eventFrame.at(0) << endl;
}


array<uint8_t, 41> Sender::parseToSumd(const std::array<uint8_t, 32>& data, uint8_t functionCode) {
    // 3 Bytes for Header
    // 16 x 2 = 32 Bytes for data
    // 4 Bytes for Func Code, Last valid packages, MODE CMD, SUB CMD
    // 2 Bytes for CRC
    // -> 41 Bytes in total

    array<uint8_t, 41> sumd;

    // header
    sumd.at(0) = 0xA8;
    sumd.at(1) = 0x03;
    sumd.at(2) = 0x12;
    
    for (size_t i = 3; i < 35; i++)
    {
        sumd.at(i) = data.at(i - 3);
    }

    // All bits set up to index 34

    sumd.at(35) = functionCode;
    sumd.at(36) = 0x00; // last valid package
    sumd.at(37) = 0x00; // MODE CMD
    sumd.at(38) = 0x00; // SUB CMD

    uint16_t crc = 0x00;

    for (size_t i = 0; i < 35; i++)
    {
        crc = crc16(crc, sumd.at(i));
    }

    array<uint8_t, 2> crcValues = Util::splitUint16ToUint8(crc);
    sumd.at(39) = crcValues.at(0); // high byte crs
    sumd.at(40) = crcValues.at(1); // low byte crc

    return sumd;
}

uint16_t Sender::crc16(uint16_t crc, uint8_t value) {
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