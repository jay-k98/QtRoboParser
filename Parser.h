#pragma once
#include <iostream>
#include <array>
#include "QtRoboEvent.h"

constexpr uint8_t base10 {10};

class Parser
{
private:
    const char* m_Prefix;

public:
    Parser(const char* prefix);
    ~Parser() = default;

    QtRoboEvent parseToQtRoboEvent(char buffer[256]);

    std::array<uint8_t, 41> parseToSumd(const QtRoboEvent& event);

    uint16_t crc16(uint16_t crc, uint8_t value);
};
