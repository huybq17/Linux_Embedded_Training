#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>

#define SERVER_PATH "/tmp/echo_server.sock"
#define BUFFER_SIZE 1024

int main() {
    int server_fd;
    struct sockaddr_un server_addr, client_addr;
    char buffer[BUFFER_SIZE];

    unlink(SERVER_PATH); // Delete old socket
    server_fd = socket(AF_UNIX, SOCK_DGRAM, 0);
    if (server_fd < 0) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sun_family = AF_UNIX;
    strncpy(server_addr.sun_path, SERVER_PATH, sizeof(server_addr.sun_path) - 1);

    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("bind");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Echo server listening on %s\n", SERVER_PATH);

    while (1) {
        socklen_t client_len = sizeof(client_addr);
        ssize_t received = recvfrom(server_fd, buffer, BUFFER_SIZE - 1, 0,
                                    (struct sockaddr *)&client_addr, &client_len);
        if (received < 0) {
            perror("recvfrom");
            continue;
        }

        buffer[received] = '\0';
        printf("Received: %s\n", buffer);

        // Send back the received data (echo)
        if (sendto(server_fd, buffer, received, 0,
                   (struct sockaddr *)&client_addr, client_len) < 0) {
            perror("sendto");
        }
    }

    close(server_fd);
    unlink(SERVER_PATH);

    return 0;
}
