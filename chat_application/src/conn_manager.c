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
static int next_peer_id = 0;


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

    conn_info.id = next_peer_id;
    conn_info.sockfd = peer_sock;
    strncpy(conn_info.ip, ip, INET_ADDRSTRLEN);
    conn_info.port = port;

    conn_list[num_peers++] = conn_info;
    next_peer_id++;

    return conn_info.id;
}

int remove_connection(int conn_id) {
    int i;

    // Find the connection with the specified ID
    for (i = 0; i < num_peers; i++) {
        if (conn_list[i].id == conn_id) {
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

    return NULL;
}

void print_connection_list() {
    int i;

    printf("\n============== CONNECTIONS LIST ===========\r\n\n");
    printf("ID   IP            Port\r\n");
    printf("---- ------------- ----\r\n");
    for (i = 0; i < num_peers; i++) {
        printf("%-4d %-13s %4d\n", conn_list[i].id, conn_list[i].ip, conn_list[i].port);
    }
    printf("\n============================================\r\n");
}

int terminate_connection(int conn_id) {
    conn_info_t *conn_info;

    conn_info = get_connection(conn_id);
    if (conn_info == NULL) {
        printf("Connection with ID %d not found.\r\n", conn_id);
        return -1;
    }

    close(conn_info->sockfd);
    remove_connection(conn_id);

    return 0;
}