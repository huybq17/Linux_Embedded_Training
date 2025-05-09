# Makefile for building a C application with static and shared libraries
.PHONY: all static-lib shared-lib clean

CC 			:= gcc
TARGET 		:= app
SRC_DIR 	:= app
OBJ_DIR 	:= obj
BIN_DIR 	:= bin

# library directories
LIB_DIR 		:= lib
STATIC_LIB_NAME := static-lib
SHARED_LIB_NAME := shared-lib
STATIC_LIB_DIR 	:= $(LIB_DIR)/$(STATIC_LIB_NAME)
SHARE_LIB_DIR 	:= $(LIB_DIR)/$(SHARED_LIB_NAME)
LIB_NAME 		:= k_lib

# source code files
APP_SRCS 	:= $(shell find $(SRC_DIR) -name "*.c")
LIB_SRCS	:= $(shell find $(LIB_DIR) -name "*.c")
SRCS 		= $(APP_SRCS) $(LIB_SRCS)

# object files
OBJS := $(SRCS:%.c=$(OBJ_DIR)/%.o)

# include files
INCS := $(LIB_DIR)/ $(SRC_DIR)/
INCS_PARAMS := $(INCS:%=-I%)

CFLAGS = -Wall $(INCS_PARAMS)

all: build

build: mkdir $(STATIC_LIB_NAME) $(SHARED_LIB_NAME)

mkdir:
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(BIN_DIR)
	@mkdir -p $(STATIC_LIB_DIR)
	@mkdir -p $(SHARE_LIB_DIR)

# Build static libraries
$(STATIC_LIB_NAME): $(OBJS)
	@ar rcs $(STATIC_LIB_DIR)/lib$(LIB_NAME).a $(OBJ_DIR)/$(LIB_DIR)/*.o
	$(CC) -L$(STATIC_LIB_DIR) -l$(LIB_NAME) $(CFLAGS) $^ -o $(BIN_DIR)/$(STATIC_LIB_NAME)
	@size $(BIN_DIR)/$(STATIC_LIB_NAME)

# Build shared libraries
$(SHARED_LIB_NAME): $(OBJS)
	$(CC) -fPIC -shared -o $(SHARE_LIB_DIR)/lib$(LIB_NAME).so $(OBJ_DIR)/$(LIB_DIR)/*.o
	$(CC) -L$(SHARE_LIB_DIR) -l$(LIB_NAME) $(CFLAGS) $^ -o $(BIN_DIR)/$(SHARED_LIB_NAME)
	@size $(BIN_DIR)/$(SHARED_LIB_NAME)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(shell dirname $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR) $(SHARE_LIB_DIR) $(STATIC_LIB_DIR)