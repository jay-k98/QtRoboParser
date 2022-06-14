#pragma once
#include <iostream>
#include "QtRoboEvent.h"


class Parser
{
private:
    const char* m_Prefix;

public:
    Parser(const char* prefix);
    ~Parser() = default;

    QtRoboEvent parseToQtRoboEvent(char buffer[256]);

    array<uint8_t, 9> parseToSumd(const QtRoboEvent& event);

    uint16_t crc16(uint16_t crc, uint8_t value);
};
