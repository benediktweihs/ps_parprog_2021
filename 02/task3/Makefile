CC = gcc
CFLAGS = -std=gnu11 -Wall -Wextra -lm

.PHONY: all
all: piSerial piParallel

.PHONY: clean
clean:
	$(RM) piSerial piParallel

piSerial: piSerial.c
	$(CC) $(CFLAGS) piSerial.c -o piSerial

piParallel: piParallel.c
	$(CC) $(CFLAGS) piParallel.c -o piParallel -lpthread