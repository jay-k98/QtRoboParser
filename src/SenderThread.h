#pragma once

#include "Buffer.h"
#include "SocketConnection.h"
#include "Sender.h"

class SenderThread
{
private:
    SocketConnection& mSocketConnection;
    Buffer& mBuffer;
    bool& m_NotTerminated;

public:
    SenderThread(SocketConnection& socketConnection, Buffer& buffer, bool& notTerminated);
    ~SenderThread() = default;

    SenderThread operator()();
};
