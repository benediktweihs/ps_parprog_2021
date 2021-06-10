#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

// time 1 thread: 27.04 seconds
// time 8 threads: 11.33 seconds (dont run with length%num_threads!=0)

void copy_range(int32_t* arr1, int32_t* arr2, long length);
void merge_sort_parallel(int32_t* arr, long length);
void print_arr(int32_t* arr, long length);
void merge_sort(int32_t* arr, long length);
void merge(int32_t* arr1, int32_t* arr2, long length1, long length2);
int32_t minimum(int32_t a, int32_t b);


int main(int argc, char* argv[]) {
    // handle input
    if(argc != 2) {
        printf("Usage: %s number\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // instantiate array
    long length = atol(argv[1]);
    int32_t* arr = malloc(sizeof(int32_t) * length);
    if(!arr) goto cleanup;

    // fill array
    srand(time(NULL));
    for (long index = 0; index < length; index++){
        arr[index] = (int32_t) rand();  // easier to see if lcc2_results is right
    }
    printf("sorting:\n");

	// print array, measure time of sorting array, print array again
    //print_arr(arr, length);
    double start_time = omp_get_wtime();
	merge_sort_parallel(arr, length);
    double end_time = omp_get_wtime();
    printf("time: %2.2f seconds\n", end_time - start_time);
    //print_arr(arr, length);

    free(arr);
    return EXIT_SUCCESS;
    cleanup:
    free(arr);
    return EXIT_FAILURE;
}


int32_t minimum(int32_t a, int32_t b) {
    /// return minimum of two integers
    return (a < b) ? a : b;
}


void print_arr(int32_t* arr, long length) {
    for (long index = 0; index < length; index++){
        printf("%d \n", arr[index]);
    }
    printf("\n\n");
}


void copy_range(int32_t* arr1, int32_t* arr2, long length){
    for (long index = 0; index < length; index++){
        arr1[index] = arr2[index];
    }
}

void merge(int32_t* arr1, int32_t* arr2, long length1, long length2){
	long tot_length = length1 + length2;
    int32_t* help = malloc(sizeof(int32_t) * tot_length);
    if(!help) goto clean;

	long i = 0;
	long j = 0;

	// shuffle togehter arrays
    while(i + j < tot_length) {
    	if(j >= length2) {
    		help[i + j] = arr1[i];
    		i++;
    		continue;
    	}
    	if(i >= length1) {
    		help[i + j] = arr2[j];
    		j++;
    		continue;
    	}
    	if(arr1[i] > arr2[j]) {
    		help[i + j] = arr2[j];
    		j++;
    		continue;
    	}
    	help[i + j] = arr1[i];
    	i++;
    }

	copy_range(arr1, help, tot_length);
	free(help);
	return;

clean:
	free(help);
}

void merge_sort_parallel(int32_t* arr, long length) {
	long max;

    #pragma omp parallel
	{
		int max_len = omp_get_num_threads();
		max = max_len;
	    int k = omp_get_thread_num();
        long private_length = length / max_len;
        int32_t* private_arr = malloc(sizeof(int32_t) * private_length);
		copy_range(private_arr, &arr[k * private_length], private_length);
		merge_sort(private_arr, private_length);
        #pragma omp critical
		copy_range(&arr[k * private_length], private_arr, private_length);
    }

    do {
        long len = length / max;
		for(int ind = 0; ind < max - 1; ind += 2) {
			merge(&arr[ind * len], &arr[(ind + 1) * len], len, len);
		}
		max /= 2;
	}while(max > 1);
}

void merge_sort (int32_t* arr, long length) {
	if (length == 2) {
        if (arr[0] > arr[1]){
			double temp = arr[1];
			arr[1] = arr[0];
			arr[0] = temp;
			return;
		}
	}

	if (length == 1) return;

    long middle = length / 2;
	merge_sort(arr, middle);
	merge_sort(arr + middle, length - middle);

    merge(arr, arr + middle, middle, length - middle);
    return;
}


