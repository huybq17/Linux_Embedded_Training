#include "peer_sock.h"
#include "server_sock.h"
#include "server.h"
#include "common.h"
#include "conn_manager.h"

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define MAX_INPUT_SIZE 4U


void cli_cmd_connect_handle(int argc, char **argv);
void cli_cmd_help_handle(int argc, char **argv);
void cli_cmd_send_handle(int argc, char **argv);
void cli_cmd_list_handle(int argc, char **argv);
void cli_cmd_myport_handle(int argc, char **argv);
void cli_cmd_myip_handle(int argc, char **argv);
void cli_cmd_terminate_handle(int argc, char **argv);
void cli_cmd_exit_handle(int argc, char **argv);

static const cli_cmd_info_t cli_cmd_connect_info = {
    .func = cli_cmd_connect_handle,                 // Function pointer to the command function
    .help_text = "Usage: connect <dest_ip> <port>"  // Help message for the command
};

static const cli_cmd_info_t cli_cmd_send_info = {
    .func = cli_cmd_send_handle, 
    .help_text = "Usage: connect <connection_id> <message>"
};

// static const cli_cmd_info_t cli_cmd_list_info = {
//     .func = cli_cmd_list_handle, 
//     .help_text = "Usage: list"
// };

static const cli_cmd_info_t cli_cmd_help_info = {
    .func = cli_cmd_help_handle,
    .help_text = "Usage: help"
};

// static const cli_cmd_info_t cli_cmd_myport_info = {
//     .func = cli_cmd_myport_handle,
//     .help_text = "Usage: myport - Show this process's listening port"
// };

// static const cli_cmd_info_t cli_cmd_myip_info = {
//     .func = cli_cmd_myip_handle,
//     .help_text = "Usage: myip - Show this process's IP address"
// };

// static const cli_cmd_info_t cli_cmd_terminate_info = {
//     .func = cli_cmd_terminate_handle,
//     .help_text = "Usage: terminate <id> - Terminate connection with ID"
// };

// static const cli_cmd_info_t cli_cmd_exit_info = {
//     .func = cli_cmd_exit_handle,
//     .help_text = "Usage: exit - Close all connections and exit"
// };

static const cli_cmd_entry_t cli_cmd_table[] = {
    {"connect", &cli_cmd_connect_info},
    // {"send", &cli_cmd_send_info},
    // {"list", &cli_cmd_list_info},
    // {"myport", &cli_cmd_myport_info},
    {"help", &cli_cmd_help_info},
    // {"myip", &cli_cmd_myip_info},
    // {"terminate", &cli_cmd_terminate_info},
    // {"exit", &cli_cmd_exit_info},
    {NULL, NULL} // End of command table
};


/*--- Handle CLI commands ----*/

// Handle the "connect" command
void cli_cmd_connect_handle(int argc, char **argv) {
    if (argc != 3) {
        printf("Usage: connect <dest_ip> <port>\n");
        return;
    }
    struct sockaddr_in peer_addr;
    int peer_sock;
    int conn_id;

    // Extract the destination IP and port from the arguments
    const char *dest_ip = argv[1];
    int dest_port = atoi(argv[2]);

    // Create a socket for peer connection
    peer_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (peer_sock < 0) {
        perror("socket");
        return;
    }

    memset(&peer_addr, 0, sizeof(peer_addr));
    peer_addr.sin_family = AF_INET;
    peer_addr.sin_port = htons(dest_port);

    // Convert the destination IP address from string to binary form
    if (inet_pton(AF_INET, dest_ip, &peer_addr.sin_addr) <= 0) {
        perror("inet_pton");
        close(peer_sock);
        // return;
    }

    // Connect to the peer
    if (connect(peer_sock, (struct sockaddr *)&peer_addr, sizeof(peer_addr)) == -1) {
        perror("connect failed");
        close(peer_sock);
        // exit(EXIT_FAILURE);
    } else {
        printf("Connected to %s:%d\n", inet_ntoa(peer_addr.sin_addr), ntohs(peer_addr.sin_port));
    }

    conn_id = add_connection(peer_sock, dest_ip, dest_port);
    if (conn_id == -1) {
        printf("Cannot add a new peer!\n");
        close(peer_sock);
        return;
    }

}

// Handle the "help" command
void cli_cmd_help_handle(int argc, char **argv) {
    int i = 0;
    const cli_cmd_entry_t *cmd_table = cli_cmd_table;

    // Print the help message for each command in the command table
    for (i = 0; cmd_table[i].name != NULL; i++) {
        printf("%s\n", cmd_table[i].cmd->help_text);
    }
}

// void cli_cmd_send_handle(int argc, char **argv) {
//     if (argc != 3) {
//         printf("Usage: send <connection_id> <message>\n");
//         return;
//     }
//     int connection_id = atoi(argv[1]);
//     const char *message = argv[2];

// }

// Handle all cli commands
void *cli_cmd_handle(void *arg) {
    int i = 0;
    char *input = (char *)arg;
    const cli_cmd_entry_t *cmd_table = cli_cmd_table;
    char *token = NULL;
    char *argv[MAX_INPUT_SIZE] = {};
    int argc = 0;
    char found_cmd = 0;

    // Check if the input is NULL
    if (input == NULL) {
        printf("Input is NULL\n");
        return NULL;
    }

    // Parse the input command
    token = strtok(input, " ");
    while (token != NULL && argc < MAX_INPUT_SIZE) {
        argv[argc] = token;
        token = strtok(NULL, " ");
        argc++;
    }
    argv[argc] = NULL; // Null-terminate the argument list

    // Find the command in the command table
    for (i = 0; cmd_table[i].name != NULL; i++) {
        if (strstr(argv[0], cmd_table[i].name)) {
            // Call the command function
            cmd_table[i].cmd->func(argc, argv);
            found_cmd = 1;
            break;
        }
    }

    // If command not found, print an error message
    if ((argc == 0) || (found_cmd == 0)) {
        printf("Unknown command: %s\n", argv[0]);
        printf("Type 'help' for a list of commands.\n> ");
    }    

    // return NULL;
}


/*-------Initialize CLI command handling-------*/
void cli_cmd_init(char *input) {
    pthread_t cli_tid;
    int ret;

    // Initialize the command table
    ret = pthread_create(&cli_tid, NULL, cli_cmd_handle, input);
    if (ret != 0) {
        perror("Failed to create CLI thread");
        exit(EXIT_FAILURE);
    }
    pthread_detach(cli_tid); // Detach the thread to avoid memory leaks
}