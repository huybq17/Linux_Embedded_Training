// Purpose: create a simple UDP client
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) {
    const char *server_ip;
    int PORT;
    int sock;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];
    char input[BUFFER_SIZE];
    socklen_t server_addr_len = sizeof(server_addr);
    int valread;

    if (argc != 3) {
        printf("Usage: %s <server_ip> <server_port>\n", argv[0]);
        return EXIT_FAILURE;
    } else {
        PORT = atoi(argv[2]);
        *server_ip = argv[1]
    }

    // 1. Create socket
    if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("socket creation error");
        exit(EXIT_FAILURE);
    }

    // 2. Setup server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);

    if (inet_pton(AF_INET, server_ip, &server_addr.sin_addr) <= 0) {
        perror("Invalid address");
        exit(EXIT_FAILURE);
    }
    printf("Connected to server %s:%d.\nType messages to send:\n", server_ip, PORT);

    // 3. Send and receive messages
    while (1) {
        printf("> ");
        if (fgets(input, BUFFER_SIZE, stdin) == NULL) {
            break;
        }
        sendto(sock, input, strlen(input), 0, (struct sockaddr *)&server_addr, server_addr_len);

        valread = recvfrom(sock, buffer, BUFFER_SIZE, 0, (struct sockaddr *)&server_addr, &server_addr_len);
        if (valread < 0) {
            perror("recvfrom failed");
            break;
        }
        buffer[valread] = '\0';
        printf("Echo from server: %s", buffer);
    }

    // 5. Close socket
    close(sock);
    return 0;
}
