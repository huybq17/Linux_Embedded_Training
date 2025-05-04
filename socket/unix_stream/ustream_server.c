#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>

#define SOCKET_PATH "/tmp/ustream_socket"
#define BUFFER_SIZE 100

int main() {
    int server_fd, client_fd;
    struct sockaddr_un server_addr;
    char buffer[BUFFER_SIZE];

    // Create new unix-stream socket
    server_fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (server_fd < 0) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    // Delete ols sockets
    unlink(SOCKET_PATH);

    // Set up server address
    memset(&server_addr, 0, sizeof(struct sockaddr_un));
    server_addr.sun_family = AF_UNIX;
    strncpy(server_addr.sun_path, SOCKET_PATH, sizeof(server_addr.sun_path) - 1);

    // Bind the socket to the address
    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(struct sockaddr_un)) < 0) {
        perror("bind");
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(server_fd, 5) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    printf("Server is listening on %s...\n", SOCKET_PATH);

    // Accept a connection
    client_fd = accept(server_fd, NULL, NULL);
    if (client_fd < 0) {
        perror("accept");
        exit(EXIT_FAILURE);
    }

    // Receive and echo data
    int n;
    while ((n = read(client_fd, buffer, BUFFER_SIZE)) > 0) {
        buffer[n] = '\0';
        printf("Server received: %s\n", buffer);
        write(client_fd, buffer, n);
    }

    close(client_fd);
    close(server_fd);
    unlink(SOCKET_PATH);
    return 0;
}
