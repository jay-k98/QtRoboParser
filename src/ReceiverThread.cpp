#include "ReceiverThread.h"

ReceiverThread::ReceiverThread(SocketConnection &socketConnection, Parser &parser, Buffer &buffer, bool& terminated)
: m_SocketConnection{socketConnection}, m_Parser{parser}, m_Buffer{buffer}, m_Terminated{terminated}
{
}

ReceiverThread ReceiverThread::operator()()
{
    while (m_SocketConnection.isConnected() && !m_Terminated)
    {
        std::array<char, 256> line{};
        SocketReadErr readReturn = m_SocketConnection.readToBuffer(line);

        if (SocketReadErr::DATA_READ == readReturn)
        {
            QtRoboEvent event = m_Parser.parseToQtRoboEvent(line);
            m_Buffer.reactToQtRoboEvent(event);
        }
    }
    return *this;
}
