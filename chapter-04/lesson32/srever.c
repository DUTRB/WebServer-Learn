#include <stdio.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

int main(){

    //1. 创建socket
    int lfd = socket(AF_INET, SOCK_STREAM, 0);

    //2. 绑定
    struct sockaddr_in saddr;
    saddr.sin_family = AF_INET;
    inet_pton(AF_INET, "192.168.160.128", saddr.sin_addr.s_addr);
    saddr.sin_port = htons(9999);
    int ret = bind(lfd, (struct sockaddr *)&saddr, sizeof(saddr));
    if(ret == -1){
        perror("bind");
        exit(-1);
    }

    //3. 监听
    ret = listen(lfd, 8);
    if(ret == -1){
        perror("liston");
        exit(-1);
    }

    //4. 接收客户端连接
    struct sockaddr_in clientaddr;
    socklen_t len = sizeof(clientaddr);
    int cfd = accept(lfd, (struct sockaddr *)&clientaddr, &len);
    if(cfd == -1){
        perror("accept");
        exit(-1);
    }
    //输出客户端的信息
    char clientIP[16];
    inet_ntop(AF_INET, &clientaddr.sin_addr.s_addr, clientIP, sizeof(clientIP));
    unsigned short clientPort = ntohs(clientaddr.sin_port);
    printf("client IP is %s, port : %d\n", clientIP, clientPort);

    //5. 获取客户端数据
    char recvBuf[1024] = {0};
    int len = read(cfd, recvBuf, sizeof(recvBuf));
    if(len == -1){
        perror("read");
        exit(-1);
    }else if(len > 0){
        printf("recv client data: %d\n");
    }else if(len == 0){ //客户端断开连接
        printf("client closed...");
    }

    //给客户端发送数据
    char * data = "Hello, I am server";
    write(cfd, data, strlen(data));

    //关闭文件描述符
    close(cfd);
    close(lfd);

    return 0;
}