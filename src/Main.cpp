#include "lyra/lyra.hpp"
#include "Parser.h"
#include "QtRoboEvent.h"
#include "SocketConnection.h"
#include "Buffer.h"
#include <thread>
#include <csignal>
#include "ReceiverThread.h"
#include "SenderThread.h"

bool terminated = false;
bool debug = false;

void signalHandler(int signum)
{
    terminated = true;
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
                ["-u"]["--uds"]("Where should the unix domain socket be created?")
        | lyra::opt(debug, "true -> debug enabled, false -> debug disabled")
                ["-d"]["--debug"]("Should debug output be enabled?")};

    auto result{cli.parse({ argc, argv })};
    bool emptyValues{parserConfig.incomplete() || udsname.empty()};
    show_help = show_help || !result || emptyValues;

    if (show_help)
    {
	std::cout << cli << std::endl;
	exit(1);
    }

    std::cout << parserConfig << udsname << std::endl;

    while (!terminated)
    {
        SocketConnection socket{udsname, terminated};
        SocketConnectionErr errorCode{socket.connect()};
        while (SocketConnectionErr::NONE != errorCode)
        {
            if (SocketConnectionErr::FATAL == errorCode)
            {
                exit(1);
            }
            else if (SocketConnectionErr::RETRY == errorCode)
            {
                errorCode = socket.connect();
            }
        }

        if (!terminated)
        {
            Buffer buffer{};
            Parser parser{parserConfig};

            ReceiverThread receiver{socket, parser, buffer, terminated};
            SenderThread sender{socket, buffer, terminated, debug};

            std::thread receiverThread{receiver};
            std::thread senderThread{sender};

            receiverThread.join();
            senderThread.join();
        }
    }
    return 0;
}
