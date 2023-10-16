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

int main(){

    //打开管道文件
    int fd = open("test", O_RDONLY);
    if(fd == -1){
        perror("open");
        exit(0);
    }

    //读取数组
    while(1){
        char buf[1024] = {0};
        int len = read(fd, buf, sizeof(buf));
        if(len == 0){
            printf("写端断开连接了...\n");
            break;
        }
        printf("recv data: %s", buf);
    }
    close(fd);


    return 0;
}