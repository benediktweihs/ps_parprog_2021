#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <omp.h>
#include <time.h>


void copy_range(int32_t* arr1, int32_t* arr2, long start, long end);
void print_arr(int32_t* arr, long length);
double merge_sort (int32_t* arr, long length);
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
        arr[index] = (int32_t) rand();// % 1000;  // easier to see if lcc2_results is right
    }

    print_arr(arr, length);
    double exec_time = merge_sort(arr, length);
    printf("time: %2.2f seconds\n", exec_time);
    print_arr(arr, length);
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


void copy_range(int32_t* arr1, int32_t* arr2, long start, long end){
    for (long index = start; index < end; index++){
        arr2[index] = arr1[index];
    }
}


double merge_sort (int32_t* arr, long length) {
    int32_t* help_left = calloc(length, sizeof(int32_t));
    if(!help_left) goto clean_left;
    int32_t* help_right = calloc(length, sizeof(int32_t));
    if(!help_right) goto clean_right;
    
    long middle, end, left, right;

    // start time measurement
	double start_time = omp_get_wtime();
    for (long size = 1; size < length - 1; size*=2){
        for (long start = 0; start < length - size; start += 2*size){
            // shuffle pairs together in order to get order
            middle = start + size;
            end = minimum(start + 2*size, length);

            // write pairs to separate arrays
            left = 0; right = 0;
            copy_range(arr, help_left, start, middle);
            copy_range(arr, help_right, middle, end);
            
            while(start + left + right < end){
                //printf("%ld %ld %ld %ld %ld \n\n", start, middle, end, left, right);
                if((middle + right == end ||
                help_left[left + start] < help_right[right + middle]) &&
                !(start + left == middle)){
                    arr[start + left + right] = help_left[left + start];
                    left++;
                }
                else{
                    arr[start + left + right] = help_right[middle + right];
                    right++;
                }
            }
        }
    }

    // stop time measurement
	double end_time = omp_get_wtime();

    free(help_left);
    free(help_right);
    return end_time - start_time;

clean_right:
    free(help_right);
clean_left:
    free(help_left);
    free(arr);
    exit(EXIT_FAILURE);
}
