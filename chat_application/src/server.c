#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "server.h"
#include "server_sock.h"
#include "peer_sock.h"

#define MAX_CONNECTIONS 10U

static struct sockaddr_in server_addr, peer_addr;
static pthread_t start_app_tid;
static int server_sock, peer_sock;
static int num_peers = 0;

// Function to handle peer connections
void *peer_handle(void *arg) {
    int peer_sock = *(int*)arg;
    char buffer[50];
    int bytes_received;


    // Receive data from the peer
    while (1) {
        bytes_received = recv(peer_sock, buffer, sizeof(buffer), 0);
        if (bytes_received <= 0) {
            printf("Peer disconnected\n");
            close(peer_sock);
            num_peers--;
            break;
        }
        buffer[bytes_received] = '\0'; // Null-terminate the received string
        printf("Received from peer: %s\n", buffer);
    }

}


void* start_app_handle(void *arg) {
    int *port = (int *)arg;

    // printf("port: %d\n", port);
    server_sock_start(port);

    // peer_sock_start();

    // cli_cmd_init();

}

void start_app(int *port) {
    int ret;

    // Initialize start app thread
    ret = pthread_create(&start_app_tid, NULL, start_app_handle, port);
    if (ret != 0) {
        perror("pthread_create");
        exit(EXIT_FAILURE);
    }
    pthread_detach(start_app_tid); 
}

