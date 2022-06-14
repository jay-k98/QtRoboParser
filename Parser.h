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

    std::uint8_t* parseToSumd(QtRoboEvent event);

    uint16_t crc16(uint16_t crc, uint8_t value);
};
