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


/*******************************************************************************
 *********************  CLI's GET COMMAND PROTOTYPES   *************************
 ******************************************************************************/
static void cli_cmd_connect_handle(int argc, char **argv);
static void cli_cmd_help_handle(int argc, char **argv);
static void cli_cmd_send_handle(int argc, char **argv);
static void cli_cmd_list_handle(int argc, char **argv);
static void cli_cmd_myport_handle(int argc, char **argv);
static void cli_cmd_myip_handle(int argc, char **argv);
static void cli_cmd_terminate_handle(int argc, char **argv);
static void cli_cmd_exit_handle(int argc, char **argv);


/*******************************************************************************
 *********************  CLI's GET COMMAND INFOS   ******************************
 ******************************************************************************/
static const cli_cmd_info_t cli_cmd_connect_info = {
    .func = cli_cmd_connect_handle,
    .help_text = "Usage: connect <dest_ip> <port>         /* Connect to another peer */"
};

static const cli_cmd_info_t cli_cmd_send_info = {
    .func = cli_cmd_send_handle,
    .help_text = "Usage: send <connection_id> <message>   /* Send message to peer */"
};

static const cli_cmd_info_t cli_cmd_list_info = {
    .func = cli_cmd_list_handle,
    .help_text = "Usage: list                             /* List all connections */"
};

static const cli_cmd_info_t cli_cmd_help_info = {
    .func = cli_cmd_help_handle,
    .help_text = "Usage: help                             /* Display this help message */"
};

static const cli_cmd_info_t cli_cmd_myport_info = {
    .func = cli_cmd_myport_handle,
    .help_text = "Usage: myport                           /* Show this process's listening  */"
};

static const cli_cmd_info_t cli_cmd_myip_info = {
    .func = cli_cmd_myip_handle,
    .help_text = "Usage: myip                             /* Show this process's IP address */"
};

static const cli_cmd_info_t cli_cmd_terminate_info = {
    .func = cli_cmd_terminate_handle,
    .help_text = "Usage: terminate <id>                   /* Terminate connection with ID */"
};

static const cli_cmd_info_t cli_cmd_exit_info = {
    .func = cli_cmd_exit_handle,
    .help_text = "Usage: exit                             /* Close all connections and exit */"
};

/*******************************************************************************
 *********************  CLI's GET COMMAND TABLE   ********************************
 ******************************************************************************/
const cli_cmd_entry_t cli_cmd_table[] = {
    {"connect", &cli_cmd_connect_info},
    {"send", &cli_cmd_send_info},
    {"list", &cli_cmd_list_info},
    {"myport", &cli_cmd_myport_info},
    {"help", &cli_cmd_help_info},
    {"myip", &cli_cmd_myip_info},
    {"terminate", &cli_cmd_terminate_info},
    {"exit", &cli_cmd_exit_info},
    {NULL, NULL} // End of command table
};


/*******************************************************************************
 *********************  CLI's GET COMMAND HANDLER   *****************************
 ******************************************************************************/
void cli_cmd_connect_handle(int argc, char **argv) {
    if (argc != 3) {
        printf("Usage: connect <dest_ip> <port>\n");
        return;
    }
    struct sockaddr_in peer_addr;
    int peer_sock;
    int conn_id;
    int peer_local_port;

    const char *dest_ip = argv[1];
    int dest_port = atoi(argv[2]);

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
        return;
    }

    if (connect(peer_sock, (struct sockaddr *)&peer_addr, sizeof(peer_addr)) == -1) {
        perror("connect failed");
        close(peer_sock);
        return;
    } else {
        printf("Connected to %s:%d\r\n", inet_ntoa(peer_addr.sin_addr), ntohs(peer_addr.sin_port));
    }

    peer_local_port = ntohs(g_local_port);
    // Send the actual port number to the peer
    if (send(peer_sock, &peer_local_port, sizeof(peer_local_port), 0) <= 0) {
        perror("send");
        close(peer_sock);
        return;
    }

    // Add the connection to the list
    conn_id = add_connection(peer_sock, inet_ntoa(peer_addr.sin_addr), ntohs(peer_addr.sin_port));
    if (conn_id == -1) {
        printf("Cannot add a new peer!\r\n");
        close(peer_sock);
        return;
    }

}

