#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>


int main(){

    //1. 判断文件是否存在
    int ret = access("fifo1", F_OK);
    if(ret == -1){
        printf("有名管道文件不存在，需要创建有名管道1。");
        ret = mkfifo("fifo1", 0664);
        if(ret == -1){
            perror("mkfifo");
            exit(0);
        }
    }
    ret = access("fifo2", F_OK);
    if(ret == -1){
        printf("有名管道文件不存在，需要创建有名管道2。");
        ret = mkfifo("fifo2", 0664);
        if(ret == -1){
            perror("mkfifo");
            exit(0);
        }
    }
    //2. 以只读的方式打开fifo1
    int fdr = open("fifo1", O_RDONLY);
    if(fdr == -1){
        perror("open");
        exit(0);
    }
    printf("打开fifo1成功,等待读取...");
    //3. 以只写的方式打开fifo2
    int fdw = open("fifo2", O_WRONLY);
    if(fdw == -1){
        perror("open");
        exit(0);
    }
    printf("打开fifo2成功,等待写入...");

    //4. 循环的读写数据
    char buf[128];
    while(1){  
        //5. 读取管道数据
        memset(buf, 0, 128);
        ret = read(fdr, buf, 128);
        if(ret <= 0){
            perror("read");
            break;
        }
        printf("buf: %s", buf);

        memset(buf, 0, 128);
        //获取标准输入的数据
        fgets(buf, 128, stdin);
        //写数据
        ret = write(fdw, buf, strlen(buf));
        if(ret == -1){
            perror("write");
            exit(0);
        }
    }
    //6. 关闭文件描述符
    close(fdr);
    close(fdw);

    return 0;
}