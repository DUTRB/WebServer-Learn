#include <stdio.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>

int main(){

    pid_t pid = fork();

    if(pid == 0){
        for(int i = 0; i < 10; i++){
            sleep(1);
            printf("child process\n");
        }
    }
    else if(pid > 0){
        printf("parent process\n");
        sleep(2);
        printf("kill child process now\n");
        kill(pid, SIGINT);

        
    }
    return 0;
}