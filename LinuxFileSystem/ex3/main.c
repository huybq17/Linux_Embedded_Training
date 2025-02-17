#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

/**************************************************************************************************************
Definitions
***************************************************************************************************************/
#define LOG_FILE "error.log"

/**************************************************************************************************************
Prototypes
***************************************************************************************************************/
/* Write any errors to the log file */
void log_error(const char *message) {
    FILE *log_fp = fopen(LOG_FILE, "a");
    if (log_fp) {
        fprintf(log_fp, "Error: %s\n", message);
        fclose(log_fp);
    }
}

/**************************************************************************************************************
Function implementations
***************************************************************************************************************/
int main(int argc, char const *argv[]) {
    int fd;
    struct stat fileStat;
    const char *filename = argv[1];
    const char *data = argv[2];

    // ./myexe file name data
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <filename> <data>\n", argv[0]);
        log_error("Invalid arguments!");
        return 0;
    }
    
    fd = open(filename, O_RDWR | O_CREAT, 0644);
    if (fd == -1) {
        perror("Error opening file");
        log_error("Failed to open file");
        return 0;
    }
    
    if (write(fd, data, strlen(data)) == -1) {
        perror("Error writing to file!");
        log_error("Failed to write to file");
        return 0;
    }
    close(fd);
    
    if (stat(filename, &fileStat) == -1) {
        perror("Error getting file stats");
        log_error("Failed to retrieve file stats");
        return 0;
    }
    
    printf("File Information:\n");
    printf("File Name: %s\n", filename);
    printf("File Type: %s\n", S_ISREG(fileStat.st_mode) ? "Regular file" :
                                 S_ISDIR(fileStat.st_mode) ? "Directory" :
                                 S_ISCHR(fileStat.st_mode) ? "Character device" :
                                 S_ISBLK(fileStat.st_mode) ? "Block device" :
                                 S_ISLNK(fileStat.st_mode) ? "Symbolic Link" : "Other");
    printf("Owner UID: %d\n", fileStat.st_uid);
    printf("Group GID: %d\n", fileStat.st_gid);
    printf("Number of Hard Links: %ld\n", fileStat.st_nlink);
    printf("Last Modified: %s", ctime(&fileStat.st_mtime));
    printf("File Size: %ld bytes\n", fileStat.st_size);
    printf("Last Status Change Time: %s", ctime(&fileStat.st_ctime));

    return 0;
}
