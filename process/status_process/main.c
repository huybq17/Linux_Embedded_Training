/*************************************************************************
 * Include
 ************************************************************************/
 #include <stdio.h>
 #include <stdlib.h>
 #include <unistd.h>
 #include <signal.h>
 #include <sys/types.h>
 #include <sys/wait.h>

/**************************************************************************************************************
* Main program
***************************************************************************************************************/
int main() {
    pid_t child_pid = fork();
    int wstatus = 0;

    if (child_pid < 0) {
        perror("Fork failed");
        exit(1);
    }

    if (0 == child_pid) {
        printf("I'm Child process with PID: %d\n", getpid());
        printf("I'm starting the process of ending\n");
        sleep(2);
        exit(7);
    } else {
        printf("Parent process...\n");
        waitpid(child_pid, &wstatus, 0);

        if (WIFEXITED(wstatus)) {
            printf("Child exited normally with code %d.\n", WEXITSTATUS(wstatus));
        } else {
            printf("Child did not exit normally.\n");
        }
    }

    return 0;
}

/**************************************************************************************************************
* EOF
***************************************************************************************************************/
