#ifndef WORKLOAD_H
#define WORKLOAD_H

#include "scheduler_sim.h"

#define N 3

static process_t workload[N] = {
    {1, 0, 7, 7, 2, 0, -1},
    {2, 1, 3, 3, 1, 0, -1},
    {3, 2, 2, 2, 3, 0, -1}
};

#endif
