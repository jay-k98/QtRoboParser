#include "ReceiverThread.h"
#include "Parser.h"
#include "QtRoboEvent.h"
#include "SocketConnection.h"
#include "Buffer.h"

ReceiverThread::ReceiverThread(SocketConnection& socketConnection, Parser& parser, Buffer& buffer)
: m_SocketConnection{socketConnection}, m_Parser{parser}, m_Buffer{buffer}
{
}

void ReceiverThread::threadLoop()
{
    while (m_SocketConnection.isConnected())
    {
        char line[256];
        write(STDOUT_FILENO, line, m_SocketConnection.readToBuffer(line));

        QtRoboEvent event = m_Parser.parseToQtRoboEvent(line);

        m_Buffer.reactToQtRoboEvent(event);
    }
}
