#include "main.h"

int main(void) {
	// set up output
	FILE* output_file = fopen("./data/analytically_stable.dat", "w+");

	// initialize particles and allocate corresponding memory
	int particle_number = 3;
	int iter = 10000000;
	long double dt = .00001L;
	long double r = (long double) 1/sqrt(3);
	state* initial_conditions = (state*) malloc((size_t) particle_number * sizeof(state));

	// determine initial conditions
	analytically_stable(initial_conditions, particle_number, r);

	// simulate mass points
	for(int i = 0; i < iter; i++) {
		evolve_state(initial_conditions, particle_number, dt);
		print_to_file(initial_conditions, output_file, particle_number);
		if(i % 200000 == 0) printf("%3.2f\n", (double) 100 * i/iter);
	}

	return EXIT_SUCCESS;
}
