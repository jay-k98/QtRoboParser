 
#include <Parser.h>
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
                    eventChannel = eventChannel * base10 + charToInt(*c);
                }
                if (*c == ':')
                    currentState = value;
                break;
            case value:
                if (isdigit(*c)) {
                    eventValue = eventValue * base10 + charToInt(*c);
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
    uint8_t sumdHeader[3];
    uint8_t sumdData[2];
    uint8_t sumdCrc[2];
    sumdHeader[0] = 0xA8;
    sumdHeader[1] = 0x01;
    sumdHeader[2] = 0x01;
    sumdData[0] = event.eventChannel();
    sumdData[1] = event.eventValue();
}

int charToInt(char c) {
    return c - '0';
}

uint16_t crc16(uint16_t crc, uint8_t value) {
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