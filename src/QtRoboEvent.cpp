#include "QtRoboEvent.h"

QtRoboEvent::QtRoboEvent(uint8_t channel, uint8_t value, QtRoboEventType eventType)
: mEventChannel{channel}, mEventValue{value}, mEventType{eventType}
{
}