#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

void * callback(void * arg){
    printf("child threadID : %ld\n", pthread_self());
    //sleep(3);
    //return NULL; //等价与pthread_exit(NULL)
    int value = 10;
    pthread_exit((void *)&value);
}

int main(){
    //创建一个线程
    pthread_t tid;
    int ret = pthread_create(&tid, NULL, callback, NULL);

    if(ret != 0){
        char *errstr = strerror(ret);
        printf("error: %s", errstr);
    }

    //主线程
    for(int i = 0; i < 5; i++){
        printf("%d\n", i);
    }
    //此时的tid应该与子线程函数中的threadID一致
    printf("tid: %ld, main threadID : %ld\n", tid, pthread_self());
    

    int *thread_retval;
    ret = pthread_join(tid, (void **)&thread_retval);
    if(ret != 0){
        char *errstr = strerror(ret);
        printf("error: %s", errstr);
    }

    printf("exit_val: %d\n", *thread_retval);

    printf("回收子线程结束。\n");



    //让主线程退出
    pthread_exit(NULL);

    return 0;   
}