#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


struct Node{
    int num;
    struct Node *next;
};

//头结点
struct Node* head = NULL;


void * producer(void * arg){
    //不断地创建新链表添加到节点中
    while(1){
        struct Node * newNode = (struct Node *)malloc(sizeof(struct Node));
        newNode->next = head;
        head = newNode;
        newNode->num = rand() % 1000;
        printf("add node, num = %d, tid : %ld\n", newNode->num, pthread_self());
        usleep(100);
    }
    return NULL;
}

void * customer(void * arg){
    while(1){
        //保存头结点的指针
        struct Node * tmp = head;
        head = head->next;
        printf("del node, num : %d, tid : %ld\n", tmp->num, pthread_self());
        free(tmp);
        usleep(100);
    }
    return NULL;
}



int main(){

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

    pthread_exit(NULL);


    return 0;
}