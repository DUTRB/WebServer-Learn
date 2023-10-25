#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main(){

    //1. 获取一个共享内存
    int shmid  = shmget(10, 0, IPC_CREAT);
    printf("shmid: %d\n", shmid);

    //2. 和当前进程关联
    void * ptr = shmat(shmid, NULL, 0);

    //3. 读数据
    printf("%s\n", (char *)ptr);

    printf("按任意键继续...\n");
    getchar();

    //4. 解除关联
    shmdt(ptr);

    //删除共享内存
    shmctl(shmid, IPC_RMID, NULL);
    

    return 0;
}