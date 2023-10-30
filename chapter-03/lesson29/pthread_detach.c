#include <stdio.h> 
#include <pthread.h>
#include <string.h>
#include <unistd.h>

void * callback(void * arg){
    printf("child thread id: %ld\n", pthread_self());
    return NULL;
}

int main(){
    
    //创建一个子线程
    pthread_t tid;
    int ret = pthread_create(&tid, NULL, callback, NULL);
    if(ret != 0){
        char * errstr = strerror(ret);
        printf("error: %s\n", errstr);
    }

    //输出主线程和子线程ID
    printf("tid: %ld, main thread id: %ld\n", tid, pthread_self());


    //设置子线程分离
    //子线程和分离后，子线程结束时对应的资源就不需要主线程释放
    pthread_detach(tid);

    //设置分离后，对分离的子线程进行连接pthread_join()
    //会报错
    // ret = pthread_join(tid, NULL);
    // if(ret != 0){
    //     char * errstr = strerror(ret);
    //     printf("error-join: %s\n", errstr);
    // }

    pthread_exit(NULL);
    return 0;
}