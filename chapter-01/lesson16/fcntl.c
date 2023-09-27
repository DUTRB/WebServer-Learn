#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

int main(){
    int fd =  open("1.txt", O_RDWR);
    int fd1 = fcntl(fd, F_DUPFD, 0);
    printf("fd: %d\nfd1: %d\n", fd, fd1);
    close(fd1);

    if(fd == -1){
        perror("open");
        return -1;
    }

    int flag = fcntl(fd, F_GETFL);
    flag |= O_APPEND;
    // 2.2.修改文件描述符状态的flag，给flag加入O_APPEND这个标记
    int ret = fcntl(fd, F_SETFL, flag);
    if(ret == -1){
        perror("fcntl");
        return -1;  
    }

    char *str = "nihao";

    write(fd, str, strlen(str));

    close(fd);


    return 0;
}