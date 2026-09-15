#include <stdio.h>
#include "scheduler_sim.h"


int turnaround_time(process_t *p)
{
    return p->completion_time - p->arrival_time;
}


int waiting_time(process_t *p)
{
    return turnaround_time(p) - p->burst_time;
}


int response_time(process_t *p)
{
    return p->first_run_time - p->arrival_time;
}


void reset_process(process_t *p)
{
    p->remaining_time = p->burst_time;
    p->completion_time = 0;
    p->first_run_time = -1;
}


void print_process(process_t *p)
{
    printf(
        "P%d  Arrival=%d  Burst=%d  Priority=%d\n",
        p->pid,
        p->arrival_time,
        p->burst_time,
        p->priority
    );
}
