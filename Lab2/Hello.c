//hello.c
//to run with makefile
//make hello

/*
Write a C program where the main process (parent) creates multiple child
processes at least 10 child processes.
Each child process should perform a unique task.
One of your processes should be “echo "Hello + <Your Name>" ”

2. Child Process Execution:
• Use fork() to create child processes.
• In each child process, use an exec function (like execvp) to execute a simple
command (e.g., ls, echo) or a custom program.
3. Process Synchronization:
• After creating child processes, the parent process should use wait() or waitpid() to
wait for the child processes to complete.
• Include detailed status reporting after each child process terminates:
• Report whether the child exited normally or was terminated by a signal.
• Display the exit status or signal number as appropriate.
4. Reporting:
• The parent process should report the completion of each child process.
• Optionally, each child process can output its PID and the command it is
executing.

*/


#include <stdio.h>
#include <stdlib.h>

int main() {
    printf("Main function\n");

    int status;
    const int numberofChildren = 3;

    char *commands[][10] = {
        {"ls", "-l", NULL}, 
        {"echo", "Hello, Alex Boyce!", NULL}, 
        {"date", NULL}, 

    };


    prinf("Parent process PID: %d\n", getpid());

    for (int i=0; i<numberofChildren; i++) {
        pid = fork();
        if (pid < 0) {
            perror("Fork failed");
            exit(EXIT_FAILURE);
        }
        else if (pid == 0) {
            // Child process
            printf("Child process PID: %d\n", getpid());
            execvp(commands[i][0], commands[i]);
            perror("exec failed");
            exit(EXIT_FAILURE);
        }
    }
    return 0;
}