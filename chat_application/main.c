#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include "server.h"
#include "server_sock.h"
#include "peer_sock.h"
#include "common.h"

// Default port if not specified
#define DEFAULT_PORT 12345U

int main(int argc, char *argv[]) {
    int server_fd;
    struct sockaddr_in server_addr;
    char input[MAX_BUFFER_SIZE];
    int port = DEFAULT_PORT;
    int ret;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <port>\n", argv[0]);
        exit(EXIT_FAILURE);
    } else {
        port = atoi(argv[1]); // Convert port string to integer
    }

    // TODO: add handle server thread
    

    // TODO: init_socket
    start_app(&port);

    while (1) {
        printf("> ");
        fflush(stdin);
        if (fgets(input, sizeof(input), stdin) == NULL) {
            perror("fgets");
            continue;
        }

        cli_cmd_init(input);

    }

}