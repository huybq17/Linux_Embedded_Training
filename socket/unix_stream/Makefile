.PHONY: clean all

BIN_PATH 			:= ./bin
CLIENT_NAME 		:= ustream_client
SERVER_NAME 		:= ustream_server
SOCKET_PATH 		:= /tmp/ustream_socket.sock
CC := gcc

all:
	@mkdir -p $(BIN_PATH)
	$(CC) -o $(BIN_PATH)/$(CLIENT_NAME) ustream_client.c
	$(CC) -o $(BIN_PATH)/$(SERVER_NAME) ustream_server.c

clean:
	rm -rf *.o $(BIN_PATH) $(SOCKET_PATH)
	@echo "Cleanup done."
