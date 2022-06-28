#include <string>
#include <array>
#include "QtRoboEvent.h"

using namespace std;

class Sender
{
    public:
        const string readBufferAsBytes(const uint8_t funcCode);
        void send(const array<uint8_t, 41> buffer);
        array<uint8_t, 41> parseToSumd(const std::array<uint8_t, 32>& data, uint8_t functionCode);
        uint16_t crc16(uint16_t crc, uint8_t value);
};
