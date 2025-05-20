#include "server.h"
#include "server_sock.h"
#include "common.h"
#include "conn_manager.h"
#include "peer_handle.h"

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


static void print_chat_application_banner(void);

static pthread_t start_app_tid;
static struct sockaddr_in server_addr;
static int server_sock;

int g_local_port = 0;
int g_actual_net_port = 0;
int g_peer_conn_id = 0;

static void print_chat_application_banner(void) {
    printf("\r\n");
    printf("=========================================\n");
    printf("   ██████╗██╗  ██╗ █████╗ ████████╗     \n");
    printf("  ██╔════╝██║  ██║██╔══██╗╚══██╔══╝     \n");
    printf("  ██║     ███████║███████║   ██║        \n");
    printf("  ██║     ██╔══██║██╔══██║   ██║        \n");
    printf("  ╚██████╗██║  ██║██║  ██║   ██║        \n");
    printf("   ╚═════╝╚═╝  ╚═╝╚═╝  ╚═╝   ╚═╝        \n");
    printf("     Chat Application Project           \n");
    printf("  Type 'help' for a list of commands    \n");
    printf("=========================================\r\n\n");
}


// Initialize server socket
void server_sock_init(int *port) {
    int conn_id;

    // Initialize server socket
    server_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (server_sock < 0) {
        perror("socket");
        exit(EXIT_FAILURE);
    }
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(*port);
    server_addr.sin_addr.s_addr = INADDR_ANY; // Listen on all interfaces

    if (bind(server_sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("bind");
        close(server_sock);
        exit(EXIT_FAILURE);
    }

    if (listen(server_sock, MAX_CONNECTIONS) < 0) {
        perror("listen");
        close(server_sock);
        exit(EXIT_FAILURE);
    }

    // Add the server connection to the list
    conn_id = add_connection(server_sock, inet_ntoa(server_addr.sin_addr), ntohs(server_addr.sin_port));
    if (conn_id == -1) {
        printf("Cannot add a new server connection!\r\n");
        close(server_sock);
        exit(EXIT_FAILURE);
    }

    if (system("clear") != 0) {
        perror("system");
        exit(EXIT_FAILURE);
    }

    print_chat_application_banner();
    printf("Server is listening on port %d...\r\n", ntohs(server_addr.sin_port));
}

void *server_socket_handle(void *arg) {
    int *port = (int *)arg;
    int peer_sock;
    struct sockaddr_in peer_addr;
    pthread_t peer_tid;
    socklen_t peer_addr_len;
    int net_port;

    // Initialize server socket
    server_sock_init(port);

    // Accept incoming connections
    while (1) {
        peer_addr_len = sizeof(peer_addr);
        peer_sock = accept(server_sock, (struct sockaddr *)&peer_addr, &peer_addr_len);
        if (peer_sock < 0) {
            perror("accept");
            continue;
        }

        // Receive the actual port number from the peer
        if (recv(peer_sock, &net_port, sizeof(net_port), 0) <= 0) {
            perror("recv");
            close(peer_sock);
            continue;
        }
        g_actual_net_port = ntohs(net_port);

        // Add the peer connection to the list
        if (net_port != server_addr.sin_port) {
            // Ignore the connection if it is from the server itself
            g_peer_conn_id = add_connection(peer_sock, inet_ntoa(peer_addr.sin_addr), g_actual_net_port);
            if (g_peer_conn_id == -1) {
                printf("Cannot add a new peer!\r\n");
                close(peer_sock);
                continue;
            }
        } else {
            // Ignore the connection if it is from the server
            g_peer_conn_id = 1;
        }

        printf("\n==========================================\r\n");
        printf("Accepted connection from %s:%d\r\n", inet_ntoa(peer_addr.sin_addr), g_actual_net_port);
        printf("==========================================\r\n");

        // Handle the peer connection in a separate thread
        peer_data_handle_start(&peer_sock);
    }
}

void server_sock_start(int *port) {
    int ret;
    g_local_port = *port;

    ret = pthread_create(&start_app_tid, NULL, server_socket_handle, port);
    if (ret != 0) {
        perror("pthread_create");
        exit(EXIT_FAILURE);
    }

    pthread_detach(start_app_tid);
}