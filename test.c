#include <stdio.h>
#include "scheduler_sim.h"

int main()
{
    process_t p = {
        1,      // pid
        0,      // arrival_time
        5,      // burst_time
        5,      // remaining_time
        2,      // priority
        10,     // completion_time
        0       // first_run_time
    };

    print_process(&p);

    printf("Turnaround = %d\n", turnaround_time(&p));
    printf("Waiting = %d\n", waiting_time(&p));
    printf("Response = %d\n", response_time(&p));

    return 0;
}
