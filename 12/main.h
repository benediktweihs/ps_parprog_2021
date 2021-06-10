//
// Created by weihs on 10/06/2021.
//

#ifndef SHEET04_WEIHS_TAR_GZ_MAIN_H
#define SHEET04_WEIHS_TAR_GZ_MAIN_H
#include <stdlib.h>
#include <stdio.h>
#include "equation_of_motion.h"

typedef struct position {
    long double x;
    long double y;
    long double z;
} position;

typedef struct vector {
	position x;
    long double velocity;
} vector;

#endif // SHEET04_WEIHS_TAR_GZ_MAIN_H
