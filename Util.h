#pragma once

using namespace std;

class Util {
    public:
        static uint8_t* splitUint16ToUint8(uint16_t value);
        static string sumdBytesToString(uint8_t* sumd);
        static int charToInt(char c);
};