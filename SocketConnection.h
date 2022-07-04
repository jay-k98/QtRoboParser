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
#include <system_error>

#define BACKLOG 5

class SocketConnection
{
private:
    bool m_connected = false;
    const char* SOCK_PATH;
    int m_socket, m_connect_socket, rc;
    socklen_t len;
    int bytes_rec {0};
    int backlog {10};
    struct sockaddr_un sockaddress;

public:
    SocketConnection(const std::string& socketPath, bool& isTerminated);
    ~SocketConnection();

    bool isConnected() const;

    std::error_code connect();

    template<std::size_t SIZE>
    int readToBuffer(std::array<char, SIZE> buff)
    {
        bytes_rec = read(m_connect_socket, &buff[0], SIZE);

        if (bytes_rec == -1){
            printf("Read error");
            close(m_connect_socket);
            close(m_socket);
            return -1;
        }

        if (bytes_rec == 0){
            printf("Connection closed by client");
            close(m_connect_socket);
            close(m_socket);
            unlink(SOCK_PATH);
            m_connected = false;
        }

        return bytes_rec;
    }
};
