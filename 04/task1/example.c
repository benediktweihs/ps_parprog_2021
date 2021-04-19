//
// Created by benedikt on 17.04.21.
//

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <limits.h>

#define ITER 100000000

int main(void){
    printf("Incrementing a number:\n");
    int number = 0;
	int one = 1;

    double startTime = omp_get_wtime();

    // it seems as if startTime-endTime does not depend on ITER without #pragma omp critical
	// maybe due to some compiler optimization
    #pragma omp for
    for(int i = 0; i < ITER; i++) {
        #pragma omp critical
		number = number + one;
	}

	printf("%d\n", number);
    double endTime = omp_get_wtime();
	printf("Time = %9.9f\n", endTime - startTime);

	return EXIT_SUCCESS;
}
// using 4 threads *and* two cpus (with 8 threads each) is overhead but cooling is simpler! =>
// performance is similar
// https://pages.tacc.utexas.edu/~eijkhout/pcse/html/omp-affinity.html

// sockets: 2.940524742

// cores: 2.940753859
