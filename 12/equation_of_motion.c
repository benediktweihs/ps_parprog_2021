//
// Created by weihs on 10/06/2021.
//

#include "equation_of_motion.h"

/**
 * returns norm of x2 - x1
 */
long double euclidian_distance(column x1, column x2) {
	long double ret = 0;
	ret += (x2.x - x1.x) * (x2.x - x1.x);
	ret += (x2.y - x1.y) * (x2.y - x1.y);
	ret += (x2.z - x1.z) * (x2.z - x1.z);
	return sqrt(ret);
}

/**
 * gets state of two particles and calculated
 * the gravitational force between the two bodies
 */
column force(state state1, state state2) {
	long double prefactor = state1.mass * state2.mass / pow(euclidian_distance(state1.x, state2.x), 3);
	column ret;
	ret.x = prefactor * (state2.x.x - state1.x.x);
	ret.y = prefactor * (state2.x.y - state1.x.y);
	ret.z = prefactor * (state2.x.z - state1.x.z);
	return ret;
}

/**
 * array of all positions and velocities of all particles
 * is passed to this function 
 */
column* compute_forces(state* state, int particle_number) {
	column force_per_particle = {0.L, 0.L, 0.L};
	column* forces;
	forces = (column*) malloc((size_t) particle_number * sizeof(column));

	for(int i = 0; i < particle_number; i++) {
		for(int j = 0; j < particle_number; j++) {
			if(i == j) continue;
			force_per_particle = force(state[i], state[j]);
			forces[i].x += force_per_particle.x;
			forces[i].y += force_per_particle.y;
			forces[i].z += force_per_particle.z;
		}
	}

	return forces;
}

/**
 * dx = v dt -> x += v dt
 * dv = a dt = F/m dt -> v += F/m dt
 */
void evolve_state(state* state, int particle_number, long double dt) {
	column* forces = compute_forces(state, particle_number);
	
	for(int i = 0; i < particle_number; i++) {
		state[i].x.x += dt * state[i].v.x;
		state[i].x.y += dt * state[i].v.y;
		state[i].x.z += dt * state[i].v.z;
		//printf("%Lf\n", forces[i].x);
		//printf("%Lf\n", forces[i].y);
		//printf("%Lf\n", forces[i].z);
		state[i].v.x += dt * forces[i].x / state[i].mass;
		state[i].v.y += dt * forces[i].y / state[i].mass;
		state[i].v.z += dt * forces[i].z / state[i].mass;
		//printf("\n");
	}
}
