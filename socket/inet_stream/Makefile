.PHONY: clean all

BIN_PATH 			:= ./bin
CLIENT_NAME 		:= inet_client
SERVER_NAME 		:= inet_server
SOCKET_PATH 		:= /tmp/inet_socket.sock
CC := gcc

all:
	@mkdir -p $(BIN_PATH)
	$(CC) -o $(BIN_PATH)/$(CLIENT_NAME) inet_client.c
	$(CC) -o $(BIN_PATH)/$(SERVER_NAME) inet_server.c

clean:
	rm -rf *.o $(BIN_PATH) $(SOCKET_PATH)
	@echo "Cleanup done."
