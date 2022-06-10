#include <Parser.h>
#include <QtRoboEvent.h>

#define MIN_CHANNEL 0
#define MAX_CHANNEL 31

using namespace std;

int main(int argc, char const *argv[])
{
    if (argc != 2) {
        cout << "Bitte Channel und Präfix angeben!" << endl;
        
    }
    int channel {stoi(argv[0])};
    if (channel > MAX_CHANNEL && channel < MIN_CHANNEL) {
        cout << "Der Wert für den Channel muss zwischen 0 und 31 liegen!" << endl;
    }
    string prefix {argv[1]};

    // TODO: Create socket and start listening
    
    return 0;
}
