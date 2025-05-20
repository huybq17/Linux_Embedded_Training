# Chat Application

## Description

This is a chat application using socket programming on Linux. It supports multiple simultaneous peer connections, allowing users to send and receive messages in real time. The application also provides a command-line interface (CLI) for managing connections.

## Features

- Multiple peer connections
- Real-time message sending and receiving
- Connection list management
- CLI commands: view connections, disconnect, help, etc.
- Simple and user-friendly command-line interface

## Running the Programs
1. Navigate to the desired subdirectory:
   ```sh
   cd <subdirectory_name>
   ```
2. Compile the program:
   ```sh
   make
   ```
3. Run the application with the desired listening port as an argument:

   ```sh
   ./bin/chat <port>
   ```


## Supported CLI Commands

- `help` : Show the list of commands
- `list` : Display the current connection list
- `connect <ip> <port>` : Connect to another peer
- `disconnect <id>` : Disconnect from a peer by ID
- `exit` : Exit the application
- `myport` : Show the local port
- `myip` : Show the local IP address


## Debug & Memory Check

Use Valgrind to check for memory leaks:

```sh
valgrind ./bin/chat 2>&1 | tee ./valgrind/valgrind.log
```
