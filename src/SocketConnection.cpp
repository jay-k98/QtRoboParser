#include "SocketConnection.h"

SocketConnection::SocketConnection(const std::string& socketPath)
{
    SOCK_PATH = socketPath.c_str();
    memset(&sockaddress, 0, sizeof(struct sockaddr_un));
}

SocketConnection::~SocketConnection()
{
    remove(SOCK_PATH);
    close(m_socket);
    unlink(SOCK_PATH);
}

bool SocketConnection::isConnected() const
{
    return m_connected;
}

void SocketConnection::start()
{
    SocketConnectionErr errorCode{connect()};
    while (SocketConnectionErr::NONE != errorCode)
    {
        if (SocketConnectionErr::FATAL == errorCode)
        {
            exit(1);
        }
        else if (SocketConnectionErr::RETRY == errorCode)
        {
            errorCode = connect();
        }
    }
}

SocketConnectionErr SocketConnection::connect()
{
    // create unix domain stream socket
    m_socket = socket(AF_UNIX, SOCK_STREAM, 0);
    if (m_socket == -1)
    {
        std::cerr << "SOCKET ERROR: %d" << std::endl;
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
        std::cerr << "BIND ERROR: %d" << std::endl;
        close(m_socket);
        unlink(SOCK_PATH);
        return SocketConnectionErr::FATAL;
    }

    if (listen(m_socket, backlog) == -1)
    {
        std::cerr << "Error while listening" << std::endl;
        close(m_socket);
        unlink(SOCK_PATH);
        return SocketConnectionErr::RETRY;
    }

    printf("socket created...\n");

    printf("awaiting connection of client...\n");

    m_connect_socket = accept(m_socket, NULL, NULL);
    if (m_connect_socket == -1)
    {
        std::cerr << "Error while connecting" << std::endl;
        close(m_connect_socket);
        unlink(SOCK_PATH);
        return SocketConnectionErr::RETRY;
    }
    m_connected = true;
    return SocketConnectionErr::NONE;
}
