#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <iostream>


#define SOCK_PATH  "/tmp/abc"
#define DATA "Hello from server"

using namespace std;

int main() {
    // init variables
    int client_sock, server_sock, rc;
    socklen_t len;
    int bytes_rec {0};
    int backlog {10};

    struct sockaddr_un server_sockaddr;
    struct sockaddr_un client_sockaddr; 

    char buf[256];

    // clear structs and buffer
    memset(&server_sockaddr, 0, sizeof(struct sockaddr_un));
    memset(&client_sockaddr, 0, sizeof(struct sockaddr_un));
    memset(buf, 0, 256);

    // create unix domain stream socket
    server_sock = socket(AF_UNIX, SOCK_STREAM, 0);
    if (server_sock == -1){
        printf("SOCKET ERROR: %d\n");
        exit(1);
    }
    
    // setup unix sockaddr struct 
    server_sockaddr.sun_family = AF_UNIX;   
    strcpy(server_sockaddr.sun_path, SOCK_PATH); 
    len = sizeof(server_sockaddr);
    
    // unlink the file so bind will succeed
    unlink(SOCK_PATH);
    rc = bind(server_sock, (struct sockaddr *) &server_sockaddr, len);
    if (rc == -1){
        printf("BIND ERROR: %d\n");
        close(server_sock);
        exit(1);
    }

    // listen for incoming client socket
    rc = listen(server_sock, backlog);
    if (rc == -1){ 
        printf("LISTEN ERROR: %d\n");
        close(server_sock);
        exit(1);
    }
    printf("socket listening...\n");

    // accept incoming connection
    client_sock = accept(server_sock, (struct sockaddr *) &client_sockaddr, &len);
    if (client_sock == -1){
        printf("ACCEPT ERROR: %d\n");
        close(server_sock);
        close(client_sock);
        exit(1);
    }

    // get name of connected socket
    len = sizeof(client_sockaddr);
    rc = getpeername(client_sock, (struct sockaddr *) &client_sockaddr, &len);
    if (rc == -1){
        printf("GETPEERNAME ERROR: %d\n");
        close(server_sock);
        close(client_sock);
        exit(1);
    }
    else {
        printf("Client socket filepath: %s\n", client_sockaddr.sun_path);
    }

    // read and print data from connected socket
    printf("waiting to read...\n");
    bytes_rec = recv(client_sock, buf, sizeof(buf), 0);
    if (bytes_rec == -1){
        printf("RECV ERROR: %d\n");
        close(server_sock);
        close(client_sock);
        exit(1);
    }
    else {
        printf("DATA RECEIVED = %s\n", buf);
    }
}