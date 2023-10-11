#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(){
    pid_t pid;
    for(int i = 0; i < 5; i++){
        pid = fork();
        if(pid == 0){
            break;
        }
    }
    if(pid > 0){
        while(1){
            printf("parent, pid = %d\n", getpid());

            int st;

            int ret = wait(&st);

            if(ret == -1){
                break;
            }

            if(WIFEXITED(st)){
                //是否正常退出
                printf("退出的状态码：%d\n", WEXITSTATUS(st));
            }

            if(WIFSIGNALED(st)){
                printf("被哪个信号干掉了：%d\n", WTERMSIG(st));
            }

            printf("child die, pid = %d\n", getpid());

            sleep(1);   
        }
    }
    else if(pid == 0){
        while(1){
            printf("child, pid = %d\n", getpid());
            sleep(1);
        }   
        exit(0);    
        
    }

    return 0;
}