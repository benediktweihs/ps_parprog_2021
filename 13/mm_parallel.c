#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

// allows the user to specify the problem size at compile time
#ifndef N
        #define N 100
#endif

#define IND(x, y) (y * N + x)


void printMatrix(double* m) {

        for(int i=0; i<N; i++) {
                for(int j=0; j<N; j++) {
                        printf("%.1f ", m[IND(i,j)]);
                }
                printf("\n");
        }
        printf("\n");
}


int main() {
    // This benchmark is computing the symmetric rank k operation
    //              B = A * A^T + B
    // where A is a upper triangular and unit (1 along the diagonal)

    double* A = malloc(sizeof(double) * N * N);
    double* B = malloc(sizeof(double) * N * N);
    double* C = malloc(sizeof(double) * N * N);

    // initialize matrices
    for (int i=0; i<N; i++) {
        for (int j=0; j<N; j++) {
            A[IND(i,j)] = (i==j)?1:0;
            B[IND(j,i)] = j*i;
            C[IND(i,j)] = 0;
        }
    }

    //printf("A:\n"); printMatrix(A, N);
    //printf("B:\n"); printMatrix(B, N);
    // get number of threads
    int numThreads = 5;

    #pragma omp parallel
    #pragma omp single
    numThreads = omp_get_num_threads();
    
    printf("%d\n", numThreads);
    int devition = N / numThreads;
    printf("hallo\n");
    double timeStart = omp_get_wtime();

    printf("hallo\n");
    // this is a start but it is not ideal
    // as every thread has to access B at probably the same time
    #pragma omp parallel
    {
        int index = omp_get_thread_num();
        int end = index == numThreads - 1 ? N : (index + 1) * devition;
        printf("%d\n", end);
        printf("%d\n", index);
        // private array to store temporary result
        //double* arr_private = (double*) malloc((size_t) devition * N * sizeof(double));
        /*int index = omp_get_thread_num();
        int start = index * devition;

        for(int i = start; i < end; i++) {
            for(int j = 0; j < N; j++){
                for(int k = 0; k < N; k++) {
                    C[IND(i,j)] += A[IND(i,k)] * B[IND(j,k)];
                }
            }
        }*/
    }

    double timeEnd = omp_get_wtime();
    //printf("C:\n"); printMatrix(C, N);

    printf("time: %f\n", timeEnd-timeStart);

    free(A);
    free(B);
    free(C);

    return EXIT_SUCCESS;
}
