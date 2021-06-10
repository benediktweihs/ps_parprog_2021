//
// Created by benedikt on 22.03.21.
//
#include "common.h"

int main(int argc, char* argv[]){
	if(argc != 2) exit(EXIT_FAILURE);
	int iter = atoi(argv[1]);
	double pi = calcPi(iter);
	printf("pi \\approx %f\n", pi);
}
