// purpose: create a simple TCP client
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>             
#include <arpa/inet.h>          
#include <netinet/in.h>         

#define BUFFER_SIZE     1024U
#define DEFAULT_PORT    12345U      // Default port if not specified
#define DEFAULT_IP      "127.0.0.1" // Default IP if not specified

int main(int argc, char *argv[]) {
    const char *server_ip = argv[1];
    int server_port = DEFAULT_PORT;
    int sock_fd;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];
    char input[BUFFER_SIZE];
    int bytes_received;

    if (argc != 3) {
        printf("Usage: %s <server_ip> <server_port>\n", argv[0]);
        return EXIT_FAILURE;
    } else {
        server_port = atoi(argv[2]); // Convert port string to integer
        server_ip = argv[1]; // Get server IP from command line
    }

    // 1. Create socket
    if ((sock_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // 2. Set up server address
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(server_port);

    if (inet_pton(AF_INET, server_ip, &server_addr.sin_addr) <= 0) {
        perror("invalid address / address not supported");
        close(sock_fd);
        exit(EXIT_FAILURE);
    }

    // 3. Connect to server
    if (connect(sock_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("connect failed");
        close(sock_fd);
        exit(EXIT_FAILURE);
    }

    printf("Connected to %s:%d\n", server_ip, server_port);

    // 4. Loop to send and receive data
    while (1) {
        printf("Input: ");
        if (fgets(input, BUFFER_SIZE, stdin) == NULL) {
            break;
        }

        // Send input to server
        send(sock_fd, input, strlen(input), 0);

        // Receive echo from server
        bytes_received = read(sock_fd, buffer, BUFFER_SIZE - 1);
        if (bytes_received <= 0) {
            printf("Server disconnected.\n");
            break;
        }

        buffer[bytes_received] = '\0';
        printf("Echo: %s", buffer);
    }

    // Close connection
    close(sock_fd);
    return 0;
}
