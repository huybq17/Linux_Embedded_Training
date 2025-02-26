#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void signal_handle(int num_sig) {
    printf("Received signal %d\n", SIGCHLD);
    wait(NULL);
}

int main(int argc, char const *argv[]) {
    pid_t child_pid = fork();
    
    if (child_pid >= 0) {
        if (child_pid == 0) {
            printf("I'm Child, Child PID: %d\n", getpid());
        }
        else {
            signal(SIGCHLD, signal_handle);
            printf("I'm Parent, My Child PID: %d\n", child_pid);
            while(1);
        }
    } else {
        printf("Error creating the child process");
        perror("fork");
    }

    return 0;
}