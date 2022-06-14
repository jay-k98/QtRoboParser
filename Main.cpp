#include "Parser.h"
#include "QtRoboEvent.h"
#include "SocketConnection.h"
#include "Util.h"

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

    cout << "Launched with following arguments:\n"
        << prefix << "\n"
        << channel << "\n"
        << argv[3] << "\n";

    SocketConnection sc = SocketConnection{argv[3]};
    sc.connect();

    char buffer[256];

    
    while (true)
    {
        write(STDOUT_FILENO, buffer, sc.readToBuffer(buffer));
        Parser p {Parser{argv[2]}};

        QtRoboEvent event = p.parseToQtRoboEvent(buffer);

        cout << to_string(event.eventChannel()) << endl;
        cout << to_string(event.eventValue()) << endl;

        uint8_t* sumd {p.parseToSumd(event)};

        cout << Util::sumdBytesToString(sumd) << endl;
    }

    return 0;
}
