.PHONY := clean all

CC = gcc
CFLAGS = -Wall -g -pedantic

LIB_NAME = lib.a
OBJECTS = main.o

all: $(LIB_NAME)

$(LIB_NAME): $(OBJECTS)
	ar rcs $(LIB_NAME) $(OBJECTS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(LIB_NAME) *.o app
