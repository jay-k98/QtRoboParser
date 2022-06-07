#include <Parser.h>
#include <ctype.h>
#include <iostream>

using namespace std;

enum ParserState { undefined, channel, value };

QtRoboEvent Parser::parseToQtRoboEvent() {
    int eventChannel {0};
    int eventValue {0};
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
                    eventChannel = eventChannel * 10 + charToInt(*c);
                }
                if (*c == ':')
                    currentState = value;
                break;
            case value:
                if (isdigit(*c)) {
                    eventValue = eventValue * 10 + charToInt(*c);
                }
                break;
        }
        c++;
    }
    cout << eventChannel << endl;
    cout << eventValue << endl;
    QtRoboEvent event {eventChannel, eventValue};
}

int charToInt(char c) {
    return c - '0';
}