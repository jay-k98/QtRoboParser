#include "SenderThread.h"
#include "Sender.h"
#include <chrono>
#include <thread>

SenderThread::SenderThread()
{

}

void SenderThread::threadLoop(SocketConnection& socketConnection, Buffer& buffer)
{
    Sender sender{};
    while (socketConnection.isConnected())
    {
        sender.send(sender.parseToSumd(buffer.getFunctionCode02(), 0x02));
        std::this_thread::sleep_for(std::chrono::milliseconds(10));

        sender.send(sender.parseToSumd(buffer.getFunctionCode03(), 0x03));
        std::this_thread::sleep_for(std::chrono::milliseconds(10));

        sender.send(sender.parseToSumd(buffer.getFunctionCode04(), 0x04));
        std::this_thread::sleep_for(std::chrono::milliseconds(10));

        sender.send(sender.parseToSumd(buffer.getFunctionCode05(), 0x05));
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }

}