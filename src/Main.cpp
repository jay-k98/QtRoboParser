#include "Parser.h"
#include "QtRoboEvent.h"
#include "SocketConnection.h"
#include "Buffer.h"
#include <thread>
#include <csignal>
#include "ReceiverThread.h"
#include "SenderThread.h"

#define MIN_CHANNEL 0
#define MAX_CHANNEL 95

bool notTerminated = true;

void signalHandler(int signum)
{
    std::cout << "Signal: " << signum << std::endl;
    notTerminated = false;
    exit(0);
}

int main(int argc, char const *argv[])
{
    signal(SIGINT, signalHandler);
    if (argc != 6)
    {
        std::cerr << "Please enter in the following order: [Prefix Prop] [Prefix Bin] [Prefix MODE] [Prefix SUB] [Name of the Unix Domain Socket]!" << std::endl;
        exit(1);
    }
    // $ABC12:48
    // argv[0] contains the directory the application was started from
    // -> That is why we start from index 1
    ParserConfig parserConfig{argv[1], argv[2], argv[3], argv[4]};
    std::string udsname{argv[5]};

    std::cout << parserConfig
         << argv[2] << "\n";

    while (notTerminated)
    {
        SocketConnection socket{udsname, notTerminated};
        socket.connect();

        Buffer buffer{};

        Parser parser{parserConfig};

        std::cout << socket.isConnected() << std::endl;

        ReceiverThread receiver = ReceiverThread{socket, parser, buffer, notTerminated};
        SenderThread sender = SenderThread{socket, buffer, notTerminated};

        std::thread receiverThread{receiver};
        std::thread senderThread{sender};

        receiverThread.join();
        senderThread.join();
    }

    return 0;
}