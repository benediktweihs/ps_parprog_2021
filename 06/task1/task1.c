//
// Created by weihs on 28/04/2021.
//

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

void exclusive_prefix(const int32_t* arr, int32_t* ret, long length) {
    for (int i = 1; i < length; i++) {
        ret[i] = ret[i - 1] + arr[i - 1];
    }
}

int main(int argc, char* argv[]) {
    if(argc != 2){
		printf("Usage: name <length>\n");
		exit(EXIT_FAILURE);
	}

	// initialize array
	long length = strtol((const char*) argv[1], NULL, 10);
    int32_t* arr = (int32_t*)calloc((size_t) length, (size_t) sizeof(int32_t));
    if (!arr) goto cleanup_arr;
    int32_t* ret = (int32_t*)calloc((size_t) length, (size_t) sizeof(int32_t));
    if (!ret) goto cleanup_ret;
	for(int i = 0; i < length; i++) arr[i] = 1;

    double startTime = omp_get_wtime();
    exclusive_prefix(arr, ret, length);
    double endTime = omp_get_wtime();

	printf("Wall Time: %.5f seconds\nb[-1] = %d\n", endTime - startTime, ret[length-1]);
	return EXIT_SUCCESS;

cleanup_ret:
	free(ret);
cleanup_arr:
	free(arr);
	return EXIT_FAILURE;
}