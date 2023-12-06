#define _DEFAULT_SOURCE
#include <stdio.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/select.h>

int main(){


    //创建socket
    int lfd = socket(PF_INET, SOCK_STREAM, 0);
    struct sockaddr_in saddr;
    saddr.sin_port = htons(9999);
    saddr.sin_family = AF_INET;
    saddr.sin_addr.s_addr = INADDR_ANY;

    //绑定
    bind(lfd, (struct sockaddr *)&saddr, sizeof(saddr));

    //监听
    listen(lfd, 8);

    //创建一个fd_set集合，存放的是需要检测的文件描述符
    fd_set rdset, tmp;
    FD_ZERO(&rdset);
    FD_SET(lfd, &rdset);
    int maxfd = lfd;

    while(1){
        //交给内核使用的是tmp集合，不会影响rdset
        tmp = rdset;

        //调用select系统函数，让内核帮助检测哪些文件描述符有数据
        int ret = select(maxfd + 1, &tmp, NULL, NULL, NULL);
        if(ret == -1){
            perror("select");
            exit(-1);
        }else if(ret == 0){
            continue;
        }else if(ret > 0){
            //检测到文件描述符改变 只返回了检测到的个数
            //判断监听文件描述符 表示是否有新的客户端连接进来
            if(FD_ISSET(lfd, &tmp)){
                struct sockaddr_in cliaddr;
                int len = sizeof(cliaddr);
                //获得新的文件描述符
                int cfd = accept(lfd, (struct sockaddr *)&cliaddr, &len);
                //添加进集合中  更新最大的文件描述符
                FD_SET(cfd, &rdset);
                maxfd = maxfd > cfd ? maxfd : cfd;
            }
            //遍历集合
            for(int i = lfd + 1; i <= maxfd; i++){
                if(FD_ISSET(i, &tmp)){
                    //说明这个文件描述符对应的客户端发来了数据
                    char buf[1024] = {0};
                    int len = read(i, buf, sizeof(buf));
                    if(len == -1){
                        perror("read");
                        exit(-1);
                    }else if(len == 0){
                        printf("client closed...");
                        close(i);
                        FD_CLR(i, &rdset);
                    }else if(len > 0){
                        printf("read buf: %s\n", buf);
                        write(i, buf, strlen(buf) + 1);
                    }
                }
            }
        }

    }
    close(lfd);
    return 0;
}