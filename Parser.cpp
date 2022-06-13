 
#include "Parser.h"
#include "Util.h"
#include <ctype.h>
#include <iostream>

using namespace std;

enum ParserState { undefined, channel, value };

QtRoboEvent Parser::parseToQtRoboEvent() {
    uint8_t eventChannel {0};
    uint8_t eventValue {0};
    uint8_t base10 {10};
    ParserState currentState = undefined;
    char *c = m_buffer;
    while (*c != '\0') {
        switch(currentState) {
            case undefined:
                if (*c == '$')
                    currentState = channel;
                break;
            case channel:
                if (isdigit(*c)) {
                    eventChannel = eventChannel * base10 + Util::charToInt(*c);
                }
                if (*c == ':')
                    currentState = value;
                break;
            case value:
                if (isdigit(*c)) {
                    eventValue = eventValue * base10 + Util::charToInt(*c);
                }
                break;
        }
        c++;
    }
    cout << eventChannel << endl;
    cout << eventValue << endl;
    QtRoboEvent event {eventChannel, eventValue};
}


uint8_t* Parser::parseToSumd(QtRoboEvent event) {
    static uint8_t sumd[9];
    // header
    sumd[0] = 0xA8;
    sumd[1] = 0x01;
    sumd[2] = 0x02; // 2 channels one for eventChannel, other for eventValue
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