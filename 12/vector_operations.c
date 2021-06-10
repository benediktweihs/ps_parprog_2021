#include "vector_operations.h"

void output_state(state* state, int particle_number) {
    // print out the state of 10 paritcles at most
  	int end_iteration = particle_number > 10 ? 10 : particle_number;

	for(int i = 0; i < end_iteration; i++) {
		printf("mass = %3.1f:\n\t", (state + i)->mass);
		printf("velocity = (%4.3Lf,%4.3Lf,%4.3Lf)^T\t", ((state + i)->v).x, ((state + i)->v).y, ((state + i)->v).z);
		printf("position = (%4.3Lf,%4.3Lf,%4.3Lf)^T\n", ((state + i)->x).x, ((state + i)->x).y, ((state + i)->x).z);
	}
}

void analytically_stable(state* state, int particle_number, long double r) {
	if(particle_number != 3) return;
	((state + 0)->x).x = r;
	((state + 0)->x).y = 0;
	((state + 0)->v).x = 0;
	((state + 0)->v).y = 1;


	((state + 1)->x).x = -.5*r;
	((state + 1)->x).y = .5*r*sqrt(3);
	((state + 1)->v).x = -.5*sqrt(3);
	((state + 1)->v).y = -5;

	
	((state + 2)->x).x = -.5*r;
	((state + 2)->x).y = .5*r*sqrt(3);
	((state + 2)->v).x = .5*sqrt(3);
	((state + 2)->v).y = -5;

	for(int i = 0; i < particle_number; i++) {
		(state + i)->mass = 1;
		((state + i)->v).z = 1;
		((state + i)->x).z = 1;
	}
}