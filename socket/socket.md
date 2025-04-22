# Socket Programming in Linux

## Introduction
This assignment aims to provide hands-on experience with socket programming in Linux. Sockets enable inter-process communication over a network, allowing applications to send and receive data between different machines or within the same system.

## Objectives
- Understand the fundamentals of socket programming in Linux.
- Implement a simple client-server model using TCP and UDP sockets.
- Learn how to establish, send, receive, and close connections using sockets.

## Prerequisites
Before starting, ensure you have:
- A Linux-based OS (Ubuntu, Debian, Fedora, etc.).
- A basic understanding of C/C++ or Python programming.
- Knowledge of networking concepts (IP, ports, protocols).

## Assignment Tasks
### 1. TCP Client-Server Implementation
- Implement a **TCP server** that:
  - Listens for incoming connections on a specified port.
  - Accepts connections from clients.
  - Receives messages from the client and sends responses.
  - Handles multiple clients using threads/processes.

- Implement a **TCP client** that:
  - Connects to the server on the specified IP and port.
  - Sends messages to the server and receives responses.

### 2. UDP Client-Server Implementation
- Implement a **UDP server** that:
  - Binds to a specified port.
  - Listens for incoming datagrams from clients.
  - Responds to client messages.

- Implement a **UDP client** that:
  - Sends messages to the server and waits for responses.

### 3. Error Handling & Robustness
- Implement error handling for socket creation, binding, connection failures, and data transmission.
- Ensure proper cleanup of sockets before termination.

## Sample Code Structure
```
├── tcp_server.c
├── tcp_client.c
├── udp_server.c
├── udp_client.c
├── README.md
```

## Compilation & Execution
Compile the programs using `gcc`:
```sh
gcc -o tcp_server tcp_server.c
gcc -o tcp_client tcp_client.c
```
Run the server first:
```sh
./tcp_server
```
Then, run the client in another terminal:
```sh
./tcp_client
```

For UDP, compile similarly and run the server before the client.

## Expected Output
- The server should start and wait for connections.
- The client should send a message, and the server should respond accordingly.
- The communication should continue until the client or server exits.

## Additional Tasks
- Implement message encryption using OpenSSL.
- Add logging for debugging purposes.
- Extend the client to support multiple concurrent connections.

## References
- [Beej's Guide to Network Programming](http://beej.us/guide/bgnet/)
- [Linux Socket Programming](https://man7.org/linux/man-pages/man7/socket.7.html)

