#ifndef SCHEDULER_SIM_H
#define SCHEDULER_SIM_H

typedef struct process {
    int pid;

    int arrival_time;
    int burst_time;
    int remaining_time;
    int priority;

    int completion_time;
    int first_run_time;   // -1 means process has not run yet
} process_t;


/* Calculate metrics */
int turnaround_time(process_t *p);
int waiting_time(process_t *p);
int response_time(process_t *p);


/* Reset process before running another algorithm */
void reset_process(process_t *p);


/* Print process information */
void print_process(process_t *p);


/* Print scheduling metrics */
void print_metrics(process_t processes[], int n);
void print_gantt(int timeline[], int length);
#endif

