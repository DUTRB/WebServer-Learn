#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>

int main(){
    int fd = open("rubo.txt", O_RDWR | O_CREAT, 0664);
    int fd1 = dup(fd);
    if(fd1 == -1){
        perror("dup");
        return -1;
    }
    printf("fd: %d \nfd1: %d \n", fd, fd1);

    close(fd);

    char* str = "Hello RUBO ";
    int ret = write(fd1, str, strlen(str));
    if(ret == -1){
        perror("write");
        return -1;
    }
    close(fd1);

    return 0;
}