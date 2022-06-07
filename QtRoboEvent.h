#pragma once
#include <iostream>

class QtRoboEvent
{
private:
    int eventChannel;
    int eventValue;
    
public:
    QtRoboEvent() = default;
    QtRoboEvent(int channel, int value);
    ~QtRoboEvent() = default;
};
