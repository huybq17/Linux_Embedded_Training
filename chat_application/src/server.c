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
#include "cli_cmd.h"


void* start_app_handle(void *arg) {
    int *port = (int *)arg;

    server_sock_start(port);
}

void start_app(int *port) {
    int ret;
    pthread_t start_app_tid;

    ret = pthread_create(&start_app_tid, NULL, start_app_handle, port);
    if (ret != 0) {
        perror("pthread_create");
        exit(EXIT_FAILURE);
    }
    pthread_detach(start_app_tid);
}

