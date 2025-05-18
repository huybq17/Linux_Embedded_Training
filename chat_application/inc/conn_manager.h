#ifndef _CONN_MANAGER_H_
#define _CONN_MANAGER_H_

#include <netinet/in.h>

typedef struct {
    int id;
    int sockfd;
    char ip[INET_ADDRSTRLEN];
    int port;
} conn_info_t;

int add_connection(int peer_sock, const char* ip, int port);
int remove_connection(int conn_id);
conn_info_t* get_connection(int conn_id);
void print_connection_list();

#endif /* _CONN_MANAGER_H_ */