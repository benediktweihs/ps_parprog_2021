CFLAGS_SEQUENTIAL=-Wall -Werror -Wextra -g -std=gnu11
CFLAGS_PARALLEL=-Wall -Werror -Wextra -O3 -g -std=gnu11
CC=gcc
TARGETS=mm mm_parallel
LIBS=-lm -fopenmp
LIBS_PARALLEL=$(LIBS)

all: mm_parallel mm

mm_parallel:
	$(CC) $(CFLAGS_PARALLEL) -o $@ $@.c $(LIBS_PARALLEL)

mm:
	$(CC) $(CFLAGS_SEQUENTIAL) -o $@ $@.c $(LIBS)

.PHONY: clean
clean:
	rm -rf $(TARGETS)