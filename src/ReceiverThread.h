#pragma once

#include "Parser.h"
#include "QtRoboEvent.h"
#include "SocketConnection.h"
#include "Buffer.h"
#include <string>

class ReceiverThread
{
private:
    SocketConnection& m_SocketConnection;
    Parser& m_Parser;
    Buffer& m_Buffer;
    bool& m_NotTerminated;
    
public:
    ReceiverThread(SocketConnection& socketConnection, Parser& parser, Buffer& buffer, bool& notTerminated);
    ~ReceiverThread() = default;

    ReceiverThread operator()();
};
