#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//创建一个互斥量
pthread_mutex_t mutex;
//创建条件变量
pthread_cond_t cond;

struct Node{
    int num;
    struct Node *next;
};

//头结点
struct Node* head = NULL;


void * producer(void * arg){
    //不断地创建新链表添加到节点中
    while(1){
        pthread_mutex_lock(&mutex);

        struct Node * newNode = (struct Node *)malloc(sizeof(struct Node));
        newNode->next = head;
        head = newNode;
        newNode->num = rand() % 1000;
        printf("add node, num = %d, tid : %ld\n", newNode->num, pthread_self());

        //只要生产了一个 就通知消费者消费
        pthread_cond_signal(&cond);

        pthread_mutex_unlock(&mutex);
        
        usleep(100);
    }
    return NULL;
}

void * customer(void * arg){
    while(1){
        pthread_mutex_lock(&mutex);

        //保存头结点的指针
        struct Node * tmp = head;

        //判断是否有数据
        if(head != NULL){
            head = head->next;
            printf("del node, num : %d, tid : %ld\n", tmp->num, pthread_self());
            free(tmp);

            pthread_mutex_unlock(&mutex);
            usleep(100);
        }
        else{
            //没有数据 需要等待
            //当这个函数调用阻塞后，会对互斥锁进行解锁
            //不阻塞向下执行后，会继续上锁
            pthread_cond_wait(&cond, &mutex);
            pthread_mutex_unlock(&mutex);
        }
    }
    return NULL;
}


int main(){

    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond, NULL);

    //创建5个生产者线程，和5个消费者线程
    pthread_t ptids[5], ctids[5];

    for(int i = 0; i < 5; i++){
        pthread_create(&ptids[i], NULL, producer, NULL);
        pthread_create(&ctids[i], NULL, customer, NULL);
    }

    for(int i = 0; i < 5; i++){
        pthread_detach(ptids[i]);
        pthread_detach(ctids[i]);
    }

    while(1){
        sleep(10);
    }
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);
    pthread_exit(NULL);


    return 0;
}

