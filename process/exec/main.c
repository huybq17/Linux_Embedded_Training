/*************************************************************************
 * Include
 ************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include "new_program.h"


/**************************************************************************************************************
* Main program
***************************************************************************************************************/
int main(int argc, char const *argv[]) {
    int i;
    pid_t child_pid;

    for (i = 1; i < argc; i++) {
        if (NULL == *check_value(argv[i])) {
             printf("Argument is unstable!\n");
             break;
        }

        child_pid = replace_process(*check_value(argv[i]), check_value(argv[i]));
        if (child_pid < 0) {
            printf("Error occurred in creating the Child Process!\n");
            break;
        } else if (child_pid > 0) {
            /**When a child is terminated, a corresponding SIGCHLD signal 
             * is delivered to the parent
            */
            signal(SIGCHLD, sigchld_handler);
        }
    }

    return 0;
}

/*************************************************************************
 * EOF
 ************************************************************************/
