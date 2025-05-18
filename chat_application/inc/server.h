#ifndef _SERVER_H_
#define _SERVER_H_
#include <stdio.h>
#include <stdlib.h>

// Function to initialize the server socket
void start_app(int *port);

void *server_handle(void *arg); 

void *peer_handle(void *arg);

#endif /* _SERVER_H_ */