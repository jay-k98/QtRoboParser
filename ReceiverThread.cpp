#include "ReceiverThread.h"

ReceiverThread::ReceiverThread(SocketConnection &socketConnection, Parser &parser, Buffer &buffer, bool& notTerminated)
: m_SocketConnection{socketConnection}, m_Parser{parser}, m_Buffer{buffer}, m_NotTerminated{notTerminated}
{
}

ReceiverThread ReceiverThread::operator()()
{
    while (m_SocketConnection.isConnected() && m_NotTerminated)
    {
        std::array<char, 256> line{};
        m_SocketConnection.readToBuffer(line);        

        QtRoboEvent event = m_Parser.parseToQtRoboEvent(line);

        m_Buffer.reactToQtRoboEvent(event);
    }
    return *this;
}
