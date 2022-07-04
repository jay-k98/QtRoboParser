#include "ReceiverThread.h"

ReceiverThread::ReceiverThread(SocketConnection &socketConnection, Parser &parser, Buffer &buffer, bool& isTerminated)
: m_SocketConnection{socketConnection}, m_Parser{parser}, m_Buffer{buffer}, m_isTerminated{isTerminated}
{
}

ReceiverThread ReceiverThread::operator()()
{
    while (m_SocketConnection.isConnected() && !m_isTerminated)
    {
        std::array<char, 256> line{};
        write(STDOUT_FILENO, &line[0], m_SocketConnection.readToBuffer(line));

        QtRoboEvent event = m_Parser.parseToQtRoboEvent(line);

        m_Buffer.reactToQtRoboEvent(event);
    }
    return *this;
}
