#pragma once
#include <iostream>
#include <QtRoboEvent.h>


class Parser
{
private:
    char* m_buffer;
    char* m_Prefix;

public:
    Parser(char* buffer, char* prefix);
    ~Parser() = default;

    QtRoboEvent parseToQtRoboEvent();

    std::uint8_t* parseToSumd(QtRoboEvent event);
};
