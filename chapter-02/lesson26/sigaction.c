#define _DEFAULT_SOURCE
#include <signal.h>
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>

void myAlarm(int num){
    printf("捕捉到了信号的编号：%d\n", num);
    printf("........\n");
}

int main(){

    struct sigaction act;
    act.sa_flags = 0;
    act.sa_handler = myAlarm;
    sigemptyset(&act.sa_mask);
    
    //注册信号捕捉
    sigaction(SIGALRM, &act, NULL);

    __sighandler_t flag = signal(SIGALRM, myAlarm);
    if (flag == SIG_ERR)
    {
        perror("signal");
        exit(0);
    }

    struct itimerval new_value;
    //间隔时间
    new_value.it_interval.tv_sec = 2;
    new_value.it_interval.tv_usec = 0;
    //延迟时间
    new_value.it_value.tv_sec = 3;
    new_value.it_value.tv_usec = 0;

    int ret = setitimer(ITIMER_REAL, &new_value, NULL);
    printf("start counting...\n");
    if(ret == -1){
        perror("setitimer");
        exit(0);
    }
    getchar();//阻塞状态    

    return 0;
}