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
        {"echo", "Hello, Alex Boyce!", NULL}, //1
        {"echo", "Flags are hard to memorize, so just remember to ask for --help!" , NULL}, //2
        {"ls", "-s", NULL}, //3
        {"ls", "-l", NULL},//4
        {"date", NULL},//5
        {"uptime", NULL}, //6
        {"pwd", NULL}, //7
        {"whoami", NULL}, //8
        {"cal", NULL}, //9
        {"ps", NULL} //10

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