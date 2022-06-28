#pragma once
#include <bitset>
#include <cstdint>
#include <string>
#include <array>

using namespace std;

class Util {
    public:
        static array<uint8_t, 2> splitUint16ToUint8(uint16_t value);
        static string sumdBytesToString(uint8_t* sumd);
        static int charToInt(char c);
};