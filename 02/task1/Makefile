CC = gcc
CFLAGS = -std=gnu11 -Wall -Wextra -lm

.PHONY: all
all: mandelbrot

.PHONY: clean
clean:
	$(RM) mandelbrot mandelbrot.png

mandelbrot: mandelbrot.c
	$(CC) $(CFLAGS) mandelbrot.c -o mandelbrot
