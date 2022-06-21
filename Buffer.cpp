#include "Buffer.h"

Buffer::Buffer() {
    funcCode02 = std::array<uint16_t, 16>{};
    funcCode03 = std::array<uint16_t, 16>{};
    funcCode04 = std::array<uint8_t, 32>{};
    funcCode05 = std::array<uint8_t, 32>{};
}

const std::array<uint16_t, 16>& Buffer::getFunctionCode02() {
    return funcCode02;
}

const std::array<uint16_t, 16>& Buffer::getFunctionCode03() {
    return funcCode03;
}

const std::array<uint8_t, 32>& Buffer::getFunctionCode04() {
    return funcCode04;
}

const std::array<uint8_t, 32>& Buffer::getFunctionCode05() {
    return funcCode05;
}

void Buffer::reactToQtRoboEvent(QtRoboEvent event) {
    if (QtRoboEventType::proportional == event.eventType()) {
        if (event.eventChannel() < propBreak) {
            funcCode02.at(event.eventChannel()) = event.eventValue();
        }
        if (event.eventChannel() > propBreak && event.eventChannel() < propEnd) {
            funcCode03.at(event.eventChannel()) = event.eventValue();
        }
    }
    if (QtRoboEventType::binary == event.eventType()) {
        if (event.eventChannel() > propEnd && event.eventChannel() < binBreak) {
            funcCode04.at(event.eventChannel()) = event.eventValue();
        }
        if (event.eventChannel() > binBreak && event.eventChannel() < binEnd) {
            funcCode05.at(event.eventChannel()) = event.eventValue();
        }
    }
}
