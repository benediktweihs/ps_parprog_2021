//
// Created by benedikt on 22.03.21.
//

#include <stdlib.h>
#include <stdio.h>
//int argc, char* argv[]
int main(int argc, char* argv[]){
	size_t n = 10;

	if(argc > 2) exit(EXIT_FAILURE);
	if(argc == 2){
		n = (size_t) atoi(argv[1]);
	}
	printf("%ld\n", n);

	int32_t** a = (int32_t**) calloc(n, sizeof(int32_t*));
	int32_t** b = (int32_t**) calloc(n, sizeof(int32_t*));
	int32_t** c = (int32_t**) calloc(n, sizeof(int32_t*));
	for(size_t i = 0; i < n; i++){
        a[i] = (int32_t*) calloc((size_t) n, sizeof(int32_t));
        b[i] = (int32_t*) calloc((size_t) n, sizeof(int32_t));
        c[i] = (int32_t*) calloc((size_t) n, sizeof(int32_t));
	}

	// from readme:
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j) {
            c[i][j] = a[i][j] * b[i][j];
        }
    }

    for(size_t i = 0; i < n; i++){
        free(a[i]);
        free(b[i]);
        free(c[i]);
    }
    free(a);
    free(b);
    free(c);
}
