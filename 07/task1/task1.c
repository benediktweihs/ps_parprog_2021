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

#define BUFSIZE 200
#define REPETITIONS 1000000
// the count of events for YYXX=1FC7 is the same for both compiler flags:
// 231.936.208.991 r1FC7:u <- parallel
// 529,280,010,583 r1FC7:u <- sequential

int main(void){
	int sizes_len = 128;
	int step_size = 16;
	int max_size = sizes_len * step_size;
	float* a = (float*) malloc((size_t) max_size * sizeof(float));
    float* b = (float*) malloc((size_t) max_size * sizeof(float));
    float* c = (float*) malloc((size_t) max_size * sizeof(float));
	double* times = (double*) malloc((size_t) sizes_len * sizeof(double));
    int* sizes = (int*) malloc((size_t) sizes_len * sizeof(int));

	for(int size_index = 0; size_index < sizes_len; size_index++) {
		sizes[size_index] = step_size * (size_index + 1);

		for(int i = 0; i < sizes[size_index]; i++) {
			a[i] = 1.;
			b[i] = 1.;
			c[i] = 1.;
		}

		// perform sequential calculation and take time measurement
		double startTime = omp_get_wtime();

		for(int run = 0; run < REPETITIONS; ++run) {
			for(int i = 0; i < sizes[size_index]; i++) {
				a[i] += b[i] * c[i];
			}
            assert(a[0] - ((float) 2 + run) < 1e-1);  // check if result is right
		}

		double endTime = omp_get_wtime();

		times[size_index] = endTime - startTime;
		printf("%.2f\n", times[size_index]);
	}

	// get generic info for time
    time_t rawtime;
    struct tm * timeinfo;
    time(&rawtime);
    timeinfo = localtime (&rawtime);
	char filename[BUFSIZE], buffer[BUFSIZE];
    strftime(buffer, sizeof(buffer),"%d_%m_%Y-%H_%M_%S", timeinfo);

	// create unique file and folder
    mkdir("./data", 0777);
	strcpy(filename, "./data/results_sequential_");
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
