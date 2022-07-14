#pragma once

#include "Buffer.h"
#include "SocketConnection.h"
#include "Sender.h"

class SenderThread
{
private:
    SocketConnection& mSocketConnection;
    Buffer& mBuffer;
    bool& m_Terminated;
    bool& m_debug;

public:
    SenderThread(SocketConnection& socketConnection, Buffer& buffer, bool& terminated, bool& debug);
    ~SenderThread() = default;

    SenderThread operator()();
};
