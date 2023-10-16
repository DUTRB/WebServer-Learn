/*
    实现ps aux | grep xxx 父子进程间通信

    子进程： ps aux ,子进程结束后，将数据发送给父进程
    父进程：获取到数据，过滤
    pipe()函数
    execlp()函数
    子进程将标准输出 stdout_fileno 重定向到管道的写端。 dup2()函数

*/


#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wait.h>

int main(){

    //创建管道
    int fd[2];
    int ret = pipe(fd);
    if(ret == -1){
        perror("pipe");
        exit(0);
    }
    //创建子进程
    pid_t pid = fork();
    if(pid > 0){
        //关闭写端
        close(fd[1]);
        //从管道里读取数据 过滤然后输出
        char buf[4096] = {0};

        int len = -1;

        while(len = read(fd[0], buf, sizeof(buf) - 1) > 0){
            printf("%s", buf);
            memset(buf, 0, 4096);
        }
        //回收子进程资源
        wait(NULL);
      

    }else if(pid == 0){ 
        //关闭读端
        close(fd[0]);
        //文件描述符重定向
        dup2(fd[1], STDOUT_FILENO);
        //执行 ps
        execlp("ps", "ps", "aux", NULL);
        perror("execlp");
        exit(0);

    }else{
        perror("fork");
        exit(0);
    }


    return 0;
}
