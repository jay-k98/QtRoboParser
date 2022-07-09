#include "SenderThread.h"
#include <chrono>
#include <thread>

SenderThread::SenderThread(SocketConnection& socketConnection, Buffer& buffer, bool& notTerminated)
: mSocketConnection{socketConnection}, mBuffer{buffer}, m_NotTerminated{notTerminated}
{
}

SenderThread SenderThread::operator()()
{
    while (mSocketConnection.isConnected() && m_NotTerminated)
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