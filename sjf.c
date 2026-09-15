#include <stdio.h>
#include "scheduler_sim.h"

int main()
{
    process_t processes[] = {
        {1, 0, 7, 7, 2, 0, -1},
        {2, 1, 3, 3, 1, 0, -1},
        {3, 2, 2, 2, 3, 0, -1}
    };

    int n = 3;
    int clock = 0;
    int completed = 0;

    int timeline[100];
    int timeline_length = 0;

    while (completed < n)
    {
        int shortest = -1;

        // Find shortest arrived process
        for (int i = 0; i < n; i++)
        {
            if (processes[i].remaining_time > 0 &&
                processes[i].arrival_time <= clock)
            {
                if (shortest == -1 ||
                    processes[i].burst_time <
                    processes[shortest].burst_time)
                {
                    shortest = i;
                }
            }
        }

        // CPU is idle
        if (shortest == -1)
        {
            clock++;
            continue;
        }

        process_t *p = &processes[shortest];

        // First time process gets CPU
        p->first_run_time = clock;

        // Run process one time unit at a time
        for (int t = 0; t < p->burst_time; t++)
        {
            timeline[timeline_length++] = p->pid;
            clock++;
        }

        p->remaining_time = 0;
        p->completion_time = clock;

        completed++;
    }

    printf("\nSJF Scheduling\n");
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

    // Print Gantt timeline
    print_gantt(timeline, timeline_length);

    return 0;
}
