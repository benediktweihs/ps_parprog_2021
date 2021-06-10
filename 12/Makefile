CFLAGS=-Wall -std=gnu11 -Werror -Wextra -O2
CC=gcc
LIBS=-fopenmp
EXEC=main
TARGETS=main equation_of_motion
OBJECTS=main.o equation_of_motion.o

%.o: %.c %.h
	$(CC) $(CFLAGS) -c $<

all: $(OBJECTS)
	$(CC) $(CFLAGS) -o $(EXEC) $^ $(LIBS)

.PHONY: clean
clean:
	rm -rf $(TARGETS) *.o
