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
#include <errno.h>

enum class SocketConnectionErr
{
    NONE,
    FATAL,
    RETRY
};

enum class SocketReadErr
{
    DATA_READ,
    NOTHING_TO_READ,
    CONNECTION_CLOSED,
    READ_ERROR
};

class SocketConnection
{
private:
    bool m_connected{false};
    bool& m_terminated;
    const char* SOCK_PATH;
    int m_socket, m_connect_socket, rc;
    socklen_t len;
    int bytes_rec {0};
    int backlog {5};
    struct sockaddr_un sockaddress;

public:
    SocketConnection(const std::string& socketPath, bool& terminated);
    ~SocketConnection();

    bool isConnected() const;
    SocketConnectionErr connect();

    template<std::size_t SIZE>
    SocketReadErr readToBuffer(std::array<char, SIZE>& buff)
    {
        bytes_rec = read(m_connect_socket, &buff[0], SIZE);
        if (-1 == bytes_rec && EAGAIN == errno)
        {
            return SocketReadErr::NOTHING_TO_READ;
        }
        else if (-1 == bytes_rec)
        {
            std::cerr << "Read error" << std::endl;
            close(m_connect_socket);
            close(m_socket);
            return SocketReadErr::READ_ERROR;
        }
        else if (bytes_rec == 0)
        {
            std::cerr << "Connection closed by client" << std::endl;
            close(m_connect_socket);
            close(m_socket);
            unlink(SOCK_PATH);
            m_connected = false;
            return SocketReadErr::CONNECTION_CLOSED;
        }

        return SocketReadErr::DATA_READ;
    }
};
