#pragma once

#include <iostream>
#include <array>

class Crc
{
private:
    uint16_t crc16{};
    
public:
    Crc() = default;
    Crc(uint16_t& start);

    uint8_t highByte() const;
    uint8_t lowByte() const;

    Crc& operator+=(const uint8_t& rhs);
};