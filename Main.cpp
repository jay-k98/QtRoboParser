#include "Parser.h"
#include "QtRoboEvent.h"
#include "SocketConnection.h"
#include "Util.h"
#include "Buffer.h"
#include <thread>
#include <csignal>
#include "ReceiverThread.h"
#include "SenderThread.h"

#define MIN_CHANNEL 0
#define MAX_CHANNEL 95

using namespace std;

bool isTerminated = true;

void signalHandler(int signum)
{
    cout << "Signal: " << signum << endl;
    isTerminated = false;
}

int main(int argc, char const *argv[])
{
    signal(SIGINT, signalHandler);
    if (argc != 6) {
        cerr << "Please enter in the following order: [Prefix Prop] [Prefix Bin] [Prefix MODE] [Prefix SUB] [Name of the Unix Domain Socket]!" << endl;
        exit(1);
    }
    // $ABC12:48
    // argv[0] contains the directory the application was started from
    // -> That is why we start from index 1
    ParserConfig parserConfig {argv[1], argv[2], argv[3], argv[4]};
    string udsname {argv[5]};

    cout << "Launched with the following arguments:\n"
        << parserConfig.prop_prefix << "\n"
        << parserConfig.bin_prefix << "\n"
        << parserConfig.mode_prefix << "\n"
        << parserConfig.sub_prefix << "\n"
        << argv[2] << "\n";

    while (isTerminated)
    {
        SocketConnection socket {udsname, isTerminated};
        socket.connect();

        Buffer buffer{};

        Parser parser{parserConfig};

        ReceiverThread* receiver = new ReceiverThread{socket, parser, buffer};
        SenderThread* sender = new SenderThread{socket, buffer};

        std::thread receiverThread {&ReceiverThread::threadLoop, receiver};
        std::thread senderThread {&SenderThread::threadLoop, sender};

        receiverThread.join();
        senderThread.join();

        delete receiver;
        delete sender;
    }

    return 0;
}
