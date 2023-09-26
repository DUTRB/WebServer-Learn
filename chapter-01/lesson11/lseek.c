#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main(){
    int fd = open("test.txt", O_RDWR);
    if(fd == -1){
        perror("open");
        return -1;

    }
    //扩展文件长度
    lseek(fd, 100, SEEK_END);
    write(fd, "111", 1);

    close(fd);
    return 0;
}