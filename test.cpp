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
#define DATA "Hello from server"



int main() {
    // init variables
    const char* SOCK_PATH = "/tmp/abc";
    int m_socket, connect_socket;
    int rc;
    socklen_t len;
    int bytes_rec {0};
    int backlog {10};

    struct sockaddr_un sockaddress;

    char buf[256];

    // clear structs and buffer
    memset(&sockaddress, 0, sizeof(struct sockaddr_un));
    memset(buf, 0, 256);

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

    printf("socket listening...\n");

    for(;;) {
        connect_socket = accept(m_socket, NULL, NULL);
        if (connect_socket == -1) {
            printf("Error while connecting");
            close(connect_socket);
            exit(1);
        }

        printf("after method");

        while ((bytes_rec = read(connect_socket, buf, 256)) > 0) {
            if (write(STDOUT_FILENO, buf, bytes_rec) != bytes_rec) {
            }
        }

        if (bytes_rec == -1){
            printf("Read error");
            close(connect_socket);
            close(m_socket);
            exit(1);
        }
    }
}