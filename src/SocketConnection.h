#pragma once

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <iostream>
#include <array>

enum class SocketConnectionErr
{
    NONE = 0,
    FATAL = 10, // Program should be terminated
    RETRY = 20 // Problem caused by client -> retry connect()
};

class SocketConnection
{
private:
    bool m_connected{false};
    const char* SOCK_PATH;
    int m_socket, m_connect_socket, rc;
    socklen_t len;
    int bytes_rec {0};
    int backlog {5};
    struct sockaddr_un sockaddress;

    SocketConnectionErr connect();

public:
    SocketConnection(const std::string& socketPath);
    ~SocketConnection();

    bool isConnected() const;
    void start();

    template<std::size_t SIZE>
    int readToBuffer(std::array<char, SIZE>& buff)
    {
        std::cout << "SIZE: " << SIZE << std::endl;
        bytes_rec = read(m_connect_socket, &buff[0], SIZE);
        if (bytes_rec == -1)
        {
            printf("Read error");
            close(m_connect_socket);
            close(m_socket);
            return -1;
        }

        if (bytes_rec == 0)
        {
            printf("Connection closed by client");
            close(m_connect_socket);
            close(m_socket);
            unlink(SOCK_PATH);
            m_connected = false;
        }

        return bytes_rec;
    }
};
