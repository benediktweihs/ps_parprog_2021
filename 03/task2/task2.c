#include <errno.h>
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define PERROR fprintf(stderr, "%s:%d: error: %s\n", __FILE__, __LINE__, strerror(errno))

#define PERROR_GOTO(label) \
	do { \
		PERROR; \
		goto label; \
	} while (0)


#define INIT_ARRAY(arr, label) \
	do { \
		if (!(arr)) PERROR_GOTO(label); \
		for (long i = 0; i < n; ++i) { \
			(arr)[i] = malloc(sizeof(**(arr)) * n); \
			if (!(arr)[i]) PERROR_GOTO(label); \
		} \
	} while (0)

void free_2d_array(int **arr, long len) {
	if (!arr) {
		return;
	}
	for (long i = 0; i < len; ++i) {
		if (!arr[i]) {
			break;
		}
		free(arr[i]);
	}
	free(arr);
}

int main(int argc, char **argv) {
	// handle input
	if (argc != 2) {
		fprintf(stderr, "Error: usage: %s <n>\n", argv[0]);
		return EXIT_FAILURE;
	}

    // get n and check for errors
	errno = 0;
	char *str = argv[1];
	char *endptr;
	long n = strtol(str, &endptr, 0);
	if (errno != 0) {
		perror("strtol");
		return EXIT_FAILURE;
	}
	if (endptr == str) {
		fprintf(stderr, "Error: no digits were found!\n");
		return EXIT_FAILURE;
	}
	if (n < 0) {
		fprintf(stderr, "Error: matrix size must not be negative!\n");
		return EXIT_FAILURE;
	}

    // allocation & definition
    int status = EXIT_FAILURE;
    int **a = malloc(sizeof(*a) * n);
    INIT_ARRAY(a, error_a);
    int **b = malloc(sizeof(*b) * n);
    INIT_ARRAY(b, error_b);
    status = EXIT_SUCCESS;
    unsigned long res = 0;  // final result

    // fill matrices
	srand((int) time(NULL));
    for (long i = 0; i < n; ++i) {
        for (long j = 0; j < n; ++j) {
            a[i][j] = rand();
            b[i][j] = rand();
        }
    }
    
    // start time measurement
	double start_time = omp_get_wtime();

    // matrix multiplication
    #pragma omp parallel
    {
		// devide the square
        int local_res = 0;
        int index = omp_get_thread_num();
        int num_threads = omp_get_num_threads();
        int n_actual = n * n / num_threads;
        int n_begin = index * n_actual;
        if (index == num_threads - 1) {
            n_actual += (n * n) % num_threads;
        }

        // allocate array
        int *c = calloc(n_actual, sizeof(int));
        
		// garbage collection in parallel section
		if (!c) {
		    free(c);
			#pragma omp critical
			{
				if(index == 0){
				free(a);
				free(b);
				}
			}
            exit(EXIT_FAILURE);
        }

        for (long i = 0; i < n_actual; ++i) {
    		for (long k = 0; k < n; ++k) {
    		    c[i] += a[(n_begin + i) / n][k] * b[k][(n_begin + i) % n];
            }
        }

        // compute sum
	    for (long i = 0; i < n_actual; ++i) local_res += c[i];
        free(c);

        #pragma omp critical
        res += local_res;  // directly write to final result
	}

	double end_time = omp_get_wtime();
	printf("res: %lu, time: %2.2f seconds\n", res, end_time - start_time);

    // cleanup
error_b:
	free_2d_array(b, n);
error_a:
	free_2d_array(a, n);

	return status;
}