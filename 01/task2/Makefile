CFLAGS=-Wall -Wextra -Werror -std=gnu11 -pedantic -fopenmp -O2 -O3
CC=gcc
RM=rm
RMFLAGS=-rf
TARGETS=slow medium fast

all: $(TARGETS)

%: %.c
	$(CC) $(CFLAGS) $< -o $@

.PHONY: clean
clean:
	$(RM) $(RMFLAGS) $(TARGETS)


