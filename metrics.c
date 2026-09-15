#include <stdio.h>
#include "scheduler_sim.h"

void print_metrics(process_t processes[], int n)
{
    int total_waiting = 0;
    int total_turnaround = 0;
    int total_response = 0;

    for (int i = 0; i < n; i++)
    {
        total_waiting += waiting_time(&processes[i]);
        total_turnaround += turnaround_time(&processes[i]);
        total_response += response_time(&processes[i]);
    }

    printf("\nMetrics\n");
    printf("-------------------------\n");

    printf("Average Waiting Time    = %.2f\n",
           (float)total_waiting / n);

    printf("Average Turnaround Time = %.2f\n",
           (float)total_turnaround / n);

    printf("Average Response Time   = %.2f\n",
           (float)total_response / n);
}


void print_gantt(int timeline[], int length)
{
    printf("\nGantt Timeline\n");
    printf("-------------------------\n");

    for (int i = 0; i < length; i++)
    {
        printf("| P%d ", timeline[i]);
    }

    printf("|\n");

    printf("0");

    for (int i = 1; i <= length; i++)
    {
        printf("    %d", i);
    }

    printf("\n");
}
