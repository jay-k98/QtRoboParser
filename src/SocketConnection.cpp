#include "SocketConnection.h"
#include <fcntl.h>
#include <errno.h>

SocketConnection::SocketConnection(const std::string& socketPath, bool& terminated)
: m_terminated{terminated}
{
    SOCK_PATH = socketPath.c_str();
    memset(&sockaddress, 0, sizeof(struct sockaddr_un));
}

SocketConnection::~SocketConnection()
{
    close(m_socket);
    unlink(SOCK_PATH);
    remove(SOCK_PATH);
}

bool SocketConnection::isConnected() const
{
    return m_connected;
}

SocketConnectionErr SocketConnection::connect()
{
    // create unix domain stream socket
    m_socket = socket(AF_UNIX, SOCK_STREAM, 0);
    int socketFlags = fcntl(m_socket, F_GETFL, 0);
    fcntl(m_socket, F_SETFL, socketFlags | O_NONBLOCK);
    if (m_socket == -1)
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
    rc = bind(m_socket, (struct sockaddr *) &sockaddress, len);
    if (rc == -1)
    {
        std::cerr << "BIND ERROR: " << errno << std::endl;
        close(m_socket);
        unlink(SOCK_PATH);
        return SocketConnectionErr::FATAL;
    }

    std::cout << "socket created..." << std::endl;

    if (listen(m_socket, backlog) == -1)
    {
        std::cerr << "LISTEN ERROR: " << errno << std::endl;
        close(m_socket);
        unlink(SOCK_PATH);
        return SocketConnectionErr::RETRY;
    }

    std::cout << "awaiting connection of client..." << std::endl;

    while (!m_terminated)
    {
        m_connect_socket = accept4(m_socket, NULL, NULL, O_NONBLOCK);
        if (m_connect_socket != -1)
        {
            m_connected = true;
            return SocketConnectionErr::NONE;
        }
    }
}
