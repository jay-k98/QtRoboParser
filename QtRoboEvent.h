#pragma once
#include <iostream>

class QtRoboEvent
{
private:
    u_int8_t mEventChannel;
    u_int8_t mEventValue;

public:
    QtRoboEvent() = default;
    QtRoboEvent(uint8_t channel, uint8_t value);
    ~QtRoboEvent() = default;

    uint8_t eventChannel() const {
        return mEventChannel;
    }

    uint8_t eventValue() const {
        return mEventValue;
    }
};
