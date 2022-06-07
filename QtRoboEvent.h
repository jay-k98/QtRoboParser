#include <iostream>

class QtRoboEvent
{
private:
    int eventChannel;
    int eventValue;
    
public:
    QtRoboEvent(int channel, int value);
    ~QtRoboEvent() = default;
};
