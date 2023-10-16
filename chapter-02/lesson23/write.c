/*
    有名管道测试案例：
    
    write.c->向管道中写入数据
    read.c->向管道中读取数据

*/
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main(){

    //判断文件是否存在
    int ret = access("test", F_OK);
    if(ret == -1){
        printf("pipe is not exsit, so make PIPE.\n");

        ret = mkfifo("test", 0664);
        if(ret == -1){
            perror("makefifo");
            exit(0);
        }
    }
    //打开管道
    int fd = open("test", O_WRONLY);
    if(fd == -1){
        perror("open");
        exit(0);
    }

    //写数据
    for(int i = 0; i < 10; i++){
        char buf[1024];
        sprintf(buf, "Hello, %d\n", i);
        printf("write data : %s", buf);
        write(fd, buf, strlen(buf));
        sleep(1);
    }
    close(fd);

    return 0;
}