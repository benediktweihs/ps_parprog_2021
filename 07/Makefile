CFLAGS1=-Wall -Wextra -Werror -std=gnu11 -pedantic -fopenmp -O1
CFLAGS2=-Wall -Wextra -Werror -std=gnu11 -pedantic -fopenmp -ftree-vectorize
CFLAGS3=-Wall -Wextra -Werror -std=gnu11 -pedantic -fopenmp -O2 -fopenmp-simd
CC=gcc
RM=rm
RMFLAGS=-rf
TARGETS=task1_seq task1_vec task2_seq task3_seq

all: $(TARGETS)

task1_seq:
	$(CC) $(CFLAGS1) ./task1/task1.c -o ./task1/task1

task1_vec:
	$(CC) $(CFLAGS2) ./task1/task1.c -o ./task1/task1_vec

task2_seq:
	$(CC) $(CFLAGS3) ./task2/task2.c -o ./task2/task2

task3_seq:
	$(CC) $(CFLAGS1) ./task3/task3.c -o ./task3/task3

.PHONY: clean
clean:
	$(RM) $(RMFLAGS) ./task1/task1 ./task1/task1_vec ./task2/task2 ./task3/task3

