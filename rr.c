#include <stdio.h>
#include "scheduler_sim.h"
#include "workload.h"

int main()
{
    int n = N;
    int quantum = 2;

    process_t processes[N];

    // Copy common workload
    for (int i = 0; i < N; i++)
    {
        processes[i] = workload[i];
    }

    int clock = 0;
    int completed = 0;

    int queue[100];
    int front = 0;
    int rear = 0;

    int added[N];

    for (int i = 0; i < N; i++)
    {
        added[i] = 0;
    }

    int timeline[100];
    int timeline_length = 0;

    while (completed < n)
    {
        // Add newly arrived processes
        for (int i = 0; i < n; i++)
        {
            if (!added[i] &&
                processes[i].arrival_time <= clock)
            {
                queue[rear++] = i;
                added[i] = 1;
            }
        }

        // CPU is idle
        if (front == rear)
        {
            clock++;
            continue;
        }

        // Take process from front of queue
        int index = queue[front++];

        process_t *p = &processes[index];

        // First time process gets CPU
        if (p->first_run_time == -1)
        {
            p->first_run_time = clock;
        }

        int run_time = quantum;

        if (p->remaining_time < quantum)
        {
            run_time = p->remaining_time;
        }

        // Run process for its time quantum
        for (int t = 0; t < run_time; t++)
        {
            timeline[timeline_length++] = p->pid;

            p->remaining_time--;
            clock++;

            // Add processes that arrive during execution
            for (int i = 0; i < n; i++)
            {
                if (!added[i] &&
                    processes[i].arrival_time <= clock)
                {
                    queue[rear++] = i;
                    added[i] = 1;
                }
            }
        }

        // Process finished
        if (p->remaining_time == 0)
        {
            p->completion_time = clock;
            completed++;
        }
        else
        {
            // Put process back at end of queue
            queue[rear++] = index;
        }
    }

    printf("\nRound Robin Scheduling\n");
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
