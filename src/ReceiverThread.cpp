#include "ReceiverThread.h"
#include <thread>

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

        // Socket has O_NONBLOCKING set -> is non-blocking -> only react if data was read
        if (SocketReadErr::DATA_READ == readReturn)
        {
            QtRoboEvent event = m_Parser.parseToQtRoboEvent(line);
            m_Buffer.reactToQtRoboEvent(event);
        }
        else
        {
            // Sleep for 1ms to avoid calling readToBuffer() too often
            // Increases performance of SenderThread by calling IO function less frequently
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
    }
    return *this;
}
