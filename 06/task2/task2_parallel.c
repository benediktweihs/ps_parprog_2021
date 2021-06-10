//
// Created by weihs on 29/04/2021.
//

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define max(a,b) (((a)>(b))?(a):(b))

int queenAllowed(int* occupiedColumns, int currentLine, int currentColumn) {
    for(int i = 0; i < currentLine; i++) {
        if(currentColumn == occupiedColumns[i]) return 0;
        if(currentColumn - occupiedColumns[i] == currentLine - i) return 0;
        if(currentColumn - occupiedColumns[i] == i - currentLine) return 0;
    }
    return 1;
}


void resetIfColumnIsDone(int* occupiedColumns, int* currentLine, int* currentColumn, int n) {
    while(*currentColumn == n) {
        (*currentLine)--;
        *currentColumn = occupiedColumns[*currentLine] + 1;
        occupiedColumns[*currentLine] = -1;
    }
}


int main(int argc, char* argv[]) {
    if(argc != 2) {
        printf("Usage: name <length>\n");
        exit(EXIT_FAILURE);
    }

	// allocate basic variables
    int n = (int) strtol((const char*) argv[1], NULL, 10);
    int res = 0;
    int flag = n % 2;
	int err = 0;
    int numThreads = 0;
	int middleSol = 0;
	int todoColumns = n / 2 + flag;

	// get total number of threads:
    #pragma omp parallel
    #pragma omp single
    numThreads = omp_get_num_threads();
	if(numThreads > n || n < 8) {
		printf("OMP_NUM_THREADS > n");
		printf("n must be bigger than 7");
		exit(EXIT_FAILURE);
	}

    int* partialSolutions = (int*) calloc((size_t) numThreads, sizeof(int));
	double startTime = omp_get_wtime();
    #pragma omp parallel shared(res, flag, err, partialSolutions, middleSol, todoColumns)
    {
        int solutions = 0;
        int currentLine = 0;
		int threadIndex = omp_get_thread_num();
		int currentColumn = todoColumns * threadIndex / numThreads;
		int lastColumn = todoColumns * (threadIndex + 1) / numThreads;

		if(threadIndex == numThreads - 1){
			lastColumn = todoColumns;
		}

        int* occupiedColumns = (int*) calloc((size_t) n, sizeof(int));
        for(int i = 0; i < n; i++) occupiedColumns[i] = -1;
        if(!occupiedColumns) err = 1;

		// proceed iff all threads could allocate memory
        #pragma omp barrier

		if(!err) {
	        while(1) {

                // every line contains a valid queen
                if(currentLine == n) {
                    solutions++;
                    currentLine--;
                    currentColumn = occupiedColumns[currentLine] + 1;
                    occupiedColumns[currentLine] = -1;
                    resetIfColumnIsDone(occupiedColumns, &currentLine, &currentColumn, n);
                    continue;
                }

                // if no queen is allowed in line currentLine then decrease line until there are allowed squares
                resetIfColumnIsDone(occupiedColumns, &currentLine, &currentColumn, n);

                if(currentColumn == lastColumn &&
				   currentLine == 0 &&
				   !flag) {
                    #pragma omp critical
                    partialSolutions[threadIndex] = solutions;
                    break;
                }

				if(currentColumn == lastColumn &&
				   currentLine == 0 &&
				   flag &&
				   threadIndex != numThreads - 1) {
                    partialSolutions[threadIndex] = solutions;
                    break;
				}

                if(currentColumn == lastColumn - 1 &&
				   currentLine == 0 &&
				   threadIndex == numThreads - 1 &&
				   flag) {
                    partialSolutions[threadIndex] = solutions;
                    solutions = 0;
                }

                if(currentColumn == lastColumn &&
				   currentLine == 0 &&
				   threadIndex == numThreads - 1 &&
				   flag) {
					middleSol = solutions;
					break;
				}

                // found a valid square to put a queen in line currentLine
                if(currentColumn < n && queenAllowed(occupiedColumns, currentLine, currentColumn)) {
                    // goto next line and mark square as occupied
                    occupiedColumns[currentLine] = currentColumn;
                    currentLine++;
                    currentColumn = 0;
                    continue;
                }

                // queen at (currentLine, currentColumn) is not allowed:
                if(currentColumn < n) {
                    currentColumn++;
                    continue;
                }

                break;  // redundant
		    }
        }
        free(occupiedColumns);
	}
    if(err){
		free(partialSolutions);
		return EXIT_FAILURE;
	}

	for (int i = 0; i < numThreads; i++) res += 2*partialSolutions[i];
	res += middleSol;
	free(partialSolutions);
    double endTime = omp_get_wtime();

    printf("time = %.5f; result = %d\n", endTime - startTime, res);
    return EXIT_SUCCESS;
}
