.PHONY: clean all

PRJ_NAME := exec

CUR_DIR := .
INC_DIR := $(CUR_DIR)/inc
SRC_DIR := $(CUR_DIR)/src
BIN_DIR := $(CUR_DIR)/bin
OBJ_DIR := $(CUR_DIR)/obj

CC := gcc
C_FLAGS := -c -fPIC -o

all: $(BIN_DIR) $(OBJ_DIR)/main.o $(OBJ_DIR)/new_program.o
	$(CC) -o $(BIN_DIR)/$(PRJ_NAME) $(OBJ_DIR)/main.o $(OBJ_DIR)/new_program.o -I $(INC_DIR)

# Create the folders if not exist
$(BIN_DIR):
	@mkdir -p $(BIN_DIR)

$(OBJ_DIR)/%.o: %.c $(INC_DIR)
	@mkdir -p $(shell dirname $@)
	$(CC) $(C_FLAGS) $@ $< -I $(INC_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INC_DIR)
	@mkdir -p $(shell dirname $@)
	$(CC) $(C_FLAGS) $@ $< -I $(INC_DIR)


# Clean generated files
clean:
	rm -rf $(OBJ_DIR)/*
	rm -rf $(BIN_DIR)/*
	rmdir $(OBJ_DIR) $(BIN_DIR) 2>/dev/null || true
	@echo "Cleanup done."
