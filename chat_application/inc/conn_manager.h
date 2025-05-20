#ifndef _CONN_MANAGER_H_
#define _CONN_MANAGER_H_

#include <netinet/in.h>


typedef struct {
    int id;
    int sockfd;
    char ip[INET_ADDRSTRLEN];
    int port;
} conn_info_t;


/**************************************************************************//**
 * @brief Add a new connection to the list
 *
 * @param peer_sock Socket file descriptor for the peer
 * @param ip IP address of the peer
 * @param port Port number of the peer
 *
 * @return Connection ID if successful, -1 if failed
 *****************************************************************************/
int add_connection(int peer_sock, const char* ip, int port);


/**************************************************************************//**
 * @brief Remove a connection from the list
 *
 * @param conn_id Connection ID to remove
 *
 * @return 0 if successful, -1 if failed
 *****************************************************************************/
int remove_connection(int conn_id);


/**************************************************************************//**
 * @brief Get connection information by ID
 *
 * @param conn_id Connection ID to search for
 *
 * @return Pointer to the connection information structure, or NULL if not found
 *****************************************************************************/
conn_info_t* get_connection(int conn_id);


/**************************************************************************//**
 * @brief Print the list of connections
 *
 *****************************************************************************/
void print_connection_list();


/**************************************************************************//**
 * @brief Terminate a connection by ID
 *
 * @param conn_id Connection ID to terminate
 *
 * @return 0 if successful, -1 if failed
 *****************************************************************************/
int terminate_connection(int conn_id);


#endif /* _CONN_MANAGER_H_ */