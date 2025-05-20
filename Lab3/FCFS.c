//FCFS.c

//to run:
//make FCFS
//./FCFS

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define TIME_QUANTUM 4

typedef struct 
{
    int process_id;
    int arrival_time;
    int burst_time;
    int waiting_time;
    int turnaround_time;
} Process;

//prototypes
void  sortProcessesByArrival(Process proc[], int n);
void fcfs(Process proc[], int n);
void RR(Process proc[], int n);
void srtf(Process proc[], int n);
void printProcesses(const Process proc[], int n);
void turnAroundTime(Process proc[], int n);

int main() 
{
    Process proc[] = 
    {
        {1, 0, 24, 0, 0},
        {2, 0,  3, 0, 0},
        {3, 0,  3, 0, 0}
    };
    int n = sizeof(proc) / sizeof(proc[0]);

    //first come first served
    printf("\nFirst Come First Served scheduling\n");
    fcfs(proc, n);
    printProcesses(proc, n);

    //reset
    for (int i = 0; i < n; i++) 
    {
        proc[i].waiting_time = proc[i].turnaround_time = 0;
    }

    //round robin
    printf("\nRound Robin scheduling (quantum = %d)\n", TIME_QUANTUM);
    RR(proc, n);
    printProcesses(proc, n);

    //reset
    for (int i = 0; i < n; i++) 
    {
        proc[i].waiting_time = proc[i].turnaround_time = 0;
    }

    //shortest remaining time first
    printf("\nShortest Remaining Time First scheduling\n");
    srtf(proc, n);
    printProcesses(proc, n);

    return 0;
}

//first come first served
void fcfs(Process proc[], int n)
{
    //sort processes by arrival time
    sortProcessesByArrival(proc, n);

    //first process always has 0 waiting time
    proc[0].waiting_time = 0; 

    //waiting time = waiting time of previous process + burst time of previous process - arrival time of current process
    for (int i=1; i<n; i++)
    {
        proc[i].waiting_time = proc[i-1].waiting_time + proc[i-1].burst_time - proc[i].arrival_time;
    }

    //trunaround time = waiting time + burst time - arrival time
    for (int i=0; i<n; i++)
    {
        proc[i].turnaround_time = proc[i].waiting_time + proc[i].burst_time - proc[i].arrival_time;
    }

    //print order of execution
    printf("Order of execution: ");
    for (int i=0; i<n; i++)
    {
        printf("%d ", proc[i].process_id);
    }
    printf("\n");
}

//round robin
void RR(Process proc[], int n) 
{
    int rem_bt[n], time = 0, done = 0;
    for (int i = 0; i < n; i++) 
    {
        rem_bt[i] = proc[i].burst_time;
    }

    while (done < n) 
    {
        for (int i = 0; i < n; i++) 
        {
            if (proc[i].arrival_time <= time && rem_bt[i] > 0) 
            {
                int qt = (rem_bt[i] > TIME_QUANTUM ? TIME_QUANTUM : rem_bt[i]);
                rem_bt[i] -= qt;
                time     += qt;
                if (rem_bt[i] == 0) 
                {
                    done++;
                    proc[i].waiting_time = time
                        - proc[i].arrival_time
                        - proc[i].burst_time;
                    proc[i].turnaround_time = proc[i].waiting_time
                        + proc[i].burst_time;
                }
            }
        }
    }
}

//shortest remaining time first
void srtf(Process proc[], int n) 
{
    int rem_bt[n], complete = 0, time = 0;
    for (int i = 0; i < n; i++) 
    {
        rem_bt[i] = proc[i].burst_time;
    }

    while (complete < n) 
    {
        int idx = -1, min_bt = INT_MAX;
        for (int i = 0; i < n; i++) 
        {
            if (proc[i].arrival_time <= time && rem_bt[i] > 0 && rem_bt[i] < min_bt) 
            {
                min_bt = rem_bt[i];
                idx    = i;
            }
        }
        if (idx == -1) 
        {
            time++;
            continue;
        }
        rem_bt[idx]--;
        time++;
        if (rem_bt[idx] == 0) 
        {
            complete++;
            proc[idx].waiting_time = time
                - proc[idx].arrival_time
                - proc[idx].burst_time;
            if (proc[idx].waiting_time < 0)
            {
                proc[idx].waiting_time = 0;
            }
        }
        
    }
    
    for (int i = 0; i < n; i++)
    {
        proc[i].turnaround_time = proc[i].waiting_time + proc[i].burst_time;
    }
}


//Function to manually sort processes by arrival time
void sortProcessesByArrival(Process proc[], int n) 
{
    for (int i = 0; i < n-1; i++)
    {
        for (int j = 0; j < n-1-i; j++)
        {
            if (proc[j].arrival_time > proc[j+1].arrival_time) 
            {
                Process tmp = proc[j];
                proc[j]     = proc[j+1];
                proc[j+1]   = tmp;
            }
        }
    }
}


//fucntion to turn around time
void turnAroundTime(Process proc[], int n)
{
    //turnaround time = waiting time + burst time
    for (int i=0; i<n; i++)
    {
        proc[i].turnaround_time = proc[i].waiting_time + proc[i].burst_time;
    }
}

//print processes
void printProcesses(const Process proc[], int n) 
{
    printf("PID\tArr\tBurst\tWait\tTurn\n");
    for (int i = 0; i < n; i++) 
    {
        printf("%d\t%d\t%d\t%d\t%d\n",
            proc[i].process_id,
            proc[i].arrival_time,
            proc[i].burst_time,
            proc[i].waiting_time,
            proc[i].turnaround_time);
    }
}
