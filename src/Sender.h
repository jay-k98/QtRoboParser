#pragma once

#include <string>
#include <array>
#include "QtRoboEvent.h"
#include "Buffer.h"
#include "Crc.h"

class Sender
{
    public:
        Sender() = delete;
        ~Sender() = default;
        Sender(Sender& orig) = delete;
        Sender& operator=(Sender& orig) = delete;

        static void send(const std::array<uint8_t, 41> buffer);
        static std::array<uint8_t, 41> parseToSumd(const std::array<uint8_t, 32>& data, const Modes& modes, uint8_t functionCode);
};
