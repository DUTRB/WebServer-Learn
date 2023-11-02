#define _DEFAULT_SOURCE
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>


//创建共享数据
int num = 1;
//pthread_mutex_t mutex;
//创建读写锁
pthread_rwlock_t rwlock;


void * writeNum(void * arg){
    while(1){
        //pthread_mutex_lock(&mutex);
        pthread_rwlock_wrlock(&rwlock);
        num++;
        printf("++write, tid: %ld, num: %d\n", pthread_self(), num);
        //pthread_mutex_unlock(&mutex);
        pthread_rwlock_unlock(&rwlock);

        usleep(100);
    }
    return NULL;
}
void * readNum(void * arg){
    while(1){
        usleep(100);
        //pthread_mutex_lock(&mutex);
        pthread_rwlock_rdlock(&rwlock);
        printf("==read, tid: %ld, num: %d\n", pthread_self(), num);
        //pthread_mutex_unlock(&mutex);
        pthread_rwlock_unlock(&rwlock);

    }
    return NULL;
}

int main(){

    //pthread_mutex_init(&mutex, NULL);
    pthread_rwlock_init(&rwlock, NULL);
    //创建3个写线程，5个读线程
    pthread_t wtids[3], rtids[5];
    for(int i = 0; i < 3; i++){
        pthread_create(&wtids[i], NULL, writeNum, NULL);
    }

    for(int i = 0; i < 5; i++){
        pthread_create(&rtids[i], NULL, readNum, NULL);
    }

    //设置线程分离
    for(int i = 0; i < 3; i++){
        pthread_detach(wtids[i]);
    }

    for(int i = 0; i < 5; i++){
        pthread_detach(rtids[i]);
    }
    //主线程退出，不影响子线程
    pthread_exit(NULL);

    //pthread_mutex_destroy(&mutex);
    pthread_rwlock_destroy(&rwlock);

    return 0; 
}