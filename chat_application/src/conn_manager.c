#include "server_sock.h"
#include "conn_manager.h"
#include "common.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

conn_info_t conn_list[MAX_CONNECTIONS];
static int num_peers = 0;
static int next_peer_id = 1;


int add_connection(int peer_sock, const char* ip, int port) {
    conn_info_t conn_info;
    int i;

    // Check if the connection list is full
    if (num_peers >= MAX_CONNECTIONS) {
        printf("Connection list is full. Cannot add new connection.\n");
        return -1;
    }

    for (i = 0; i < num_peers; i++) {
        if (strcmp(conn_list[i].ip, ip) == 0 && conn_list[i].port == port) {
            printf("Connection already exists: %s:%d\n", ip, port);
            return -1;
        }
    }

    // Add the new connection to the list
    conn_info.id = next_peer_id++;
    conn_info.sockfd = peer_sock;
    strncpy(conn_info.ip, ip, INET_ADDRSTRLEN);
    conn_info.port = port;

    conn_list[num_peers++] = conn_info;

    return conn_info.id;
}

int remove_connection(int conn_id) {
    int i;

    // Find the connection with the specified ID
    for (i = 0; i < num_peers; i++) {
        if (conn_list[i].id == conn_id) {
            // Close the socket and remove the connection from the list
            close(conn_list[i].sockfd);
            memmove(&conn_list[i], &conn_list[i + 1], (num_peers - i - 1) * sizeof(conn_info_t));
            num_peers--;
            return 0;
        }
    }

    printf("Connection with ID %d not found.\n", conn_id);
    return -1;
}

conn_info_t* get_connection(int conn_id) {
    int i;

    // Find the connection with the specified ID
    for (i = 0; i < num_peers; i++) {
        if (conn_list[i].id == conn_id) {
            return &conn_list[i];
        }
    }

    printf("Connection with ID %d not found.\n", conn_id);
    return NULL;
}

void print_connection_list() {
    int i;

    printf("Current connections:\n");
    for (i = 0; i < num_peers; i++) {
        printf("ID: %d, IP: %s, Port: %d\n", conn_list[i].id, conn_list[i].ip, conn_list[i].port);
    }
}