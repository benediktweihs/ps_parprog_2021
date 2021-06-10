CFLAGS=-Wall -Wextra -std=gnu11 -pedantic -fopenmp -O1 -O2 -O3
CC=gcc
RM=rm
RMFLAGS=-rf
TARGETS=ex2 task2

all: $(TARGETS)

%: %.c
	$(CC) $(CFLAGS) $< -o $@

.PHONY: clean
clean:
	$(RM) $(RMFLAGS) $(TARGETS)


