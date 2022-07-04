#include "Parser.h"
#include "Util.h"
#include <ctype.h>
#include <iostream>
#include <array>
#include <regex>

using namespace std;

enum class ParserState { undefined, prefix, channel, value };

Parser::Parser(const ParserConfig& config)
: m_Config{config}
{
}

    // $Prefix15:56

    // $Prop15:56
    // $MODE
    // $Bin48
    // $SUB

    // Prefix{Prop, Bin, MODE, SUB}
QtRoboEvent Parser::parseToQtRoboEvent(char buffer[256]) {
    string line {buffer};
    uint8_t eventChannel {0};
    uint8_t eventValue {0};
    ParserState currentState {ParserState::undefined};
    QtRoboEventType eventType {QtRoboEventType::binary};
    cout << buffer << endl;

    if (line.at(0) == '$')
    {
        if (line.find(m_Config.bin_prefix) != string::npos)
        {
            eventType = QtRoboEventType::binary;
            sregex_iterator iterator{line.begin(), line.end(), numberRegex};

            for (sregex_iterator i {iterator}; i != sregex_iterator{}; ++i)
            {
                smatch match{*i};
                eventChannel = stoi(match.str());
            }
        }
        if (line.find(m_Config.prop_prefix) != string::npos)
        {
            eventType = QtRoboEventType::proportional;
            sregex_iterator iterator{line.begin(), line.end(), numberRegex};

            size_t idx{0};
            for (sregex_iterator i {iterator}; i != sregex_iterator{}; ++i)
            {
                smatch match{*i};
                if (0 == idx)
                {
                    eventChannel = stoi(match.str());
                }
                if (1 == idx)
                {
                    eventValue = stoi(match.str());
                }
                idx++;
            }
        }
        if (line.find(m_Config.mode_prefix) != string::npos)
        {
            eventType = QtRoboEventType::mode;
        }
        if (line.find(m_Config.sub_prefix) != string::npos)
        {
            eventType = QtRoboEventType::sub;
        }
    }

    return QtRoboEvent{eventChannel, eventValue, eventType};

    /**
    while (*c != '\0') {
        switch(currentState) {
            case ParserState::undefined:
                if (line.at(0) == '$')
                    currentState = ParserState::channel;
                break;
            case ParserState::prefix:

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
    */
}
