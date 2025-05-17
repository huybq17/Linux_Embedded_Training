#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include "inc/server.h"

#define DEFAULT_PORT 12345U      // Default port if not specified

int main(int argc, char *argv[]) {
    int server_fd;
    struct sockaddr_in server_addr;
    char input[50];
    int port = DEFAULT_PORT;
    pthread_t server_tid;
    int ret;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <port>\n", argv[0]);
        exit(EXIT_FAILURE);
    } else {
        port = atoi(argv[1]); // Convert port string to integer
    }

    // TODO: add handle server thread
    

    // TODO: init_socket
    start_app(port);

    while (1) {
        printf("> ");
        fflush(stdin);
        fgets(input, sizeof(input), stdin);

        // TODO: handle input
        pthread_join(server_tid, NULL);
    }



}