//
// Created by weihs on 26/04/2021.
//

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int dellanoy(int matrixSize, int horizontal, int vertical);

int main(int argc, char* argv[]){

    // get user input
    if(argc != 2) {
        printf("Usage: %s number\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    int matrixSize = atoi(argv[1]);

    double startTime = omp_get_wtime();
    int paths = 0;
    paths = dellanoy(matrixSize, 0, 0);
    double endTime = omp_get_wtime();

    printf("result = %d, time = %f\n", paths, endTime - startTime);
    return EXIT_SUCCESS;
}

// https://www.geeksforgeeks.org/delannoy-number/
int dellanoy(int matrixSize, int horizontal, int vertical) {
    int dp[matrixSize + 1][matrixSize + 1];

    // Base cases
    for (int index1 = 0; index1 <= matrixSize; index1++)
        dp[index1][0] = 1;
    for (int index2 = 0; index2 <= matrixSize; index2++)
        dp[0][index2] = 1;
    # pragma omp parallel shared(dp)
    # pragma omp single
        for(int index1 = 1; index1 <= matrixSize; index1++) {
            for(int index2 = 1; index2 <= matrixSize; index2++) {
                #pragma omp task firstprivate(index1, index2) shared(dp)
                    dp[index1][index2] = dp[index1 - 1][index2] + dp[index1 - 1][index2 - 1] + dp[index1][index2 - 1];
            }
		}

	return dp[matrixSize][matrixSize];
}