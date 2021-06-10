CFLAGS=-Wall -Wextra -std=gnu11 -pedantic -fopenmp -O1 -O2 -O3 -g
CC=gcc
RM=rm
RMFLAGS=-rf
TARGETS=merge_sort_iter merge_sort_parallel

all: $(TARGETS)

%: %.c
	$(CC) $(CFLAGS) $< -o $@

.PHONY: clean
clean:
	$(RM) $(RMFLAGS) $(TARGETS)


