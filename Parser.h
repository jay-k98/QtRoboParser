#pragma once
#include <iostream>
#include <array>
#include "QtRoboEvent.h"

struct ParserConfig
{
    std::string prop_prefix;
    std::string bin_prefix;
    std::string mode_prefix;
    std::string sub_prefix;
};

constexpr uint8_t base10 {10};

class Parser
{
private:
    ParserConfig m_Config;

public:
    Parser(const ParserConfig& config);
    ~Parser() = default;

    QtRoboEvent parseToQtRoboEvent(char buffer[256]);

    uint16_t crc16(uint16_t crc, uint8_t value);
};
