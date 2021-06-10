#include "main.h"

int main(void) {
	// initialize particles
	int particle_number = 3;
	long double r = (long double) 1/sqrt(3);
	state* initial_conditions = (state*) malloc((size_t) particle_number * sizeof(state));

	// determine initial conditions
	analytically_stable(initial_conditions, particle_number, r);

	// print out initial conditions
	output_state(initial_conditions, particle_number);	

	return EXIT_SUCCESS;
}
