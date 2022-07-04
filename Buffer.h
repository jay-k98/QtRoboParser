#pragma once

#include <array>
#include <cstdint>
#include <mutex>
#include "QtRoboEvent.h"

struct Modes
{
    uint8_t MODE_CMD;
    uint8_t SUB_CMD;
};


class Buffer
{
private:
    std::array<uint8_t, 32> funcCode02{};
    std::array<uint8_t, 32> funcCode03{};
    std::array<uint8_t, 32> funcCode04{};
    std::array<uint8_t, 32> funcCode05{};
    Modes m_modes{};

    std::mutex mutex_func02;
    std::mutex mutex_func03;
    std::mutex mutex_func04;
    std::mutex mutex_func05;
    std::mutex mutex_modes;

public:
    Buffer();
    ~Buffer() = default;

    const std::array<uint8_t, 32> functionCode02();
    const std::array<uint8_t, 32> functionCode03();
    const std::array<uint8_t, 32> functionCode04();
    const std::array<uint8_t, 32> functionCode05();
    const Modes modes();

    void reactToQtRoboEvent(QtRoboEvent event);
};
