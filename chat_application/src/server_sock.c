#include "server.h"
#include "server_sock.h"
#include "common.h"
#include "conn_manager.h"

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define MAX_CONNECTIONS 10U
#define IP_ADDRESS "127.0.0.1"

static pthread_t start_app_tid;

static struct sockaddr_in server_addr;
static int server_sock, peer_sock;
static int num_peers = 0;

void *peer_data_handle(void *arg) {
    int peer_sock = *(int *)arg;
    char buffer[MAX_BUFFER_SIZE];
    int bytes_received;
    char peer_ip[INET_ADDRSTRLEN];
    int peer_port;
    int conn_id;

    struct sockaddr_in peer_addr;
    socklen_t peer_addr_len = sizeof(peer_addr);

    getpeername(peer_sock, (struct sockaddr*)&peer_addr, &peer_addr_len);
    printf("Peer connected from %s:%d\n", inet_ntoa(peer_addr.sin_addr),
              ntohs(peer_addr.sin_port));
    
    inet_ntop(AF_INET, &peer_addr.sin_addr, peer_ip, sizeof(peer_ip));
    peer_port = ntohs(peer_addr.sin_port);

    conn_id = add_connection(peer_sock, peer_ip, peer_port);
    if (conn_id == -1) {
        printf("Cannot add a new peer!\n");
        close(peer_sock);
        return NULL;
    }

    // Receive data from the peer
    while (1) {

        if ((bytes_received = read(peer_sock, buffer, sizeof(buffer))) > 0) {
            buffer[bytes_received] = '\0';
            printf("Received from peer %s:%d: %s\n", peer_ip, peer_port, buffer);
            fflush(stdout);
            // write(peer_sock, buffer, bytes_received); // Echo data back to client
        }

        if (bytes_received <= 0) {
            printf("Peer disconnected.\n");
            remove_connection(conn_id);
            close(peer_sock);
            break;
        }
    }

    // close(peer_sock);
}

// Handle peer connection
void peer_data_handle_start() {
    pthread_t peer_tid;
    int ret;

    ret = pthread_create(&peer_tid, NULL, peer_data_handle, (void *)&peer_sock);
    if (ret != 0) {
        perror("pthread_create");
        exit(EXIT_FAILURE);
    }
    pthread_detach(peer_tid); // Detach the thread to avoid memory leaks
}

// Initialize server socket
void server_sock_init(int *port) {
    // Initialize server socket
    server_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (server_sock < 0) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    // Set up the server address structure
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(*port);
    server_addr.sin_addr.s_addr = INADDR_ANY; // Listen on all interfaces

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

    // CLear the screen
    if (system("clear") != 0) {
        perror("system");
        exit(EXIT_FAILURE);
    }
    printf("Server is listening on port %d...\n", ntohs(server_addr.sin_port));

}

void *server_socket_handle(void *arg) {
    int *port = (int *)arg;
    struct sockaddr_in peer_addr;
    pthread_t peer_tid;
    socklen_t peer_addr_len = sizeof(peer_addr);

    // Initialize server socket
    server_sock_init(port);

    // Accept incoming connections
    while (1) {
        peer_sock = accept(server_sock, (struct sockaddr *)&peer_addr, &peer_addr_len);
        if (peer_sock < 0) {
            perror("accept");
            continue;
        }

        printf("Accepted connection from %s:%d\n>", inet_ntoa(peer_addr.sin_addr), ntohs(peer_addr.sin_port));

        // Handle the peer connection in a separate thread
        peer_data_handle_start();
        // pthread_create(&peer_tid, NULL, peer_handle, (void *)&peer_sock);
        // pthread_detach(peer_tid); // Detach the thread to avoid memory leaks
        num_peers++;
    }

}

void server_sock_start(int *port) {
    int ret;
    // printf("port: %d\n", *port);
    ret = pthread_create(&start_app_tid, NULL, server_socket_handle, port);
    if (ret != 0) {
        perror("pthread_create");
        exit(EXIT_FAILURE);
    }
    // Detach the thread to avoid memory leaks
    pthread_detach(start_app_tid);
}