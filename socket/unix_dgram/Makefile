.PHONY: clean all

BIN_PATH 			:= ./bin
CLIENT_NAME 		:= $(BIN_PATH)/unix_dgram_client
SERVER_NAME 		:= $(BIN_PATH)/unix_dgram_server
CLIENT_SOCKET_PATH 	:= /tmp/unix_dgram_client.sock
SERVER_SOCKET_PATH	:= /tmp/unix_dgram_server.sock
CC := gcc

all:
	@mkdir -p $(BIN_PATH)
	$(CC) -o $(CLIENT_NAME) dgram_client.c
	$(CC) -o $(SERVER_NAME) dgram_server.c

clean:
	rm -rf *.o $(BIN_PATH) $(SERVER_SOCKET_PATH) $(CLIENT_SOCKET_PATH)
	@echo "Cleanup done."
