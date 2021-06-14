#include "vector_operations.h"

long double distance_of_center(state* state, int index) {
	long double ret = 0;
	ret += state[index].x.x * state[index].x.x;
	ret += state[index].x.y * state[index].x.y;
	ret += state[index].x.z * state[index].x.z;
	return sqrt(ret);
}

/**
 * print out the state of 10 paritcles at most
 * state will always refer to a point in phase
 * space and mass of the particle 
 */
void output_state(state* state, int particle_number) {
  	int end_iteration = particle_number > 10 ? 10 : particle_number;

	for(int i = 0; i < end_iteration; i++) {
		printf("mass = %3.1Lf:\n\t", (state + i)->mass);
		printf("velocity = (%4.3Lf,%4.3Lf,%4.3Lf)^T\t", ((state + i)->v).x, ((state + i)->v).y, ((state + i)->v).z);
		printf("position = (%4.3Lf,%4.3Lf,%4.3Lf)^T\n", ((state + i)->x).x, ((state + i)->x).y, ((state + i)->x).z);
	}
}

/**
 * print states of all particles (for a given time)
 * to a file
 */
void print_to_file(state* state, FILE* file, int particle_number) {
	for(int i = 0; i < particle_number; i++) {
		fprintf(file, "%Lf %Lf %Lf\n", ((state + i)->x).x, ((state + i)->x).y, ((state + i)->x).z);
	}
	fprintf(file, "\n\n");
}

/**
 * these three masses will rotate around their common
 * com (center of mass) in a circle
 */
void analytically_stable(state* state, int particle_number, long double r) {
	if(particle_number != 3) return;
	((state + 0)->x).x = r;
	((state + 0)->x).y = 0.L;
	((state + 0)->v).x = 0.L;
	((state + 0)->v).y = 1.L;


	((state + 1)->x).x = (long double) -.5*r;
	((state + 1)->x).y = (long double) .5*r*sqrt(3);
	((state + 1)->v).x = (long double) -.5*sqrt(3);
	((state + 1)->v).y = -.5L;

	
	((state + 2)->x).x = (long double) -.5*r;
	((state + 2)->x).y = (long double) -.5*r*sqrt(3);
	((state + 2)->v).x = (long double) .5*sqrt(3);
	((state + 2)->v).y = -.5L;

	for(int i = 0; i < particle_number; i++) {
		(state + i)->mass = 1.L;
		((state + i)->v).z = 0.L;
		((state + i)->x).z = 0.L;
	}
}

void random_initial_positions(state* state, int particle_number) {
	// z in [0, 100)
	long double limit = 100.L;
	long double rand_pos = 0;

	// seed
	srand(time(0));

	for(int i = 0; i < particle_number; i++) {
		(state + i)->mass = 1.L;

		rand_pos = (long double)rand() / (long double)RAND_MAX;
		((state + i)->x).x = rand_pos * limit;
		rand_pos = (long double)rand() / (long double)RAND_MAX;
		((state + i)->x).y = rand_pos * limit;
		rand_pos = (long double)rand() / (long double)RAND_MAX;
		((state + i)->x).z = rand_pos * limit;

		rand_pos = (long double)rand() / (long double)RAND_MAX;
		((state + i)->v).x = rand_pos * limit;
		rand_pos = (long double)rand() / (long double)RAND_MAX;
		((state + i)->v).y = rand_pos * limit;
		rand_pos = (long double)rand() / (long double)RAND_MAX;
		((state + i)->v).z = rand_pos * limit;
	}
}
