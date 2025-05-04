#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>

#define SOCKET_PATH "/tmp/ustream_socket"
#define BUFFER_SIZE 100

int main() {
    int client_fd;
    struct sockaddr_un server_addr;
    char buffer[BUFFER_SIZE];

    // Create a new unix-stream socket
    client_fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (client_fd < 0) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    // Set up server address
    memset(&server_addr, 0, sizeof(struct sockaddr_un));
    server_addr.sun_family = AF_UNIX;
    strncpy(server_addr.sun_path, SOCKET_PATH, sizeof(server_addr.sun_path) - 1);

    // Connect to the server
    // Note: The server must be running and listening on the socket path
    // before the client can connect.
    // If the server is not running, the client will block here until it can connect.
    if (connect(client_fd, (struct sockaddr *)&server_addr, sizeof(struct sockaddr_un)) < 0) {
        perror("connect");
        exit(EXIT_FAILURE);
    }

    // Receive and echo data
    printf("Enter message: ");
    while (fgets(buffer, BUFFER_SIZE, stdin)) {
        write(client_fd, buffer, strlen(buffer));
        int n = read(client_fd, buffer, BUFFER_SIZE);
        if (n <= 0) break;
        buffer[n] = '\0';
        printf("Echo from server: %s", buffer);
        printf("Enter message: ");
    }

    close(client_fd);
    return 0;
}
