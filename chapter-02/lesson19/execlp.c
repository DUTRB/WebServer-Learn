#include <unistd.h>
#include <stdio.h>

int main(){

    //创建一个子进程，在子进程执行execl()函数
    __pid_t pid = fork();

    if(pid > 0){
        printf("I am parent process, pid : %d\n", getpid());
        sleep(1);
    }
    else if(pid == 0){
        execlp("ps", "ps", "aux" , NULL);

        printf("I am child process, pid = %d\n", getpid());
    }

    for(int i = 0; i < 3; i++){
        printf("i = %d, pid = %d\n", i, getpid());
    }

    return 0;
}