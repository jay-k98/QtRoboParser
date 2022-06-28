#pragma once

#include <string>

class ReceiverThread
{
private:
    
public:
    ReceiverThread();
    ~ReceiverThread() = default;

    void threadLoop(SocketConnection& socketConnection, const std::string prefix, Buffer& buffer);
};
