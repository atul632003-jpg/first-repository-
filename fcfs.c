#include <stdio.h>
#include "scheduler_sim.h"
#include "workload.h"

int main()
{
    int n = N;
    process_t processes[N];

    // Copy common workload
    for (int i = 0; i < N; i++)
    {
        processes[i] = workload[i];
    }

    int clock = 0;

    int timeline[100];
    int timeline_length = 0;

    for (int i = 0; i < n; i++)
    {
        process_t *p = &processes[i];

        // CPU waits if process has not arrived
        if (clock < p->arrival_time)
        {
            clock = p->arrival_time;
        }

        // First time process gets CPU
        p->first_run_time = clock;

        // Run process until completion
        for (int t = 0; t < p->burst_time; t++)
        {
            timeline[timeline_length++] = p->pid;
            clock++;
        }

        p->remaining_time = 0;
        p->completion_time = clock;
    }

    printf("\nFCFS Scheduling\n");
    printf("-------------------------\n");

    for (int i = 0; i < n; i++)
    {
        process_t *p = &processes[i];

        printf(
            "P%d: Completion=%d, Waiting=%d, Turnaround=%d, Response=%d\n",
            p->pid,
            p->completion_time,
            waiting_time(p),
            turnaround_time(p),
            response_time(p)
        );
    }

    print_metrics(processes, n);

    print_gantt(timeline, timeline_length);

    return 0;
}
