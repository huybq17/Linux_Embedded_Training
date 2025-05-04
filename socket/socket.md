# Socket Programming in Linux

## Introduction
This folder contains a series of exercises designed to provide hands-on experience with socket programming in Linux. Socket programming is a fundamental skill for network communication, enabling processes to exchange data over a network or within the same system. These exercises cover both UNIX domain sockets and Internet domain sockets, using both stream (TCP) and datagram (UDP) protocols.

## Objectives
- Understand the fundamentals of socket programming in Linux.
- Learn how to use UNIX domain sockets for inter-process communication on the same machine.
- Implement client-server communication using Internet domain sockets with both TCP and UDP protocols.
- Gain experience in handling socket creation, binding, sending, receiving, and closing connections.

## Exercises Overview
The folder is organized into subdirectories, each focusing on a specific type of socket communication:

### 1. `unix_dgram`
- Implements a client-server model using UNIX domain datagram sockets (UDP-like behavior).
- The server listens for messages from clients and responds to them.

### 2. `unix_stream`
- Implements a client-server model using UNIX domain stream sockets (TCP-like behavior).
- The server accepts connections from clients, exchanges messages.

### 3. `inet_dgram`
- Implements a client-server model using Internet domain datagram sockets (UDP).
- The server binds to a specified port and listens for incoming datagrams from client, echoing messages back.

### 4. `inet_stream`
- Implements a client-server model using Internet domain stream sockets (TCP).
- The server listens for incoming connections, accepts them, and exchanges messages with client.

## How to Run the Exercises
Each subdirectory contains a Makefile for running the client and server programs. Follow these steps to compile and run the exercises:


### Running the Programs

To run the server and client in the each folder:
1. Compile:
   ```sh
   > cd Makefile
   > make
   ```
2. Run the server:
   ```sh
   > ./server <port>
   ```
3. Run the client:
   ```sh
   > ./client <server_ip> <port>
   ```


## References
- [Beej's Guide to Network Programming](http://beej.us/guide/bgnet/)
- [Linux Socket Programming](https://man7.org/linux/man-pages/man7/socket.7.html)
- [UNIX Domain Sockets](https://man7.org/linux/man-pages/man7/unix.7.html)

