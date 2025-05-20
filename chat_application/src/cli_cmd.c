#include "cli_cmd.h"
#include "server_sock.h"
#include "server.h"
#include "common.h"
#include "conn_manager.h"
#include "cli_cmd_registration.h"

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>


/* ---------Main function to handle all cli commands-----------*/
void *cli_cmd_handle(void *arg) {
    int i = 0;
    char *input = (char *)arg;
    const cli_cmd_entry_t *cmd_table = cli_cmd_table;
    char *token = NULL;
    char *argv[MAX_INPUT_SIZE] = {};
    int argc = 0;
    char found_cmd = 0;

    if (input == NULL) {
        printf("Input is NULL\r\n");
        return NULL;
    }

    token = strtok(input, " ");
    while (token != NULL && argc < MAX_INPUT_SIZE) {
        argv[argc] = token;
        token = strtok(NULL, " ");
        argc++;
    }
    argv[argc] = NULL;

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
    if (strcmp(argv[0], "\n") == 0) {
        // Ignore empty command
    } else if (strcmp(argv[0], "\r") == 0) {
        // Ignore empty command
    } else if (found_cmd == 0) {
        printf("\nUnknown command: %s\r\n", argv[0]);
        printf("Type 'help' for a list of commands.\r\n");
    }
}


/*-------Initialize CLI command handling-------*/
void cli_cmd_init(char *input) {
    pthread_t cli_tid;
    int ret;

    ret = pthread_create(&cli_tid, NULL, cli_cmd_handle, input);
    if (ret != 0) {
        perror("Failed to create CLI thread");
        exit(EXIT_FAILURE);
    }
    pthread_detach(cli_tid);
}