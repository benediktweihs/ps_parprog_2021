//
// Created by weihs on 11/04/2021.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

int main(int argc, char* argv[]){
    if(argc != 2) exit(EXIT_FAILURE);
    int num_threads = omp_get_num_threads();
    int iter = atoi(argv[1]) / num_threads;
    int totalIter = 0;

	unsigned int seed = time(NULL);
    double startTime = omp_get_wtime();

    #pragma omp parallel
	{
        double randX, randY;
        #pragma omp for reduction(+ : totalIter)
        for(int i = 0; i < iter; i++) {
        	randX = (double) rand_r(&seed) / RAND_MAX;
        	randY = (double) rand_r(&seed) / RAND_MAX;
        	totalIter += (int) (randX * randX + randY * randY); // hope that randX!=1.!=randY
        }
    }

    double endTime = omp_get_wtime();

    double pi = 4*((double) (num_threads*iter-totalIter)/(double) (num_threads*iter));

    //printf("pi \\approx %f\n", pi);
    printf("Time = %2.4f at pi = %2.6f\n", endTime-startTime, pi);
}
