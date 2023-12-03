#define _DEFAULT_SOURCE
#include <stdio.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

struct sockInfo{
    int fd;  //通信的文件描述符
    pthread_t tid;  //线程号
    struct sockaddr_in addr;

};

struct sockInfo sockinfos[128];

void * working(void * arg){
    struct sockInfo * pinfo = (struct sockInfo *) arg;
    //子线程和客户端通信
    char cliIp[16];
    inet_ntop(AF_INET, &pinfo->addr.sin_addr.s_addr, cliIp, sizeof(cliIp));
    unsigned short cliPort = ntohs(pinfo->addr.sin_port);

    printf("client ip is : %s, prot is %d\n", cliIp, cliPort);

    //接收从客户端发来的信息
    char recvBuf[1024] = {0};
    while (1)
    {
        int len = read(pinfo->fd, &recvBuf, sizeof(recvBuf));
        if(len == -1){
            perror("read");
            exit(-1);
        }else if(len > 0){
            printf("recv client %s\n", recvBuf);
        }else if(len == 0){
            printf("client closed...");
            break;
        }

        write(pinfo->fd, recvBuf, sizeof(recvBuf));
    }
    close(pinfo->fd);
    return NULL;
}

int main(){

    //创建socket
    int lfd = socket(PF_INET, SOCK_STREAM, 0);
    if(lfd == -1){
        perror("socket");
        exit(-1);
    }
    //绑定
    struct sockaddr_in saddr;
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(9999);
    //inet_pton(AF_INET, "192.168.160.128", &saddr.sin_addr.s_addr);
    saddr.sin_addr.s_addr = INADDR_ANY;

    int ret = bind(lfd, (struct sockaddr *)&saddr, sizeof(saddr));
    if(ret == -1){
        perror("bind");
        exit(-1);
    }

    //监听
    ret = listen(lfd, 128);
    if(ret == -1){
        perror("listen");
        exit(-1);
    }

    //初始化结构体
    int max = sizeof(sockinfos) / sizeof(sockinfos[0]);
    for(int i = 0; i < max; i++){
        bzero(&sockinfos[i], sizeof(sockinfos[i]));
        sockinfos->fd = -1;
        sockinfos->tid = -1;
    }

    //循环等待客户端连接，一旦一个客户端连接进来，就创建一个子线程进行通信
    while(1){

        //接受连接
        struct sockaddr_in cliaddr;
        int len = sizeof(cliaddr);
        int cfd = accept(lfd, (struct sockaddr *)&cliaddr, &len);

        struct sockInfo * pinfo;
        for(int i = 0; i < max; i++){
            //从这个数组中找到一个可以用的sockInfo元素
            if(sockinfos[i].fd == -1){
                pinfo = &sockinfos[i];
                break;
            }
            if(i == max - 1){
                sleep(1);
                i--;
            }
        }

        pinfo->fd = cfd;
        memcpy(&pinfo->addr, &cliaddr, len);
        
        //创建子线程
        pthread_create(&pinfo->tid, NULL, working, pinfo);

        pthread_detach(pinfo->tid);

    }

    close(lfd);
    return 0;
}