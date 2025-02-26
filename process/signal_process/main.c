/*************************************************************************
 * Include
 ************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

/*************************************************************************
 * Static Function
 ************************************************************************/
// Handle the signal SIGUSR1
static void sigusr1_handler(int sig) {
    if (sig == SIGUSR1) {
        printf("Child process received SIGUSR1 signal!\n");
    }
}

/**************************************************************************************************************
* Main program
***************************************************************************************************************/
int main() {
    child_pid_t child_pid = fork();
    int wstatus = 0;
    int kill_status = 0;
    
    if (child_pid < 0) {
        perror("Fork failed");
        exit(1);
    }
    
    // Here is child process
    if (0 == child_pid) {
        signal(SIGUSR1, sigusr1_handler);
        printf("Child process waiting for SIGUSR1...\n");
        while (1);
    } else { 
        sleep(2);
        printf("Parent process sending SIGUSR1 to child (child_pid: %d)\n", child_pid);
        kill_status = kill(child_pid, SIGUSR1);
        if (kill_status < 0) {
            printf("Failed to send a signall to the child process!");
        }
        wait(&wstatus);
    }
    
    return 0;
}
/**************************************************************************************************************
* EOF
***************************************************************************************************************/
