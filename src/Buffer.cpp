#include "Buffer.h"

const std::array<uint8_t, 32> Buffer::functionCode02()
{
    std::lock_guard<std::mutex> guard(mutex_func02);
    return funcCode02;
}

const std::array<uint8_t, 32> Buffer::functionCode03()
{
    std::lock_guard<std::mutex> guard(mutex_func03);
    return funcCode03;
}

const std::array<uint8_t, 32> Buffer::functionCode04()
{
    std::lock_guard<std::mutex> guard(mutex_func04);
    return funcCode04;
}

const std::array<uint8_t, 32> Buffer::functionCode05()
{
    std::lock_guard<std::mutex> guard(mutex_func05);
    return funcCode05;
}

const Modes Buffer::modes()
{
    std::lock_guard<std::mutex> guard(mutex_modes);
    return m_modes;
}

void Buffer::reactToQtRoboEvent(QtRoboEvent event)
{
    constexpr uint8_t propBreak {16};
    constexpr uint8_t propEnd {32};
    constexpr uint8_t binBreak {64};
    constexpr uint8_t binEnd {96};
    
    if (QtRoboEventType::proportional == event.eventType())
    {
        size_t index{event.eventChannel() * 2U};
        if (event.eventChannel() < propBreak)
        {
            std::lock_guard<std::mutex> guard(mutex_func02);
            funcCode02.at(index) = 0x00;
            funcCode02.at(index + 1) = event.eventValue();
        }
        else if (event.eventChannel() >= propBreak && event.eventChannel() < propEnd)
        {
            std::lock_guard<std::mutex> guard(mutex_func03);
            funcCode03.at(index - propEnd) = 0x00;
            funcCode03.at(index - propEnd + 1) = event.eventValue();
        }
        else
        {
            std::cerr << "Wrong channel for proportional event!" << std::endl;
        }
    }
    else if (QtRoboEventType::binary == event.eventType())
    {
        size_t index{event.eventChannel() - propEnd - 1U};
        if (event.eventChannel() >= propEnd && event.eventChannel() < binBreak)
        {
            std::lock_guard<std::mutex> guard(mutex_func04);
            funcCode04.at(index) ^= 1UL << 0;
        }
        else if (event.eventChannel() >= binBreak && event.eventChannel() < binEnd)
        {
            std::lock_guard<std::mutex> guard(mutex_func05);
            funcCode05.at(index) ^= 1UL << 0;
        }
        else
        {
            std::cerr << "Wrong channel for binary event!" << std::endl;
        }
    }
    else if (QtRoboEventType::mode == event.eventType())
    {
        std::lock_guard<std::mutex> guard(mutex_modes);
        m_modes.MODE_CMD ^= 1UL << 0;
    }
    else if (QtRoboEventType::sub == event.eventType())
    {
        std::lock_guard<std::mutex> guard(mutex_modes);
        m_modes.SUB_CMD ^= 1UL << 0;
    }
}
