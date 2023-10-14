#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
//wait()函数功能，回收指定进程号的子进程，可以设置是否阻塞

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
            sleep(1);

            printf("parent, pid = %d\n", getpid());

            int st;

            int ret = waitpid(-1, &st, WNOHANG);

            if(ret == -1){
                break;
            }

            if(ret == 0){
                continue;
            }

            else if(ret > 0){
                if(WIFEXITED(st)){
                //是否正常退出
                    printf("退出的状态码：%d\n", WEXITSTATUS(st));
                }

                if(WIFSIGNALED(st)){
                    printf("被哪个信号干掉了：%d\n", WTERMSIG(st));
                }

                
            }
            printf("child die, pid = %d\n", ret);
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