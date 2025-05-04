// purpose: create a simple TCP server
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>            
#include <arpa/inet.h>       
#include <netinet/in.h>     

#define BUFFER_SIZE  1024U
#define DEFAULT_PORT 12345U      // Default port if not specified

int main(int argc, char *argv[]) {
    int server_fd, client_fd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len;
    char buffer[BUFFER_SIZE];
    int port = DEFAULT_PORT;
    int bytes_read;

    // Allow user to input port number from command line
    if (argc != 2) {
        printf("Usage: %s <port>\n", argv[0]);
        return EXIT_FAILURE;
    } else {
        port = atoi(argv[1]); // Convert port string to integer
    }

    // 1. Create socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // 2. Set up server address
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;       // Accept any incoming IP
    server_addr.sin_port = htons(port);             // Convert port to network byte order

    // 3. Bind socket to address
    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // 4. Listen for incoming connections
    if (listen(server_fd, 5) == -1) {
        perror("listen failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }
    printf("Echo Server is listening on port %d...\n", port);

    while (1) {
        // 5. Accept a client connection
        client_len = sizeof(client_addr);
        if ((client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &client_len)) == -1) {
            perror("accept failed");
            continue;
        }
        printf("Connected with client: %s:%d\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

        // 6. Receive and echo back data
        while ((bytes_read = read(client_fd, buffer, BUFFER_SIZE)) > 0) {
            buffer[bytes_read] = '\0';
            printf("Received: %s", buffer);
            write(client_fd, buffer, bytes_read); // Echo data back to client
        }

        if (bytes_read == 0) {
            printf("Client disconnected.\n");
        } else {
            perror("read failed");
        }

        // 7. Close client socket
        close(client_fd);
        printf("Client socket closed.\n");
    }

    // 8. Close server socket
    close(server_fd);
    return 0;
}
