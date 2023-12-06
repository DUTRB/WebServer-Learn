#include <stdio.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main(){

    //1. 创建套接字
    int fd = socket(PF_INET, SOCK_STREAM, 0);

    //2. 连接服务器
    struct sockaddr_in serveraddr;
    serveraddr.sin_family = AF_INET;
    inet_pton(AF_INET, "127.0.0.1", &serveraddr.sin_addr.s_addr);
    serveraddr.sin_port = htons(9999);
    int ret = connect(fd, (struct sockaddr *)&serveraddr, sizeof(serveraddr));
    if(ret == -1){
        perror("connect");
        exit(-1);
    }

    //3. 通信
    //给服务端发送数据
    
    int num = 0;
    while (1)
    {
        char sendBuf[1024] = {0};

        sprintf(sendBuf, "send data: %d\n", num++);
        //给服务端发送数据
        write(fd, sendBuf, strlen(sendBuf) + 1);
        
        int len = read(fd, sendBuf, sizeof(sendBuf));
        if(len == -1){
            perror("read");
            exit(-1);
        }else if(len > 0){
            printf("recv server data: %s\n", sendBuf);
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