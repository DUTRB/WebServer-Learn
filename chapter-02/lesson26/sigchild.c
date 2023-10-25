
#define _DEFAULT_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

void myFun(int num){
    printf("捕捉到的信号：%d\n", num);
    
    while(1){
        int ret = waitpid(-1, NULL, WNOHANG);
        if(ret > 0){
            printf("------------- child die,pid = %d\n", ret);
        }else if(ret == 0){
            break;;
        }else if(ret == -1){
            break;
        }
    }
}

int main(){

    //提前设置好阻塞信号集
    sigset_t set;
    sigemptyset(&set);
    sigaddset(&set, SIGCHLD);
    sigprocmask(SIG_BLOCK, &set, NULL);


    //创建一些子进程
    pid_t pid;
    for(int i = 0; i < 20; i++){
        pid = fork();
        if(pid == 0){
            break;
        }
    }

    if(pid > 0){
        //父进程
        struct sigaction act;
        act.sa_flags = 0;
        act.sa_handler = myFun;
        sigemptyset(&act.sa_mask);
        sigaction(SIGCHLD, &act, NULL);

        //注册完信号捕捉以后，解除阻塞
        sigprocmask(SIG_UNBLOCK, &set, NULL);

        while(1){
            printf("parent process pid: %d\n", getpid());
            sleep(2);
        }
    }else if(pid == 0){
        printf("child process pid : %d\n", getpid());
    }

    return 0;
}