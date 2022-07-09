
#include <iostream>
#include <stdio.h>


#define SOCK_PATH  "/tmp/abc"
#define DATA "Hello from server"



struct qtRoboEvent {
    string eventName;
    string eventValue;
};

int main() {
    int buf_size = 256;
    char buf[buf_size];
    buf[0] = '$';
    buf[1] = 'S';
    buf[2] = '1';
    buf[3] = ':';
    buf[4] = '4';
    buf[5] = '0';
    buf[6] = '\0';
    cout << buf << endl;
    char *c = buf;
    qtRoboEvent qtE{}; 
    bool valueBegin = false;
    if(buf[0] == '$') {
        c++;
        while (*c != '\0') {
            if (*c == ':') {
                valueBegin = true;
                c++;
            }
            if(valueBegin)
                qtE.eventValue += *c;
            else
                qtE.eventName += *c;
            c++;
        }
    }
    cout << qtE.eventName << endl;
    cout << qtE.eventValue << endl;
    return 0;
}