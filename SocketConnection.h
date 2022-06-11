#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <iostream>

#define BACKLOG 5

using namespace std;

class SocketConnection
{
private:
    const char* SOCK_PATH;
    int m_socket, connect_socket, rc;
    socklen_t len;
    int bytes_rec {0};
    int backlog {10};
    struct sockaddr_un sockaddress;

    char buf[256];
public:
    SocketConnection(const char* socketPath);
    ~SocketConnection() = default;

    int connect();
};
