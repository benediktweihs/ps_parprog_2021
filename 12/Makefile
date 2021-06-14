CFLAGS=-Wall -std=gnu11 -Werror -Wextra -O3 -fopenmp
CC=gcc
LIBS=-fopenmp -lm
EXEC=analytically_stable main main_parallel
TARGETS=analytically_stable equation_of_motion vector_operations
OBJECTS_STABLE=analytically_stable.o equation_of_motion.o vector_operations.o
OBJECTS=main.o equation_of_motion.o vector_operations.o
OBJECTS_PARALLEL=main_parallel.o equation_of_motion.o vector_operations.o

all: $(EXEC)

%.o: %.c %.h
	$(CC) $(CFLAGS) -c $<

analytically_stable: $(OBJECTS_STABLE)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

main: $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

main_parallel: $(OBJECTS_PARALLEL)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

.PHONY: clean
clean:
	rm -rf $(EXEC) *.o
