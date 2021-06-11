CFLAGS=-Wall -std=gnu11 -Werror -Wextra -O2
CC=gcc
LIBS=-fopenmp -lm
EXEC=analytically_stable main
TARGETS=analytically_stable equation_of_motion vector_operations
OBJECTS_STABLE=analytically_stable.o equation_of_motion.o vector_operations.o
OBJECTS=main.o equation_of_motion.o vector_operations.o

all: $(EXEC)

%.o: %.c %.h
	$(CC) $(CFLAGS) -c $<

analytically_stable: $(OBJECTS_STABLE)
	$(CC) $(CFLAGS) -o analytically_stable $^ $(LIBS)

main: $(OBJECTS)
	$(CC) $(CFLAGS) -o main $^ $(LIBS)

.PHONY: clean
clean:
	rm -rf $(EXEC) *.o
