#include "Util.h"

using namespace std;

array<uint8_t, 2> Util::splitUint16ToUint8(uint16_t value) {
    array<uint8_t, 2> bytes;
    bytes.at(0) = value & 0xff; // high byte
    bytes.at(1) = (value >> 8); // low byte
    return bytes;
}

string Util::sumdBytesToString(uint8_t* sumd) {
    string out {""};
    uint8_t *b = sumd;
    for(int i {0}; i < 9; i++) {
        bitset<8> bits(*b);
        out += bits.to_string();
        b++;
    }
    return out;
}

int Util::charToInt(char c) {
    return c - '0';
}