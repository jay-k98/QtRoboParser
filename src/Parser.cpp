#include "Parser.h"
#include <ctype.h>
#include <iostream>
#include <array>
#include <regex>

Parser::Parser(const ParserConfig& config)
: m_Config{config}
{
}

// $Prefix15:56
// $Prop15:56
// $MODE
// $Bin48
// $SUB
QtRoboEvent Parser::parseToQtRoboEvent(std::array<char, 256>& buffer)
{
    std::string line {std::begin(buffer), std::end(buffer)};

    if (line.at(0) == '$')
    {
        uint8_t eventChannel {0};
        uint8_t eventValue {0};
        QtRoboEventType eventType {QtRoboEventType::binary};
        if (line.find(m_Config.bin_prefix) != std::string::npos)
        {
            eventType = QtRoboEventType::binary;
            std::sregex_iterator iterator{line.begin(), line.end(), numberRegex};

            for (std::sregex_iterator i {iterator}; i != std::sregex_iterator{}; ++i)
            {
                std::smatch match{*i};
                eventChannel = stoi(match.str());
            }
        }
        else if (line.find(m_Config.prop_prefix) != std::string::npos)
        {
            eventType = QtRoboEventType::proportional;
            std::sregex_iterator iterator{line.begin(), line.end(), numberRegex};

            std::size_t idx{0};
            for (std::sregex_iterator i {iterator}; i != std::sregex_iterator{}; ++i)
            {
                std::smatch match{*i};
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
        else if (line.find(m_Config.mode_prefix) != std::string::npos)
        {
            eventType = QtRoboEventType::mode;
        }
        else if (line.find(m_Config.sub_prefix) != std::string::npos)
        {
            eventType = QtRoboEventType::sub;
        }
        return QtRoboEvent{eventChannel, eventValue, eventType};
    }

    std::cerr << "Message from Socket is not a QtRoboEvent (Does not start with $)" << std::endl;
    return QtRoboEvent{0, 0, QtRoboEventType::error};
}
