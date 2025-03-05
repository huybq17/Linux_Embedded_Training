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
void sigint_handler(int sig) {
    count_signal++;

    printf("SIGINT received %d\n", count_signal);
    if (count_signal >= 3) {
        printf("Received SIGINT 3 times. Exiting.\n");
        exit(EXIT_SUCCESS);
    }

}

/*************************************************************************
 * Main program
 ************************************************************************/
int main() {
	if (signal(SIGINT, sigint_handler) == SIG_ERR) {
        fprintf(stderr, "Cannot receive SIGINT!\n");
        exit(EXIT_FAILURE);
    }

    while (1) {
        // Add sleep() to avoid CPU running 100%
        sleep(1);
    }

    return 0;
}
/*************************************************************************
 * EOF
 ************************************************************************/
