#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main(){

    int num = 10;
    //创建子进程
    pid_t pid = fork();
    //判断是子进程还是父进程
    if(pid > 0){
        printf("pid: %d\n", pid);
        printf("I am parent process, pid : %d, ppid : %d\n", getpid(), getppid());

        printf("parent num: %d\n", num);
        num += 10;
        printf("parent num += 10: %d\n", num);


    }
    else if(pid == 0){
        printf("I am child process, pid: %d, ppid: %d\n", getpid(), getppid());

        printf("child num: %d\n", num);
        num += 100;
        printf("child num += 100: %d\n", num);

    }

    for(int i = 0; i < 5; i++){
        printf("i : %d, pid: %d\n", i, getpid());
        sleep(2);
    }

 
    return 0;
}