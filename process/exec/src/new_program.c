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
Function implementations
***************************************************************************************************************/
void sigchld_handler(int sig)
{
    printf("A SIGCHLD signal is delivered to the parent");
    wait(NULL);
}

pid_t replace_process(const char *program, char *const *args) {
    pid_t child_pid = fork();

    // check if current calling process is parent process
    // so we just return pid
    if (child_pid != 0) {
        return child_pid;
    } else if (child_pid == 0){
        // caller is child process, then we replace current image
        // byte new image which declared by program variant
        execvp(program, args);
        // when current image has been replaced by new image, so this
        // statement from here will be replaced by new commands which
        // defined in new image
        perror("execlp");
        abort();
    }
}

char **check_value(char const *args) {
    new_program_t new_pro = UNKNOWN;
    static char *command[ARG_COUNT] = {0};

    char *args_list[] = {"ls", "-l", NULL};
    char *args_date[] = {"date", "--utc", NULL};
    char *args_time[] = {"time", "ls", NULL};
    char *args_process[] = {"ps", "-a", NULL};

    new_pro = atoi(args);
    switch (new_pro) {
        case LIST:
            memcpy(command, args_list, sizeof(args_list));
            break;
        case DATE:
            memcpy(command, args_date, sizeof(args_date));
            break;
        case TIME:
            memcpy(command, args_time, sizeof(args_time));
            break;
        case PROCESS:
            memcpy(command, args_process, sizeof(args_process));
            break;
        default:
            fprintf(stderr, "Error occurred in checking!\n");
    }

    return command;
}

/*************************************************************************
 * EOF
 ************************************************************************/
