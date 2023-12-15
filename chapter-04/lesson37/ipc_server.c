#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/un.h>

int main(){

    int lfd = socket(AF_LOCAL, SOCK_STREAM, 0);
    if(lfd == -1){
        perror("socket");
        exit(-1);
    }

    struct sockaddr_un addr;
    addr.sun_family = AF_LOCAL;
    strcpy(addr.sun_path, "server.sock");
    int ret = bind(lfd, (struct sockaddr *)&addr, sizeof(addr));
    if(ret == -1){
        perror("bind");
        exit(-1);
    }

    ret = listen(lfd, 100);

    struct sockaddr_un cliaddr;
    int len = sizeof(cliaddr);
    int cfd = accept(lfd, (struct sockaddr *)&cliaddr, &len);

    printf("client socket filename: %s\n ", cliaddr.sun_path);
    
    while(1){
        char buf[128];
        int len = recv(cfd, buf, sizeof(buf), 0);
        if(len == -1){
            perror("recv");
            exit(-1);
        }else if(len == 0){
            printf("client closed...");
        }else{
            printf("client say : %s\n", buf);
            send(cfd, buf, len, 0);
        }
    }

    close(cfd);
    close(lfd);

    return 0;
}