#pragma once

#include "Buffer.h"
#include "SocketConnection.h"
#include "Sender.h"

class SenderThread
{
private:
    SocketConnection& mSocketConnection;
    Buffer& mBuffer;
    bool& m_isTerminated;

public:
    SenderThread(SocketConnection& socketConnection, Buffer& buffer, bool& isTerminated);
    ~SenderThread() = default;

    SenderThread operator()();
};
