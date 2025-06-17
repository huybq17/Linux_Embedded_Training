#ifndef _SERVER_SOCK_H_
#define _SERVER_SOCK_H_


extern int g_local_port;        // Share local port with other files
extern int g_actual_net_port;   // Actual port number received from the peer
extern int g_peer_conn_id;      // The port number received from the peer


/**************************************************************************//**
 * @brief Start the server socket
 *
 * @param port Pointer to the port number
 *
 *****************************************************************************/
void server_sock_start(int *port);


#endif /* _SERVER_SOCK_H_ */