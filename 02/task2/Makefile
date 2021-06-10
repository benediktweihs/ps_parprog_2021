CC = gcc
CFLAGS = -std=gnu11 -Wall -Wextra -lm

.PHONY: all
all: hadamard1 hadamard2

.PHONY: clean
clean:
	$(RM) hadamard1 hadamard2

hadamard1: hadamard1.c
	$(CC) $(CFLAGS) hadamard1.c -o hadamard1

hadamard2: hadamard2.c
	$(CC) $(CFLAGS) hadamard2.c -o hadamard2
