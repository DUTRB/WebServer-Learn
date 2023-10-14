#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    //一定是在fork创建子进程之前创建管道
    int pipefd[2];
    int ret = pipe(pipefd);
    if(ret == -1){
        perror("pipe");
        exit(0);
    }

    //创建子进程
    pid_t pid = fork();
    if(pid > 0)
    {
        printf("I am parent process, pid = %d\n", getpid());

        char buf[1024] = {0};
        while(1){
            //从管道读取数据
            int len = read(pipefd[0], buf, sizeof(buf));
            printf("parent rev: %s, pid : %d\n", buf, getpid());

            //向管道中写入数据
            char *str = "write test";
            write(pipefd[1], str, strlen(str));
            sleep(1);
        }
    }
    else if(pid == 0){
        //子进程
        printf("    I am child process, pid = %d\n", getpid());

        char buf[1024] = {0};
        while(1){
            //往管道写入数据
            char *str = "   hello, I am child";
            write(pipefd[1], str, strlen(str));
            sleep(1);

            //从管道读取数据
            int len = read(pipefd[0], buf, sizeof(buf));
            printf("    child pecv: %s, pid = %d\n", buf, getpid());
        }

    }

    return 0;
}