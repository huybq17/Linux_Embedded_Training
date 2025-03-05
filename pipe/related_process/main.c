/*************************************************************************
 * Include
 ************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

/*************************************************************************
 * Definitions
 ************************************************************************/
#define MAX_SIZE 20u
static char message[MAX_SIZE] = "Hello from parent!";

/*************************************************************************
 * Prototypes
 ************************************************************************/
// Handler signal when received
static void signal_handel(int sig)
{
    wait(NULL); 
    printf("child process termination\n");
}

/*************************************************************************
 * Main program
 ************************************************************************/
int main()
{
    int status;
    int pipe_fds[2];
    pid_t child_pid;
    char buffer[MAX_SIZE];

    if (pipe(pipe_fds) < 0) {
        fprintf(stderr, "pipe unsuccessfully!\n");
        exit(1);
    }

    child_pid = fork();
    if (child_pid < 0) {
        fprintf(stderr, "fork unsuccessfully!\n");
        exit(1);
    }
    if (child_pid == 0) {
        printf("Im Child process.\n");

        // writer is unused
        if (close(pipe_fds[1]) < 0) {
            fprintf(stderr, "close writer unsuccessfully!\n");
            exit(1);
        }

        while (1) {
            status = read(pipe_fds[0], buffer, MAX_SIZE);
            if (status == -1) {
                printf("read() failed\n");
                exit(1);
            } else if (status == 0) {
                printf("Here is end-of-pipe\n");
                break;
            } else {
                printf("Child received: %s\n", message);
            }
        };
    } else {
        printf("Im Parent process.\n");

        signal(SIGCHLD, signal_handel);
        // reader is unused
        if (close(pipe_fds[0]) == -1) {
            fprintf(stderr, "close reader unsuccessfully!\n");
            exit(1);
        }

        write(pipe_fds[1], message, MAX_SIZE);
        if (close(pipe_fds[1]) == -1) {
            fprintf(stderr, "close writer unsuccessfully!\n");
            exit(1);
        }
    }

    return 0;
}
/*************************************************************************
 * EOF
 ************************************************************************/
