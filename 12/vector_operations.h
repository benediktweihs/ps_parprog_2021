#ifndef VECTOR_OPS_H
#define VECTOR_OPS_H
#include "main.h"

void output_state(state*, int);
void analytically_stable(state*, int, long double);
long double distance_of_center(state*, int);
void print_to_file(state*, FILE*, int);
void random_initial_positions(state*, int);

#endif
