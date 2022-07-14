#pragma once

#include <iostream>

enum class QtRoboEventType { error, binary, proportional, mode, sub };

class QtRoboEvent
{
private:
    uint8_t m_EventChannel;
    uint8_t m_EventValue;
    QtRoboEventType m_EventType;

public:
    QtRoboEvent() = default;
    QtRoboEvent(uint8_t channel, uint8_t value, QtRoboEventType eventType);
    ~QtRoboEvent() = default;

    uint8_t eventChannel() const {
        return m_EventChannel;
    }

    uint8_t eventValue() const {
        return m_EventValue;
    }

    QtRoboEventType eventType() const {
        return m_EventType;
    }
};