#include "SocketConnection.h"

SocketConnection::SocketConnection(const std::string& socketPath, bool& isTerminated)
{
    SOCK_PATH = socketPath.c_str();

    // clear structs and buffer
    memset(&sockaddress, 0, sizeof(struct sockaddr_un));
}

SocketConnection::~SocketConnection()
{
    unlink(SOCK_PATH);
}

bool SocketConnection::isConnected() const
{
    return m_connected;
}

std::error_code SocketConnection::connect()
{
    // create unix domain stream socket
    m_socket = socket(AF_UNIX, SOCK_STREAM, 0);
    if (m_socket == -1){
        printf("SOCKET ERROR: %d\n");
        exit(1);
    }
    
    // setup unix sockaddr struct 
    sockaddress.sun_family = AF_UNIX;   
    strncpy(sockaddress.sun_path, SOCK_PATH, sizeof(sockaddress.sun_path) - 1); 
    len = sizeof(sockaddress);
    
    // unlink the file so bind will succeed
    unlink(SOCK_PATH);
    rc = bind(m_socket, (struct sockaddr *) &sockaddress, len);
    if (rc == -1){
        printf("BIND ERROR: %d\n");
        close(m_socket);
        exit(1);
    }

    if (listen(m_socket, BACKLOG) == -1) {
        printf("Error while listening");
        close(m_socket);
        exit(1);
    }

    printf("socket created...\n");

    while (false == m_connected) {
        printf("awaiting connection of client...\n");

        m_connect_socket = accept(m_socket, NULL, NULL);
        if (m_connect_socket == -1) {
            printf("Error while connecting");
            close(m_connect_socket);
            exit(1);
        }
        m_connected = true;
    }
}
