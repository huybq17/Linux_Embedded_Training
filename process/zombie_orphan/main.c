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
 * Prototypes
 ************************************************************************/
static void create_zombie() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        exit(1);
    }
    if (pid == 0) {
        // Child process: stays alive long enough to become zombie
        printf("Child process (Zombie) PID = %d\n", getpid());
        sleep(15);  // Keep child alive for 10 seconds
        printf("Child process (Zombie) exits\n");
        exit(0);
    } else {
        // Parent process exits immediately
        printf("Parent process (creating zombie) PID = %d\n", getpid());
        printf("Parent process exits, leaving child as zombie\n");
        exit(0);  // Parent exits without waiting for the child
    }
}

static void create_orphan() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        exit(1);
    }
    if (pid == 0) {
        // Child process: will become orphan
        sleep(5);  // Sleep so parent exits first
        printf("Orphan child process PID = %d, Parent PID = %d\n", getpid(), getppid());
        sleep(5);  // Sleep more to observe new parent (init)
        printf("Orphan child exits\n");
        exit(0);
    } else {
        // Parent process exits before child
        printf("Parent process (creating orphan) PID = %d\n", getpid());
        sleep(2);  // Ensure parent exits first
        printf("Parent process exits\n");
        exit(0);
    }
}

/*************************************************************************
 * Main program
 ************************************************************************/
int main(int argc, char const *argv[]) {

    // 1 for zombie or 2 for orphan, Plz entering which process you need
    if (strcmp(argv[1],"1") == 0) {
        printf("Creating zombie process...\n");
        create_zombie();
        sleep(15);  // Give time to observe the zombie with `ps`
    } else if (strcmp(argv[1],"2") == 0) {
        printf("Creating orphan process...\n");
        create_orphan();
        sleep(10);  // Allow time to observe orphan process
    } else {
        printf("Invalid argument. Please use 1 for zombie or 2 for orphan.\n");
    }

    return 0;
}

/*************************************************************************
 * EOF
 ************************************************************************/
