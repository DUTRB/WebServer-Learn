 #define _DEFAULT_SOURCE
 #include <stdio.h>
 #include <stdlib.h>
 #include <signal.h>
 #include <unistd.h>

 int main(){

    sigset_t set;
    sigemptyset(&set);

    //将2 3号信号加入到信号集中
    sigaddset(&set, SIGINT);
    sigaddset(&set, SIGQUIT);

    //修改内核中的阻塞信号集
    sigprocmask(SIG_BLOCK, &set, NULL);

    int num = 0;
    while(1){
        num++;

        //获取当前未决信号集中的数据
        sigset_t pendingset;
        sigemptyset(&pendingset);
        sigpending(&pendingset);

        for(int i = 1; i <= 32; i++){
            if(sigismember(&pendingset, i) == 1)
                printf("1");
            else if(sigismember(&pendingset, i) == 0)
                printf("0");
            else
            {
                perror("sigismembe\n");
                exit(0);
            }
        }

        printf("\n");
        sleep(1);
        if(num == 10){
            sigprocmask(SIG_UNBLOCK, &set, NULL);
        }
    }
    return 0;
 }