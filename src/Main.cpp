#include "lyra/lyra.hpp"
#include "Parser.h"
#include "QtRoboEvent.h"
#include "SocketConnection.h"
#include "Buffer.h"
#include <thread>
#include <csignal>
#include "ReceiverThread.h"
#include "SenderThread.h"

bool notTerminated = true;

void signalHandler(int signum)
{
    notTerminated = false;
}

int main(int argc, char const *argv[])
{
    signal(SIGINT, signalHandler);

    ParserConfig parserConfig{};
    std::string udsname{};
    bool show_help{false};

    auto cli{lyra::help(show_help)
        | lyra::opt(parserConfig.bin_prefix, "binary prefix")
                ["-b"]["--bin"]("What prefix is used for binary events?")
        | lyra::opt(parserConfig.prop_prefix, "proportional prefix")
                ["-p"]["--prop"]("What prefix is used for proportional events?")
        | lyra::opt(parserConfig.mode_prefix, "mode prefix")
                ["-m"]["--mode"]("What prefix is used for the mode event?")
        | lyra::opt(parserConfig.sub_prefix, "sub prefix")
                ["-s"]["--sub"]("What prefix is used for the sub event?")
        | lyra::opt(udsname, "unix domain socket name")
                ["-u"]["--uds"]("Where should the unix domain socket be created?")};

    auto result{cli.parse({ argc, argv })};
    bool emptyValues{parserConfig.incomplete() || udsname.empty()};
    show_help = show_help || !result || emptyValues;

    if (show_help)
    {
	    std::cout << cli << std::endl;
	    exit(1);
    }

    std::cout << parserConfig << udsname << std::endl;

    while (notTerminated)
    {
        SocketConnection socket{udsname};
        socket.start();

        Buffer buffer{};
        Parser parser{parserConfig};

        ReceiverThread receiver{ReceiverThread{socket, parser, buffer, notTerminated}};
        SenderThread sender{SenderThread{socket, buffer, notTerminated}};

        std::thread receiverThread{receiver};
        std::thread senderThread{sender};

        receiverThread.join();
        senderThread.join();
    }

    return 0;
}
