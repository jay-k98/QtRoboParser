#pragma once

#include <array>
#include <cstdint>
#include "QtRoboEvent.h"

constexpr int propBreak {16};
constexpr int propEnd {32};
constexpr int binBreak {64};
constexpr int binEnd {96};

class Buffer
{
private:
    std::array<uint16_t, 16> funcCode02;
    std::array<uint16_t, 16> funcCode03;
    std::array<uint8_t, 32> funcCode04;
    std::array<uint8_t, 32> funcCode05;

public:
    Buffer();
    ~Buffer() = default;

    const std::array<uint16_t, 16>& getFunctionCode02();
    const std::array<uint16_t, 16>& getFunctionCode03();
    const std::array<uint8_t, 32>& getFunctionCode04();
    const std::array<uint8_t, 32>& getFunctionCode05();

    void reactToQtRoboEvent(QtRoboEvent event);
};
