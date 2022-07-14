#include "SenderThread.h"
#include <chrono>
#include <thread>

SenderThread::SenderThread(SocketConnection& socketConnection, Buffer& buffer, bool& terminated, bool& debug)
: mSocketConnection{socketConnection}, mBuffer{buffer}, m_Terminated{terminated}, m_debug{debug}
{
}

SenderThread SenderThread::operator()()
{
    while (mSocketConnection.isConnected() && !m_Terminated)
    {
        Sender::send(Sender::parseToSumd(mBuffer.functionCode02(), mBuffer.modes(), 0x02), m_debug);
        std::this_thread::sleep_for(std::chrono::milliseconds(10));

        Sender::send(Sender::parseToSumd(mBuffer.functionCode03(), mBuffer.modes(), 0x03), m_debug);
        std::this_thread::sleep_for(std::chrono::milliseconds(10));

        Sender::send(Sender::parseToSumd(mBuffer.functionCode04(), mBuffer.modes(), 0x04), m_debug);
        std::this_thread::sleep_for(std::chrono::milliseconds(10));

        Sender::send(Sender::parseToSumd(mBuffer.functionCode05(), mBuffer.modes(), 0x05), m_debug);
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    return *this;
}