#include "Buffer.h"
#include "SocketConnection.h"

class SenderThread
{
private:
    SocketConnection mSocketConnection;
    Buffer mBuffer;

public:
    SenderThread(SocketConnection& socketConnection, Buffer& buffer);
    ~SenderThread();

    void threadLoop();
};
