// Purpose: create a simple UDP server
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define BUFFER_SIZE 1024U

int main(int argc, char *argv[]) {
    int PORT;
    int server_fd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_addr_len = sizeof(client_addr);
    char buffer[BUFFER_SIZE];
    int valread;

    if (argc != 2) {
        printf("Usage: %s <port>\n", argv[0]);
        return EXIT_FAILURE;
    } else {
        PORT = atoi(argv[1]);
    }

    // 1. Create socket
    if ((server_fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // 2. Assign IP address and PORT
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    // 3. Bind
    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }
    printf("UDP Server is listening on port %d...\n", PORT);

    // 4. Receive and echo back data
    while (1) {
        valread = recvfrom(server_fd, buffer, BUFFER_SIZE, 0, (struct sockaddr *)&client_addr, &client_addr_len);
        if (valread < 0) {
            perror("recvfrom failed");
            break;
        }
        buffer[valread] = '\0';
        printf("Received from client %s:%d: %s", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port), buffer);

        // Echo back to the client
        sendto(server_fd, buffer, valread, 0, (struct sockaddr *)&client_addr, client_addr_len);
    }

    // 5. Close socket
    close(server_fd);
    return 0;
}
