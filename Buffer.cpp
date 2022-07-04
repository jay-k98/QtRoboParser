#include "Buffer.h"

const std::array<uint8_t, 32> Buffer::functionCode02() {
    std::lock_guard<std::mutex> guard(mutex_func02);
    return funcCode02;
}

const std::array<uint8_t, 32> Buffer::functionCode03() {
    std::lock_guard<std::mutex> guard(mutex_func03);
    return funcCode03;
}

const std::array<uint8_t, 32> Buffer::functionCode04() {
    std::lock_guard<std::mutex> guard(mutex_func04);
    return funcCode04;
}

const std::array<uint8_t, 32> Buffer::functionCode05() {
    std::lock_guard<std::mutex> guard(mutex_func05);
    return funcCode05;
}

const Modes Buffer::modes() {
    std::lock_guard<std::mutex> guard(mutex_modes);
    return m_modes;
}

void Buffer::reactToQtRoboEvent(QtRoboEvent event) {
    constexpr int propBreak {16};
    constexpr int propEnd {32};
    constexpr int binBreak {64};
    constexpr int binEnd {96};

    if (QtRoboEventType::proportional == event.eventType()) {
        size_t index{event.eventChannel() * 2};
        if (event.eventChannel() < propBreak) {
            std::lock_guard<std::mutex> guard(mutex_func02);
            funcCode02.at(index) = 0x00;
            funcCode02.at(index + 1) = event.eventValue();
        }
        if (event.eventChannel() > propBreak && event.eventChannel() < propEnd) {
            std::lock_guard<std::mutex> guard(mutex_func03);
            funcCode03.at(index) = 0x00;
            funcCode03.at(index + 1) = event.eventValue();
        }
    }
    if (QtRoboEventType::binary == event.eventType()) {
        if (event.eventChannel() > propEnd && event.eventChannel() < binBreak) {
            std::lock_guard<std::mutex> guard(mutex_func04);
            funcCode04.at(event.eventChannel()) ^= 1UL << 0;
        }
        if (event.eventChannel() > binBreak && event.eventChannel() < binEnd) {
            std::lock_guard<std::mutex> guard(mutex_func05);
            funcCode05.at(event.eventChannel()) ^= 1UL << 0;
        }
    }
    if (QtRoboEventType::mode == event.eventType()) {
        std::lock_guard<std::mutex> guard(mutex_modes);
        m_modes.MODE_CMD ^= 1UL << 0;
    }
    if (QtRoboEventType::sub == event.eventType()) {
        std::lock_guard<std::mutex> guard(mutex_modes);
        m_modes.SUB_CMD ^= 1UL << 0;
    }
}
