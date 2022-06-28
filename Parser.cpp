#include "Parser.h"
#include "Util.h"
#include <ctype.h>
#include <iostream>
#include <array>

using namespace std;

enum class ParserState { undefined, channel, value };

Parser::Parser(const string prefix) {
    m_Prefix = prefix;
}

QtRoboEvent Parser::parseToQtRoboEvent(char buffer[256]) {
    uint8_t eventChannel {0};
    uint8_t eventValue {0};
    ParserState currentState {ParserState::undefined};
    QtRoboEventType eventType {QtRoboEventType::binary};
    cout << buffer << endl;
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