void cli_cmd_help_handle(int argc, char **argv) {
    int i = 0;
    const cli_cmd_entry_t *cmd_table = cli_cmd_table;

    if (argc != 1) {
        printf("%s\n", cli_cmd_help_info.help_text);
        return;
    }

    printf("\n================== HELP ===============\r\n\n");
    for (i = 0; cmd_table[i].name != NULL; i++) {
        printf("%s\n", cmd_table[i].cmd->help_text);
    }
    printf("\n=========================================\r\n");
}

void cli_cmd_send_handle(int argc, char **argv) {
    if (argc != 3) {
        printf("%s\n", cli_cmd_send_info.help_text);
        return;
    }

    int conn_id = atoi(argv[1]);
    const char *buffer = argv[2];
    conn_info_t *conn_info;
    int ret;
    int bytes_sent;

    if (strlen(buffer) > MAX_BUFFER_SIZE) {
        printf("Message is too long. Maximum length is %d characters.\r\n", MAX_BUFFER_SIZE);
        return;
    }

    conn_info = get_connection(conn_id);
    if (conn_info == NULL) {
        printf("Connection with ID %d not found.\r\n", conn_id);
        return;
    }

    bytes_sent = send(conn_info->sockfd, buffer, strlen(buffer), 0);
    if (bytes_sent < 0) {
        printf("Failed to send message to connection ID %d\r\n", conn_id);
        return;
    } else {
        printf("\n========================================\r\n");
        printf("Sent to connection #%d: %s\r\n", conn_id, buffer);
        printf("========================================\r\n");
    }
}

void cli_cmd_list_handle(int argc, char **argv) {
    print_connection_list();
}

void cli_cmd_myip_handle(int argc, char **argv) {
    char myip[INET_ADDRSTRLEN];
    struct sockaddr_in local_addr;
    struct sockaddr_in fake_addr;
    socklen_t addr_len = sizeof(local_addr);
    int fake_sock;

    if (argc != 1) {
        printf("%s\n", cli_cmd_myip_info.help_text);
        return;
    }

    fake_sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (fake_sock < 0) {
        perror("socket");
        return;
    }

    // Set up a fake address to connect to Google DNS (not sending any data)
    memset(&fake_addr, 0, sizeof(fake_addr));
    fake_addr.sin_family = AF_INET;
    fake_addr.sin_port = htons(53);  // DNS port
    inet_pton(AF_INET, "8.8.8.8", &fake_addr.sin_addr);

    if (connect(fake_sock, (struct sockaddr *)&fake_addr, sizeof(fake_addr)) < 0) {
        perror("connect");
        close(fake_sock);
        return;
    }

    // Get the local IP address
    if (getsockname(fake_sock, (struct sockaddr *)&local_addr, &addr_len) == -1) {
        perror("getsockname");
        return;
    }

    inet_ntop(AF_INET, &local_addr.sin_addr, myip, sizeof(myip));

    printf("\n========================================\r\n");
    printf("Local IP address: %s\n", myip);
    printf("========================================\r\n");

    close(fake_sock);
}

void cli_cmd_terminate_handle(int argc, char **argv) {
    int conn_id;

    if (argc != 2) {
        printf("%s\n", cli_cmd_terminate_info.help_text);
        return;
    }

    conn_id = atoi(argv[1]);
    if (conn_id == 0) {
        printf("Cannot terminate root ID: %d\r\n", conn_id);
        return;
    }

    if (terminate_connection(conn_id) != -1) {
        printf("\n=============================================\r\n");
        printf("Connection with ID %d terminated successfully.\r\n", conn_id);
        printf("=============================================\r\n");

    } else {
        printf("Failed to terminate connection with ID %d.\r\n", conn_id);
    }
}

void cli_cmd_exit_handle(int argc, char **argv) {
    int i;
    conn_info_t *conn_info;

    if (argc != 1) {
        printf("%s\n", cli_cmd_exit_info.help_text);
        return;
    }

    printf("\n========================================\r\n");
    printf("Closing all connections and exiting...\n");
    printf("========================================\r\n");

    for (i = 0; i < MAX_CONNECTIONS; i++) {
        conn_info = get_connection(i+1);
        if (conn_info != NULL) {
            terminate_connection(conn_info->id);
        }
    }

    exit(0);
}

void cli_cmd_myport_handle(int argc, char **argv) {
    if (argc != 1) {
        printf("%s\n", cli_cmd_myport_info.help_text);
        return;
    }

    printf("\n==================================\r\n");
    printf("My port: %d\n", g_local_port);
    printf("==================================\r\n");
}
