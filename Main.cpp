#include "Parser.h"
#include "QtRoboEvent.h"

#define MIN_CHANNEL 0
#define MAX_CHANNEL 31

using namespace std;

int main(int argc, char const *argv[])
{
    if (argc != 4) {
        cout << "Please enter Channel and prefix!" << endl;
        exit(1);
    }
    int channel {stoi(argv[1])};
    if (channel > MAX_CHANNEL && channel < MIN_CHANNEL) {
        cout << "The value of the channel must be between 0 and 31 (inclusive)!" << endl;
        cout << "Please change accordingly and try again!" << endl;
        exit(1);
    }
    string prefix {argv[2]};
    string path {argv[3]};

    cout << "Launched with following arguments:\n"
        << prefix << "\n"
        << channel << "\n"
        << path << "\n";

    // TODO: Create socket and start listening
    
    return 0;
}
