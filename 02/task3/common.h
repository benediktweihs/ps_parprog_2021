//
// Created by benedikt on 22.03.21.
//

#ifndef PS_PARPROG_2021_COMMON_H
#define PS_PARPROG_2021_COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int calcIter(int iter){
    double randX, randY;
    int counter = 0;
    unsigned int seed = time(NULL);

    for(int i = 0; i < iter; i++){
        randX = (double) rand_r(&seed)/RAND_MAX;
        randY = (double) rand_r(&seed)/RAND_MAX;
        counter += (int) (randX*randX + randY*randY);  // hope that randX!=1.!=randY
    }

    return iter - counter;
}

double calcPi(int iter){
    int i = calcIter(iter);
    return 4*((double) i/(double)iter);
}

#endif // PS_PARPROG_2021_COMMON_H
