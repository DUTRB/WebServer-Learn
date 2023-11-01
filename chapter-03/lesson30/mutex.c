#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

//全局变量, 线程共享
int ticket = 1000;

//创建一个互斥量
pthread_mutex_t mutex;


void * sellTicket(void * arg){

    //卖票 
    while(1){

        //加锁
        pthread_mutex_lock(&mutex);

        if(ticket > 0){
            //usleep(6000);
            printf("%ld 正在卖第 %d 张门票\n", pthread_self(), ticket);
            ticket--;
        }else{
            //解锁
            pthread_mutex_unlock(&mutex);
            break;
        }
        
         //解锁
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

int main(){

    //初始化互斥量
    pthread_mutex_init(&mutex, NULL);

    //创建3个子线程
    pthread_t tid1;
    pthread_t tid2; 
    pthread_t tid3;
    pthread_create(&tid1, NULL, sellTicket, NULL);
    pthread_create(&tid2, NULL, sellTicket, NULL);
    pthread_create(&tid3, NULL, sellTicket, NULL);

    //回收子线程的资源，阻塞函数
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    pthread_join(tid3, NULL);


    // 退出主线程
    pthread_exit(NULL);

    //销毁互斥量
    pthread_mutex_destroy(&mutex);

    return 0;
}
