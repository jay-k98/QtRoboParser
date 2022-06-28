#include "Buffer.h"
#include "SocketConnection.h"

class SenderThread
{
private:

public:
    SenderThread();
    ~SenderThread();

    void threadLoop(SocketConnection& socketConnection, Buffer& buffer);
};
