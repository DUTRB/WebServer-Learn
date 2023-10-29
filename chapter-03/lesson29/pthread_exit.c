#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

void * callback(void * arg){
    printf("child threadID : %ld\n", pthread_self());
    return NULL;

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
    printf("tid: %ld, main threadID : %ld\n", tid, pthread_self());
    
    //让主线程退出
    pthread_exit(NULL);

    return 0;   
}