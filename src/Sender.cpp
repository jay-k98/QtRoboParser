#include "Sender.h"
#include <iostream>

void Sender::send(const std::array<uint8_t, 41> eventFrame) {
    for (size_t i = 0; i < eventFrame.size(); i++)
    {
        std::cout << unsigned(eventFrame.at(i)) << std::endl;
    }
}

std::array<uint8_t, 41> Sender::parseToSumd(const std::array<uint8_t, 32>& data, const Modes& modes, uint8_t functionCode) {
    // 3 Bytes for Header
    // 16 x 2 = 32 Bytes for data
    // 4 Bytes for Func Code, Last valid packages, MODE CMD, SUB CMD
    // 2 Bytes for CRC
    // -> 41 Bytes in total

    std::array<uint8_t, 41> sumd;

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
    sumd.at(37) = modes.MODE_CMD; // MODE CMD
    sumd.at(38) = modes.SUB_CMD; // SUB CMD

    Crc crc16{};
    for (size_t i = 0; i < 35; i++)
    {
        crc16 += sumd.at(i);
    }

    sumd.at(39) = crc16.highByte(); // high byte crs
    sumd.at(40) = crc16.lowByte(); // low byte crc

    return sumd;
}