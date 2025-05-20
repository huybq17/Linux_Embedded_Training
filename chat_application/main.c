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
#include "cli_cmd.h"
#include "common.h"


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
        port = atoi(argv[1]);
    }

    // start peer socket
    start_app(&port);

    while (1) {
        fflush(stdout);
        printf("> ");

        if (fgets(input, sizeof(input), stdin) == NULL) {
            perror("fgets");
            continue;
        }

        // Initialize the command line interface
        cli_cmd_init(input);
    }
}