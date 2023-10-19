#define _DEFAULT_SOURCE
#include <stdio.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>

#define BUF_LEN     4096

int main(){
    //创建匿名映射区
    void *ptr = mmap(NULL, BUF_LEN, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    if(ptr == MAP_FAILED){
        perror("mmap");
        exit(0);
    }
    //父子间通信
    pid_t pid = fork();
    if(pid > 0){
        strcpy((char *)ptr, "Hello world");
        wait(NULL);
    }
    else if(pid == 0){
        sleep(1);
        printf("%s\n", (char *)ptr);
    }

    //释放内存映射区
    int ret = munmap(ptr, BUF_LEN);
    if(ret == -1){
        perror("munmap");
        exit(0);
    }

    return 0;
}