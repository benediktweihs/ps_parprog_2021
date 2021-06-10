//
// Created by benedikt on 22.03.21.
// each thread performs a fraction of ITER/numThreads of the total Monte-Carlo method.
#include <pthread.h>
#include "common.h"

#define ITER 50000000

typedef struct passData {
    int iterations;
	int result;
} passData;

void* exec(void* args){
	passData* parameters = (passData*) args;
	parameters->result = calcIter(parameters->iterations);
	return NULL;
}

int main(int argc, char* argv[]){
	int numThreads;
	if(argc!=2) exit(EXIT_FAILURE);
	numThreads = atoi(argv[1]);


    pthread_t iterThread[numThreads];
    passData data[numThreads];
    for(int i = 0; i < numThreads; i++){
		(data + i)->iterations = ITER/numThreads;
        (data + i)->result = 0;
	}

    for(int i = 0; i < numThreads; i++) {
        pthread_create(&iterThread[i], NULL, exec, (void*)(data + i));
    }

    for(int i = 0; i < numThreads; i++) if(pthread_join(*(iterThread + i), NULL)) goto ERR;

	int hitsInQuadrant = 0;
    for(int i = 0; i < numThreads; i++) hitsInQuadrant += (data + i)->result;

	double pi = 4*((double) hitsInQuadrant/(double)ITER);
    printf("pi \\approx %f\n", pi);
	return EXIT_SUCCESS;

ERR:
    printf("Failure\n");
    exit(EXIT_FAILURE);

}