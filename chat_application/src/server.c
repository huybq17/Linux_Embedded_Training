#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "../inc/start_peer.h"

#define MAX_CONNECTIONS 10U

static struct sockaddr_in server_addr, peer_addr;
static pthread_t server_tid;
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

void* app_handle(void *arg) {
    int *port = (int *)arg;
    socklen_t peer_addr_len = sizeof(peer_addr);
    pthread_t peer_tid;


    // Accept incoming connections
    while (1) {
        peer_sock = accept(server_sock, (struct sockaddr *)&peer_addr, &peer_addr_len);
        if (peer_sock < 0) {
            perror("accept");
            continue;
        }

        printf("Accepted connection from %s:%d\n", inet_ntoa(peer_addr.sin_addr), ntohs(peer_addr.sin_port));

        // Handle the peer connection in a separate thread
        // pthread_create(&peer_tid, NULL, peer_handle, (void *)&peer_sock);
        // pthread_detach(peer_tid); // Detach the thread to avoid memory leaks
        num_peers++;
    }

    close(server_sock);
}

void start_app(int port) {
    int ret;

    // Create socket
    server_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (server_sock < 0) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    // Set up the server address structure
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(port);

    // Bind the socket to the specified port
    if (bind(server_sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("bind");
        close(server_sock);
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(server_sock, MAX_CONNECTIONS) < 0) {
        perror("listen");
        close(server_sock);
        exit(EXIT_FAILURE);
    }
    printf("Server is listening on port %d...\n", port);

    ret = pthread_create(&server_tid, NULL, app_handle, &port);
    pthread_detach(server_tid); 
}

