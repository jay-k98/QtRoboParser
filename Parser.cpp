 
#include "Parser.h"
#include "Util.h"
#include <ctype.h>
#include <iostream>
#include <array>

using namespace std;

constexpr uint8_t base10 {10};

enum class ParserState { undefined, channel, value };

Parser::Parser(const char* prefix) {
    m_Prefix = prefix;
}

QtRoboEvent Parser::parseToQtRoboEvent(char buffer[256]) {
    uint8_t eventChannel {0};
    uint8_t eventValue {0};
    ParserState currentState {ParserState::undefined};
    QtRoboEventType eventType {QtRoboEventType::binary};
    cout << buffer << endl;;
    char *c = buffer;
    bool valueReached {false};
    while (*c != '\0') {
        switch(currentState) {
            case ParserState::undefined:
                if (*c == '$')
                    currentState = ParserState::channel;
                break;
            case ParserState::channel:
                if (isdigit(*c)) {
                    eventChannel = eventChannel * base10 + Util::charToInt(*c);
                }
                if (*c == ':')
                    currentState = ParserState::value;
                    valueReached = true;
                break;
            case ParserState::value:
                if (isdigit(*c)) {
                    eventValue = eventValue * base10 + Util::charToInt(*c);
                }
                break;
        }
        c++;
    }

    if (valueReached)
        eventType = QtRoboEventType::proportional;

    return QtRoboEvent{eventChannel, eventValue, eventType};
}


array<uint8_t, 9> Parser::parseToSumd(const QtRoboEvent& event) {
    array<uint8_t, 9> sumd;
    // header
    sumd[0] = 0xA8;
    sumd[1] = 0x03;
    sumd[2] = 0x12;
    // data
    uint8_t* channelData {Util::splitUint16ToUint8(event.eventChannel())};
    uint8_t* valueData {Util::splitUint16ToUint8(event.eventValue())};
    sumd[3] = *channelData;
    channelData++;
    sumd[4] = *channelData;
    sumd[5] = *valueData;
    valueData++;
    sumd[6] = *valueData;
    // crc - 42 as placeholder
    uint16_t crc {crc16(42, 42)};
    uint8_t* crcSumd {Util::splitUint16ToUint8(crc)};
    sumd[7] = *crcSumd;
    crcSumd++;
    sumd[8] = *crcSumd;
    return sumd;
}

uint16_t Parser::crc16(uint16_t crc, uint8_t value) {
    uint8_t i;
    crc = crc ^ (int16_t)value << 8;

    for (i = 0; i < 8; i++) {
        if (crc & 0x8000)
            crc = crc << 1 ^ 0x1021;
        else
            crc = crc << 1;
    }
    return crc;
}