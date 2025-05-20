#include "conn_manager.h"
#include "common.h"
#include "peer_handle.h"
#include "server_sock.h"

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>


void *peer_data_handle(void *arg) {
    int peer_sock = *(int *)arg;
    char buffer[MAX_BUFFER_SIZE];
    int bytes_received;
    char peer_ip[INET_ADDRSTRLEN];
    struct sockaddr_in peer_addr;
    socklen_t peer_addr_len = sizeof(peer_addr);

    if (g_peer_conn_id < 0) {
        printf("Can not accept peer connection!\n");
        close(peer_sock);
        return NULL;
    }

    // Receive the actual port number from the peer
    getpeername(peer_sock, (struct sockaddr*)&peer_addr, &peer_addr_len);
    inet_ntop(AF_INET, &peer_addr.sin_addr, peer_ip, sizeof(peer_ip));

    // Receive data from the peer
    while (1) {
        if ((bytes_received = read(peer_sock, buffer, sizeof(buffer))) > 0) {
            buffer[bytes_received] = '\0';

            printf("\n==========================================\r\n");
            printf("Received from peer %s:%d: %s\r\n", peer_ip, g_actual_net_port, buffer);
            printf("==========================================\r\n");

            fflush(stdout);
        }

        if (bytes_received <= 0) {
            printf("Peer #%d disconnected.\r\n", g_peer_conn_id);
            remove_connection(g_peer_conn_id);
            close(peer_sock);
            break;
        }
    }
}

void peer_data_handle_start(int *peer_sock) {
    pthread_t peer_tid;
    int ret;

    ret = pthread_create(&peer_tid, NULL, peer_data_handle, (void *)peer_sock);
    if (ret != 0) {
        perror("pthread_create");
        exit(EXIT_FAILURE);
    }
    pthread_detach(peer_tid);
}
