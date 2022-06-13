#include "Util.h"

using namespace std;

uint8_t* Util::splitUint16ToUint8(uint16_t value) {
    static uint8_t bytes[2];
    bytes[0] = *((uint8_t*) & (value)+1); // high byte
    bytes[1] = *((uint8_t*) & (value)+0); // low byte
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