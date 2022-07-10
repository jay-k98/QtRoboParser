#pragma once

#include <iostream>
#include <array>
#include <regex>
#include "QtRoboEvent.h"

struct ParserConfig
{
    std::string prop_prefix;
    std::string bin_prefix;
    std::string mode_prefix;
    std::string sub_prefix;

    bool incomplete()
    {
        return prop_prefix.empty() || bin_prefix.empty() || mode_prefix.empty() || sub_prefix.empty();
    }

    friend std::ostream& operator<<(std::ostream& out, const ParserConfig& cfg)
    {
        out << "Launched with the following arguments:\n"
         << cfg.prop_prefix << "\n"
         << cfg.bin_prefix << "\n"
         << cfg.mode_prefix << "\n"
         << cfg.sub_prefix << "\n";
        return out;
    }
};

constexpr uint8_t base10 {10};
const std::regex numberRegex {"\\d+", std::regex_constants::ECMAScript};

class Parser
{
private:
    ParserConfig m_Config;

public:
    Parser(const ParserConfig& config);
    ~Parser() = default;

    QtRoboEvent parseToQtRoboEvent(std::array<char, 256>& buffer);

    uint16_t crc16(uint16_t crc, uint8_t value);
};
