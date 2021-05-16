#include <stdio.h>

#define SIZE 1024

int main(int argc, char** argv) {
	printf("%s\n", argv[0]);  // avoid unused variable error
	int a[SIZE];
	int b[SIZE];

	for(int i = 0; i < SIZE; ++i) {
		a[i] = argc;
	}

	for(int i = 0; i < SIZE; ++i) {
		b[i] = a[i];
	}

	for(int i = 4; i < SIZE; ++i) {
		a[i - 4] = a[i];
	}

	for(int i = 1; i < SIZE - 1; ++i) {
		a[i] = a[i % argc];
	}

	// output data to prevent compiler from removing any code
	for(int i = 0; i < SIZE; ++i) {
		printf("%d ", a[i]);
	}
    printf("\n");
	for(int i = 0; i < SIZE; ++i) {
        printf("%d ", b[i]);
	}
	printf("\n");

	return 0;
}
