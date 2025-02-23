#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main() {
    int fd;
    char *data = "This data will be written at the beginning of the file.";

    // Open a file in O_APPEND mode and create new file if it does not exist
    fd = open("input.txt", O_WRONLY | O_CREAT | O_APPEND, 0777);
    if (fd == -1) {
        perror("Error opening file");
        return 1;
    }

    // Move the file pointer to the beginning of the file
    lseek(fd, 0, SEEK_SET);
    // Write data to the beginning of the file
    write(fd, data, strlen(data));

    // CLose the file
    close(fd);

    return 0;
}