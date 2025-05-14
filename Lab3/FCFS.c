//FCFS.c

//to run:
//make FCFS
//./FCFS

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int process_id;
    int arrival_time;
    int burst_time;
    int waiting_time;
    int turnarround_time;
} Process;

//Function to manually sort processes by arrival time
void sortProcessesByArrival(Process proc[], int n)
{
    for (int i=0; i<n-1; i++)
    {
        for (int j=0; j<n-i-1; j++)
        {
            if (proc[j].arrival_time>proc[j+1].arrival_time)
            {
                Process temp = proc[j+1];
                proc[j] = proc [j+1];
                proc [j+1] = temp;
            }
        }
    }
}

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
        proc[i].turnarround_time = proc[i].waiting_time + proc[i].burst_time - proc[i].arrival_time;
    }

    //print order of execution
    printf("Order of execution: ");
    for (int i=0; i<n; i++)
    {
        printf("%d ", proc[i].process_id);
    }
    printf("\n");
}


//fucntion to turn around time
void turnAroundTime(Process proc[], int n)
{
    //turnaround time = waiting time + burst time
    for (int i=0; i<n; i++)
    {
        proc[i].turnarround_time = proc[i].waiting_time + proc[i].burst_time;
    }
}

//fucntion to perform RR scheduling
void roundRobin()
{
    //RR implementation
    //to be implemented
}

//function to perform SRTF scheduling
void srtf()
{
    //SRTF implementation
    //to be implemented
}


void printProcesses(Process proc[], int n)
{
    printf("Process ID\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i=0; i<n; i++)
    {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n", proc[i].process_id, proc[i].arrival_time, proc[i].burst_time, proc[i].waiting_time, proc[i].turnarround_time);

    }
}


int main ()
{
    //intialize process with ids, arrival time, burst time

    Process proc[] = {{1, 0, 24}, {2, 0, 3}, {3,0,3}};
    int n = sizeof(proc)/sizeof(proc[0]);

    //quantum time for something here? maybe roundrobin

    fcfs(proc, n);
    printProcesses(proc, n);
    return 0;
}