#pragma once

#include <array>
#include <cstdint>
#include <atomic>
#include "QtRoboEvent.h"

class Buffer
{
private:
    std::array<uint8_t, 32> funcCode02{};
    std::array<uint8_t, 32> funcCode03{};
    std::array<uint8_t, 32> funcCode04{};
    std::array<uint8_t, 32> funcCode05{};

public:
    Buffer();
    ~Buffer() = default;

    const std::array<uint8_t, 32>& getFunctionCode02();
    const std::array<uint8_t, 32>& getFunctionCode03();
    const std::array<uint8_t, 32>& getFunctionCode04();
    const std::array<uint8_t, 32>& getFunctionCode05();

    void reactToQtRoboEvent(QtRoboEvent event);
};
