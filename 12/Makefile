CFLAGS=-Wall -std=gnu11 -Werror -Wextra -O2
CC=gcc
LIBS=-fopenmp -lm
EXEC=main
TARGETS=main equation_of_motion vector_operations
OBJECTS=main.o equation_of_motion.o vector_operations.o

%.o: %.c %.h
	$(CC) $(CFLAGS) -c $<

all: $(OBJECTS)
	$(CC) $(CFLAGS) -o $(EXEC) $^ $(LIBS)

.PHONY: clean
clean:
	rm -rf $(TARGETS) *.o
