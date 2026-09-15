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
    int completed = 0;

    int timeline[100];
    int timeline_length = 0;

    while (completed < n)
    {
        int shortest = -1;

        // Find process with shortest remaining time
        for (int i = 0; i < n; i++)
        {
            if (processes[i].arrival_time <= clock &&
                processes[i].remaining_time > 0)
            {
                if (shortest == -1 ||
                    processes[i].remaining_time <
                    processes[shortest].remaining_time)
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
        if (p->first_run_time == -1)
        {
            p->first_run_time = clock;
        }

        // Run for one time unit
        timeline[timeline_length++] = p->pid;

        p->remaining_time--;
        clock++;

        // Process finished
        if (p->remaining_time == 0)
        {
            p->completion_time = clock;
            completed++;
        }
    }

    printf("\nSRTF Scheduling\n");
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
