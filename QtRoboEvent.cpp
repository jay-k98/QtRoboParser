#include <QtRoboEvent.h>

QtRoboEvent::QtRoboEvent(uint8_t channel, uint8_t value) : 
    mEventChannel{channel}, mEventValue{value}
{

}