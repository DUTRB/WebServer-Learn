#include <stdio.h>
#include<pthread.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

//子线程执行函数
void * callback(void * arg){
    printf("This is a child thread.\n");
    printf("arg value: %d\n", *(int *)arg);
    return NULL;
}

int main(){
    //1. 创建一个子线程
    pthread_t tid;
    int num = 10;
    int ret = pthread_create(&tid, NULL, callback, (void *)&num);

    if(ret != 0){
        char * errstr = strerror(ret);
        printf("error: %s\n", errstr);
    }

    printf("wait child thread...\n");
    sleep(1);

    return 0;
}