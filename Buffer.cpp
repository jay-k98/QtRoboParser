#include "Buffer.h"

Buffer::Buffer() {
}

const std::array<uint8_t, 32>& Buffer::getFunctionCode02() {
    return funcCode02;
}

const std::array<uint8_t, 32>& Buffer::getFunctionCode03() {
    return funcCode03;
}

const std::array<uint8_t, 32>& Buffer::getFunctionCode04() {
    return funcCode04;
}

const std::array<uint8_t, 32>& Buffer::getFunctionCode05() {
    return funcCode05;
}

void Buffer::reactToQtRoboEvent(QtRoboEvent event) {
    constexpr int propBreak {16};
    constexpr int propEnd {32};
    constexpr int binBreak {64};
    constexpr int binEnd {96};

    if (QtRoboEventType::proportional == event.eventType()) {
        size_t index{event.eventChannel() * 2};
        if (event.eventChannel() < propBreak) {
            funcCode02.at(index) = 0x00;
            funcCode02.at(index + 1) = event.eventValue();
        }
        if (event.eventChannel() > propBreak && event.eventChannel() < propEnd) {
            funcCode03.at(index) = 0x00;
            funcCode03.at(index + 1) = event.eventValue();
        }
    }
    if (QtRoboEventType::binary == event.eventType()) {
        if (event.eventChannel() > propEnd && event.eventChannel() < binBreak) {
            funcCode04.at(event.eventChannel()) ^= 1UL << 0;
        }
        if (event.eventChannel() > binBreak && event.eventChannel() < binEnd) {
            funcCode05.at(event.eventChannel()) ^= 1UL << 0;
        }
    }
}
