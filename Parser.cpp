 
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


array<uint8_t, 73> Parser::parseToSumd(const QtRoboEvent& event) {
    // 3 Bytes for Header#
    // 32 x 2 = 64 Bytes for data
    // 4 Bytes for Func Code, Last valid packages, MODE CMD, SUB CMD
    // 2 Bytes for CRC
    // -> 73 Bytes in total
    array<uint8_t, 73> sumd;
    // header
    sumd[0] = 0xA8;
    sumd[1] = 0x03;
    sumd[2] = 0x12;
    // data
    
    // crc - 42 as placeholder
    
    return sumd;
}

uint16_t Parser::crc16(uint16_t crc, uint8_t value) {
    uint8_t i;
    crc = crc ^ (int16_t)value << 8;

    for (i = 0; i < 8; i++) {
        if (crc & 0x8000)
            crc = (crc << 1) ^ 0x1021;
        else
            crc = (crc << 1);
    }
    return crc;
}