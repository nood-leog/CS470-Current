//hello.c
//to run with makefile:
//  make 
// ./Hello

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() 
{
    printf("Running...\n");

    int status;
    const int numberofChildren = 10;
    pid_t pid, cpid;


    char *commands[][10] = 
    {
        //echo can be used to print text to the console, for example, our first two commands:
        {"echo", "Hello, Alex Boyce!", NULL}, //1

        //ls -l is used to list files in long format, showing permissions, owner, group, size, and modification date
        {"ls", "-l", NULL},//2

        //groups is used to display the groups the current user belongs to
        {"groups", NULL},//3

        //date is used to display the current date and time
        {"date", NULL},//4

        //uptime is used to show how long the system has been running
        {"uptime", NULL}, //5

        //pwd is used to print the current working directory
        {"pwd", NULL}, //6

        //whoami is used to display the username of the current user
        {"whoami", NULL}, //7

        //uname -a is used to display system information, including kernel name, version, and architecture
        {"uname", "-a", NULL}, //8

        //cal is used to display a calendar, in this case, the current month
        {"cal", NULL}, //9

        //ps is used to display information about running processes
        {"ps", NULL}, //10
    };

    printf("Parent process PID: %d\n", getpid());

    for (int i = 0; i < numberofChildren; i++) 
    {
        pid = fork();
        if (pid < 0) 
        {
            perror("Fork failed");
            exit(EXIT_FAILURE);
        } 
        else if (pid == 0) 
        {
            // Child process
            printf("Child Process PID: %d -- Executing command: %s\n", getpid(), commands[i][0]);
            execvp(commands[i][0], commands[i]);
            // Only reaches here if exec fails
            perror("Exec failed");
            exit(EXIT_FAILURE);
        }
    }

    // Parent waits for all children
    for (int i = 0; i < numberofChildren; i++) 
    {
        cpid = wait(&status);
        if (WIFEXITED(status)) 
        {
            printf("Child PID %d exited with status %d\n", cpid, WEXITSTATUS(status));
        } 
        else if (WIFSIGNALED(status)) 
        {
            printf("Child PID %d was terminated by signal %d\n", cpid, WTERMSIG(status));
        } 
    }

    return 0;
}