#include "SocketConnection.h"

SocketConnection::SocketConnection(const char* socketPath)
{
    SOCK_PATH = socketPath;

    // clear structs and buffer
    memset(&sockaddress, 0, sizeof(struct sockaddr_un));
}

int SocketConnection::connect()
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

int SocketConnection::readToBuffer(char buf[])
{
        while ((bytes_rec = read(m_connect_socket, buf, 256)) > 0) {
            if (write(STDOUT_FILENO, buf, bytes_rec) != bytes_rec) {
            }
        }

        if (bytes_rec == -1){
            printf("Read error");
            close(m_connect_socket);
            close(m_socket);
            exit(1);
        }
}
