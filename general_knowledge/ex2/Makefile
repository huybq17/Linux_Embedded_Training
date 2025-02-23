.PHONY : clean all

PRJ_NAME := hello

CC := gcc
CFLAGS := -Wall -g -pedantic -fPIC

SHARED_LIB_NAME := shared_lib.so
OBJECTS := main.o

all: $(SHARED_LIB_NAME)

$(SHARED_LIB_NAME): $(OBJECTS)
	$(CC) -shared -o $(SHARED_LIB_NAME) $(OBJECTS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(SHARED_LIB_NAME) *.o app
