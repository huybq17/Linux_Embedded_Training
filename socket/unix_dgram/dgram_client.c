#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>

#define SERVER_PATH "/tmp/echo_server.sock"
#define CLIENT_PATH "/tmp/echo_client.sock"
#define BUFFER_SIZE 1024U

int main() {
    int client_fd;
    struct sockaddr_un client_addr, server_addr;
    char buffer[BUFFER_SIZE] = {0};
    ssize_t bytes_received;

    unlink(CLIENT_PATH); // Remove the old file

    client_fd = socket(AF_UNIX, SOCK_DGRAM, 0);
    if (client_fd < 0) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    memset(&client_addr, 0, sizeof(client_addr));
    client_addr.sun_family = AF_UNIX;
    strncpy(client_addr.sun_path, CLIENT_PATH, sizeof(client_addr.sun_path) - 1);

    if (bind(client_fd, (struct sockaddr *)&client_addr, sizeof(client_addr)) < 0) {
        perror("bind");
        close(client_fd);
        exit(EXIT_FAILURE);
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sun_family = AF_UNIX;
    strncpy(server_addr.sun_path, SERVER_PATH, sizeof(server_addr.sun_path) - 1);

    // Get the user input
    printf("Enter message to send: ");
    fgets(buffer, BUFFER_SIZE, stdin);
    buffer[strcspn(buffer, "\n")] = '\0'; // Delete newline

    // Send to server
    if (sendto(client_fd, buffer, strlen(buffer), 0,
               (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("sendto");
        close(client_fd);
        exit(EXIT_FAILURE);
    }

    // Receive from server
    bytes_received = recvfrom(client_fd, buffer, BUFFER_SIZE - 1, 0, NULL, NULL);
    if (bytes_received < 0) {
        perror("recvfrom");
    } else {
        buffer[bytes_received] = '\0';
        printf("Echoed from server: %s\n", buffer);
    }

    close(client_fd);
    unlink(CLIENT_PATH);
    return 0;
}
