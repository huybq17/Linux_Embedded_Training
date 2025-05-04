#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    int fd1, fd3; 
    char *data1 = "Hello,", *data2 = "world", *data3 = "HELLO,";

    fd1 = open("input2.txt", O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if (fd1 == -1) {
        perror("Error opening file");
        return -1;
    }

    fd3 = open("input2.txt", O_RDWR); 
    if (fd3 == -1) {
        perror("Error opening file");
        return -1;
    }

    write(fd1, data1, 6); 
    write(fd1, data3, 6); 
    write(fd3, "Gidday", 6);

    close(fd1); 
    close(fd3);

    return 0;
}