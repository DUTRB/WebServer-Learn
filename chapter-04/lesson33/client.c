#include <stdio.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main(){

    //1. 创建套接字
    int fd = socket(AF_INET, SOCK_STREAM, 0);

    //2. 连接服务器
    struct sockaddr_in serveraddr;
    serveraddr.sin_family = AF_INET;
    inet_pton(AF_INET, "192.168.160.128", &serveraddr.sin_addr.s_addr);
    serveraddr.sin_port = htons(9999);
    int ret = connect(fd, (struct sockaddr *)&serveraddr, sizeof(serveraddr));
    if(ret == -1){
        perror("connect");
        exit(-1);
    }

    //3. 通信
    //给服务端发送数据
    char recvBuf[1024] = {0};
    int i = 0;
    while (1)
    {
        sprintf(recvBuf, "data: %d\n", i++);
        //给服务端发送数据
        write(fd, recvBuf, strlen(recvBuf));
        
        int len = read(fd, recvBuf, sizeof(recvBuf));
        if(len == -1){
            perror("read");
            exit(-1);
        }else if(len > 0){
            printf("recv server data: %s\n", recvBuf);
        }else if(len == 0){ //客户端断开连接
            printf("server closed...\n");
            break;
        }

        sleep(1);
    }
    //关闭连接
    close(fd);
    return 0;
}