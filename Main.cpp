#include "Parser.h"
#include "QtRoboEvent.h"
#include "SocketConnection.h"
#include "Util.h"
#include "Buffer.h"
#include <thread>
#include "ReceiverThread.h"
#include "SenderThread.h"

#define MIN_CHANNEL 0
#define MAX_CHANNEL 95

using namespace std;

int main(int argc, char const *argv[])
{
    if (argc != 3) {
        cerr << "Please enter in the following order: [Prefix] [Name of the Unix Domain Socket]!" << endl;
        exit(1);
    }
    // $ABC12:48
    // argv[0] contains the directory the application was started from
    // -> That is why we start from index 1
    string prefix {argv[1]};
    string udsname {argv[2]};

    cout << "Launched with the following arguments:\n"
        << prefix << "\n"
        << argv[2] << "\n";

    while (true)
    {
        SocketConnection socket {udsname};
        socket.connect();

        Buffer buffer{};

        std::thread receiverThread {ReceiverThread::threadLoop, std::ref(socket), prefix, std::ref(buffer)};

        std::thread senderThread {SenderThread::threadLoop, std::ref(socket), std::ref(buffer)};

        receiverThread.join();
        senderThread.join();
    }

    return 0;
}
