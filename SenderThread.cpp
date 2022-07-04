#include "SenderThread.h"
#include <chrono>
#include <thread>

SenderThread::SenderThread(SocketConnection& socketConnection, Buffer& buffer, bool& isTerminated)
: mSocketConnection{socketConnection}, mBuffer{buffer}, m_isTerminated{isTerminated}
{
}

SenderThread SenderThread::operator()()
{
    while (mSocketConnection.isConnected() && !m_isTerminated)
    {
        Sender::send(Sender::parseToSumd(mBuffer.functionCode02(), mBuffer.modes(), 0x02));
        std::this_thread::sleep_for(std::chrono::milliseconds(10));

        Sender::send(Sender::parseToSumd(mBuffer.functionCode03(), mBuffer.modes(), 0x03));
        std::this_thread::sleep_for(std::chrono::milliseconds(10));

        Sender::send(Sender::parseToSumd(mBuffer.functionCode04(), mBuffer.modes(), 0x04));
        std::this_thread::sleep_for(std::chrono::milliseconds(10));

        Sender::send(Sender::parseToSumd(mBuffer.functionCode05(), mBuffer.modes(), 0x05));
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    return *this;
}