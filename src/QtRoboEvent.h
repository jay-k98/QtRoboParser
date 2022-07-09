#pragma once

#include <iostream>

enum class QtRoboEventType { error, binary, proportional, mode, sub };

class QtRoboEvent
{
private:
    uint8_t mEventChannel;
    uint8_t mEventValue;
    QtRoboEventType mEventType;

public:
    QtRoboEvent() = default;
    QtRoboEvent(uint8_t channel, uint8_t value, QtRoboEventType eventType);
    ~QtRoboEvent() = default;

    uint8_t eventChannel() const {
        return mEventChannel;
    }

    uint8_t eventValue() const {
        return mEventValue;
    }

    QtRoboEventType eventType() const {
        return mEventType;
    }
};