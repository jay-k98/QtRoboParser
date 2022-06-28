#pragma once
#include <iostream>
#include <array>
#include "QtRoboEvent.h"

constexpr uint8_t base10 {10};

class Parser
{
private:
    std::string m_Prefix;

public:
    Parser(const std::string prefix);
    ~Parser() = default;

    QtRoboEvent parseToQtRoboEvent(char buffer[256]);

    uint16_t crc16(uint16_t crc, uint8_t value);
};
