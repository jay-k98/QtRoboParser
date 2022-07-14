#include "QtRoboEvent.h"

QtRoboEvent::QtRoboEvent(uint8_t channel, uint8_t value, QtRoboEventType eventType)
: m_EventChannel{channel}, m_EventValue{value}, m_EventType{eventType}
{
}