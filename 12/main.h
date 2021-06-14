#ifndef SHEET04_WEIHS_TAR_GZ_MAIN_H
#define SHEET04_WEIHS_TAR_GZ_MAIN_H
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <omp.h>

typedef struct column {
    long double x;
    long double y;
    long double z;
} column;

// point in phase-space
typedef struct state {
    column x;
    column v;
    long double mass;
} state;

#include "equation_of_motion.h"
#include "vector_operations.h"
#endif
