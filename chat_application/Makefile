.PHONY: clean all

PRJ_NAME := chat

CUR_DIR := .
INC_DIR := $(CUR_DIR)/inc
SRC_DIR := $(CUR_DIR)/src
BIN_DIR := $(CUR_DIR)/bin
OBJ_DIR := $(CUR_DIR)/obj

CC := gcc
C_FLAGS := -c -fPIC -O2 -o

SRCS = $(wildcard $(SRC_DIR)/*.c) \
	   $(wildcard $(CUR_DIR)/*.c)

OBJS = $(patsubst %.c, $(OBJ_DIR)/%.o, $(notdir $(SRCS)))


all: $(BIN_DIR) $(OBJS)
	$(CC) -o $(BIN_DIR)/$(PRJ_NAME) $(OBJS) -I $(INC_DIR)

# Create the folders if not exist
$(BIN_DIR):
	@mkdir -p $(BIN_DIR)
	@mkdir -p $(OBJ_DIR)

# Rule for compiling .c files from current directory
$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(shell dirname $@)
	$(CC) $(C_FLAGS) $@ $< -I $(INC_DIR)

# Rule for compiling .c files from src directory
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(shell dirname $@)
	$(CC) $(C_FLAGS) $@ $< -I $(INC_DIR)

# Clean generated files
clean:
	rm -rf $(OBJ_DIR)
	rm -rf $(BIN_DIR)
	@echo "Cleanup done."
