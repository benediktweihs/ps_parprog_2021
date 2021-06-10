CFLAGS=-Wall -std=gnu11 -Werror -Wextra -fopenmp -O2 -ftree-vectorize -fopt-info-vec-all
CC=gcc
TARGETS=analysis

all: $(TARGETS)

%: %.c
	module load gcc/8.2.0 && $(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf $(TARGETS)
