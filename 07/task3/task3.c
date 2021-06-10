//
// Created by weihs on 05/05/2021.
//

#include <assert.h>
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
#include <xmmintrin.h>

#define BUFSIZE 200
#define REPETITIONS 1000000
// the lcc2_results are still correct (assert statement after inner for loop ensures that)
// performance is best
// 231.936.208.991 r1FC7:u <- parallel


int main(void){
	int sizes_len = 128;
	int step_size = 16;
	int max_size = sizes_len * step_size;
	float* a = (float*) calloc((size_t) max_size, sizeof(float));
    float* b = (float*) calloc((size_t) max_size, sizeof(float));
    float* c = (float*) calloc((size_t) max_size, sizeof(float));
	double* times = (double*) malloc((size_t) sizes_len * sizeof(double));
    int* sizes = (int*) malloc((size_t) sizes_len * sizeof(int));

	for(int size_index = 0; size_index < sizes_len; size_index++) {
		sizes[size_index] = step_size * (size_index + 1);

        for(int i = 0; i < sizes[size_index]; i++) {
            a[i] = 1.;
            b[i] = 1.;
            c[i] = 1.;
        }

        __m128 a_comprised = _mm_load_ps(a);
        __m128 b_comprised = _mm_load_ps(b);
        __m128 c_comprised = _mm_load_ps(c);

		// perform sequential calculation and take time measurement
		double startTime = omp_get_wtime();
        for(int run = 0; run < REPETITIONS; ++run)
			a_comprised = _mm_add_ps(a_comprised, _mm_mul_ps(b_comprised, c_comprised));
		_mm_store_ps(a, a_comprised);
		assert(a[0] - (2. + REPETITIONS - 1.) < 1e-1);  // check if result is right
		double endTime = omp_get_wtime();

		times[size_index] = endTime - startTime;
		printf("%.5f\n", times[size_index]);
	}

	// get generic info for time
    time_t rawtime;
    struct tm * timeinfo;
    time ( &rawtime );
    timeinfo = localtime ( &rawtime );
	char filename[BUFSIZE], buffer[BUFSIZE];
    strftime(buffer, sizeof(buffer),"%d_%m_%Y-%H_%M_%S", timeinfo);

	// create unique file and folder
    mkdir("./data", 0777);
	strcpy(filename, "./data/results_sequential_");  // was manually changed with compiler flag
    strcat(filename, buffer);
    strcat(filename, ".txt");
    printf("%s\n", filename);
	FILE* results = fopen(filename, (const char *) "w");
    fprintf(results, "times\tlen(a,b,c)\n");

	for(int size_index = 0; size_index < sizes_len; size_index++) {
        fprintf(results, "%5.5f\t%d\n", times[size_index], sizes[size_index]);
	}

    fclose(results);
	free(a);
	free(b);

	free(c);
	free(times);
	free(sizes);
	return EXIT_SUCCESS;
}
