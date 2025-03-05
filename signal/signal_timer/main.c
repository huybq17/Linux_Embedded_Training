/*************************************************************************
 * Include
 ************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>

/*************************************************************************
 * Definitions
 ************************************************************************/
static int count_signal = 0;

/*************************************************************************
 * Prototypes
 ************************************************************************/
void alarm_handler(int sig) {
    count_signal++;
    printf("Timer: %d seconds.\n", count_signal);

    if (count_signal >= 10) {
        printf("Exiting!\n");
        exit(0);
    }

    alarm(1);
}

/*************************************************************************
 * Main program
 ************************************************************************/
int main() {
    int i;
    if (signal(SIGALRM, alarm_handler) == SIG_ERR) {
        fprintf(stderr, "Cannot receive SIGALRM!\n");
        exit(EXIT_FAILURE);
    }

    alarm(1);

    while (1) {
        sleep(1);
    }

    return 0;
}

/*************************************************************************
 * EOF
 ************************************************************************/
