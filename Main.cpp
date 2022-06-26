#include "Parser.h"
#include "QtRoboEvent.h"
#include "SocketConnection.h"
#include "Util.h"
#include "Buffer.h"

#define MIN_CHANNEL 0
#define MAX_CHANNEL 95

using namespace std;

int main(int argc, char const *argv[])
{
    if (argc != 3) {
        cerr << "Please enter in the following order: [Prefix] [Name of the Unix Domain Socket]!" << endl;
        exit(1);
    }

    // argv[0] contains the directory the application was started from
    // -> That is why we start from index 1
    string prefix {argv[1]};
    string udsname {argv[2]};

    cout << "Launched with the following arguments:\n"
        << prefix << "\n"
        << argv[2] << "\n";

    SocketConnection sc = SocketConnection{udsname};
    sc.connect();

    char buffer[256];

    
    while (true)
    {
        write(STDOUT_FILENO, buffer, sc.readToBuffer(buffer));
        Parser p {Parser{argv[2]}};

        QtRoboEvent event = p.parseToQtRoboEvent(buffer);

        cout << to_string(event.eventChannel()) << endl;
        cout << to_string(event.eventValue()) << endl;

        auto sumd {p.parseToSumd(event)};

        Buffer buff{};

        //cout << Util::sumdBytesToString(sumd) << endl;
    }

    return 0;
}
