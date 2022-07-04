#pragma once
#include <iostream>
#include <array>

class Crc
{
private:
    uint16_t crc16{};
    uint16_t calculateCrc16(uint16_t& start, uint8_t& value);
    
public:
    Crc() = default;
    Crc(uint16_t& start);

    uint8_t highByte() const {
        return crc16 & 0xff;;
    }

    uint8_t lowByte() const {
        return (crc16 >> 8);;
    }

    Crc& operator+=(const uint8_t& rhs)
    {
        uint8_t value = rhs;
        this->crc16 = calculateCrc16(this->crc16, value);
        return *this;
    }

};