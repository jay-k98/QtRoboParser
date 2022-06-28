#include "ReceiverThread.h"
#include "Parser.h"
#include "QtRoboEvent.h"
#include "SocketConnection.h"
#include "Buffer.h"

ReceiverThread::ReceiverThread()
{

}

void ReceiverThread::threadLoop(SocketConnection& socketConnection, const std::string prefix, Buffer& buffer)
{
    Parser p {prefix};
    while (socketConnection.isConnected())
    {
        char line[256];
        write(STDOUT_FILENO, line, socketConnection.readToBuffer(line));

        QtRoboEvent event = p.parseToQtRoboEvent(line);

        buffer.reactToQtRoboEvent(event);
    }
}
