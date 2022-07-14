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
    RETRY,
    TERMINATED
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
    bool m_Connected{false};
    bool& m_Terminated;
    const char* SOCK_PATH;
    int m_Socket, m_Connect_Socket, rc;
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
        bytes_rec = read(m_Connect_Socket, &buff[0], SIZE);
        if (-1 == bytes_rec && EAGAIN == errno)
        {
            return SocketReadErr::NOTHING_TO_READ;
        }
        else if (-1 == bytes_rec)
        {
            std::cerr << "Read error" << std::endl;
            close(m_Connect_Socket);
            close(m_Socket);
            return SocketReadErr::READ_ERROR;
        }
        else if (0 == bytes_rec)
        {
            std::cerr << "Connection closed by client" << std::endl;
            close(m_Connect_Socket);
            close(m_Socket);
            unlink(SOCK_PATH);
            m_Connected = false;
            return SocketReadErr::CONNECTION_CLOSED;
        }

        return SocketReadErr::DATA_READ;
    }
};
