#include "main.h"

int main(int argc, char* argv[]) {
	long double dt;

    if(argc != 2) {
		printf("Usage: ./program_name <timestep>\n");
		exit(EXIT_FAILURE);
	}

	// read input and convert to number
	sscanf(argv[1], "%Lf", &dt);
	printf("Timestep = %Lf\n", dt);

	// set up output
	FILE* output_file = fopen("./data/positions.dat", "w+");

	// initialize particles and allocate corresponding memory
	int particle_number = 5000;
	long double total_time_simulated = 100.L;
	int iter = (int) total_time_simulated / dt;
	state* initial_conditions = (state*) malloc((size_t) particle_number * sizeof(state));

	// determine initial conditions
	random_initial_positions(initial_conditions, particle_number);

	// simulate mass points
	for(int i = 0; i < iter; i++) {
		//printf("%Lf\n", distance_of_center(initial_conditions, 0) / r);
		evolve_state_parallel(initial_conditions, particle_number, dt);
		print_to_file(initial_conditions, output_file, particle_number);
		printf("%3.2f\n", (double) i/iter);
	}

	return EXIT_SUCCESS;
}