#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>

int main(){

    //判断文件是否存在
    int ret = access("fifo1", F_OK);
    if(ret == -1){
        printf("pipe is not exsit, so make PIPE.\n");
        //创建管道文件
        ret = mkfifo("fifo1", 0664);
        if(ret == -1){
            perror("makefifo");
            exit(0);
        }
    }

    
    return 0;
}