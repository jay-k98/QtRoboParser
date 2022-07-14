#include "SocketConnection.h"
#include <fcntl.h>
#include <errno.h>

SocketConnection::SocketConnection(const std::string& socketPath, bool& terminated)
: m_Terminated{terminated}
{
    SOCK_PATH = socketPath.c_str();
    memset(&sockaddress, 0, sizeof(struct sockaddr_un));
}

SocketConnection::~SocketConnection()
{
    close(m_Socket);
    unlink(SOCK_PATH);
    remove(SOCK_PATH);
}

bool SocketConnection::isConnected() const
{
    return m_Connected;
}

SocketConnectionErr SocketConnection::connect()
{
    // create unix domain stream socket
    m_Socket = socket(AF_UNIX, SOCK_STREAM, 0);
    int socketFlags = fcntl(m_Socket, F_GETFL, 0);
    fcntl(m_Socket, F_SETFL, socketFlags | O_NONBLOCK);
    if (m_Socket == -1)
    {
        std::cerr << "SOCKET ERROR: " << errno << std::endl;
        return SocketConnectionErr::FATAL;
    }
    
    // setup unix sockaddr struct 
    sockaddress.sun_family = AF_UNIX;   
    strncpy(sockaddress.sun_path, SOCK_PATH, sizeof(sockaddress.sun_path) - 1); 
    len = sizeof(sockaddress);
    
    // unlink the file so bind will succeed
    unlink(SOCK_PATH);
    rc = bind(m_Socket, (struct sockaddr *) &sockaddress, len);
    if (rc == -1)
    {
        std::cerr << "BIND ERROR: " << errno << std::endl;
        close(m_Socket);
        unlink(SOCK_PATH);
        return SocketConnectionErr::FATAL;
    }

    std::cout << "socket created..." << std::endl;

    if (listen(m_Socket, backlog) == -1)
    {
        std::cerr << "LISTEN ERROR: " << errno << std::endl;
        close(m_Socket);
        unlink(SOCK_PATH);
        return SocketConnectionErr::RETRY;
    }

    std::cout << "awaiting connection of client..." << std::endl;

    while (!m_Terminated)
    {
        m_Connect_Socket = accept4(m_Socket, NULL, NULL, O_NONBLOCK);
        if (m_Connect_Socket != -1)
        {
            m_Connected = true;
            return SocketConnectionErr::NONE;
        }
    }
    return SocketConnectionErr::TERMINATED;
}
