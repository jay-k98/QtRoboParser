#pragma once
#include <iostream>

class Crc
{
private:
    uint8_t mHighByte;  
    uint8_t mLowByte;
    
public:
    uint8_t highByte() const {
        return mHighByte;
    }

    uint8_t lowByte() const {
        return mLowByte;
    }
};