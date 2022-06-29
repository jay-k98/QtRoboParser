#pragma once

#include <string>

class ReceiverThread
{
private:
    SocketConnection& m_SocketConnection;
    Parser& m_Parser;
    Buffer& m_Buffer;
    
public:
    ReceiverThread(SocketConnection& socketConnection, Parser& parser, Buffer& buffer);
    ~ReceiverThread() = default;

    void threadLoop();
};
