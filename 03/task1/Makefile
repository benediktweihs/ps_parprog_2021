CFLAGS=-Wall -Wextra -std=gnu11 -pedantic -fopenmp -O1 -O2 -O3
CC=gcc
RM=rm
RMFLAGS=-rf
TARGETS=task1 task2 task3

all: $(TARGETS)

%: %.c
	$(CC) $(CFLAGS) $< -o $@

.PHONY: clean
clean:
	$(RM) $(RMFLAGS) $(TARGETS)


