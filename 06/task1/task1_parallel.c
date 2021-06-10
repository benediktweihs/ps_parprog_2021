//
// Created by weihs on 28/04/2021.
//

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

void exclusive_prefix(const int32_t* arr, int32_t* ret_outer, long length) {
    int32_t* ret = ret_outer + 1;

	int numThreads;
    #pragma omp parallel
    #pragma omp single
    numThreads = omp_get_num_threads();
	int32_t* tempRes =  (int32_t*) calloc((size_t) numThreads, (size_t) sizeof(int32_t));

	// simplify the partitioning process
	if(numThreads >= length) {
        for(int i = 1; i <= length; i++) {
            ret_outer[i] = ret_outer[i - 1] + arr[i - 1];
        }
		return;
	}

	# pragma omp parallel shared(ret, arr, tempRes)
    {
		long start, end, i;
	    int outer_index = omp_get_thread_num();
	    start = outer_index * length / numThreads;
	    end = (outer_index + 1) * length / numThreads;
		ret[start] = arr[start];

		// makes sure that length % numThreads == 0 can be false
	    if(outer_index == numThreads - 1) {
	    	end = length;
	    }

	    for(i = start + 1; i < end; i++) {
            ret[i] = ret[i - 1] + arr[i];
        }

        #pragma omp critical
	    tempRes[outer_index] = ret[end - 1];

        #pragma omp barrier

        int32_t toAdd = 0;
        for(i = 0; i < outer_index; i++) toAdd += tempRes[i];

		// replacing "ret[i] = ret[i] + toAdd;" with "ret[i] = ret[i] + toAdd - arr[i];" increases
		// execution time by half a second for length=1e9
        for(i = start; i < end; i++) {
            ret[i] = ret[i] + toAdd;
        }
	}
}

int main(int argc, char* argv[]) {
    if(argc != 2){
        printf("Usage: name <length>\n");
        exit(EXIT_FAILURE);
    }

	// basic separation of workload:
	// [1,2,3,4] & 2 threads
	// [1,2] & [3,4]
	// [1,3] & [3,7]
	// -> combine:
	// thread 0: add 0 [1,3]
	// thread 1: add 3 [6,10]
	// concat: [1,3,6,10]
	// result - initial array = [0,1,3,6]

    // initialize array
    long length = strtol((const char*) argv[1], NULL, 10);
    int32_t* arr = (int32_t*)calloc((size_t) length, (size_t) sizeof(int32_t));
    if (!arr) goto cleanup_arr;
    int32_t* ret = (int32_t*)calloc((size_t) length + 1, (size_t) sizeof(int32_t));
    if (!ret) goto cleanup_ret;
	for(int i = 0; i < length; i++) arr[i] = 1;


    double startTime = omp_get_wtime();
    exclusive_prefix(arr, ret, length);
    double endTime = omp_get_wtime();
	printf("Wall Time: %.5f seconds\nb[-1] = %d\n", endTime - startTime, ret[length-1]);

	free(ret);
	free(arr);
    return EXIT_SUCCESS;

cleanup_ret:
    free(ret);
cleanup_arr:
    free(arr);
    return EXIT_FAILURE;
}