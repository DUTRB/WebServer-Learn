#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

int main(){

    //1. socket 
    int fd = socket(PF_INET, SOCK_DGRAM, 0);
    if(fd == -1){
        perror("socket");
        exit(-1);
    }

    //2. bind
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(9999);
    addr.sin_addr.s_addr = INADDR_ANY;
    //inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr.s_addr);

    int ret = bind(fd, (struct sockaddr *)&addr, sizeof(addr));
    if(ret == -1){
        perror("bind");
        exit(-1);
    }

    while(1){
        char buf[128];
        
        int num = recvfrom(fd, buf, sizeof(buf), 0, NULL, NULL);
        printf("server say : %s\n", buf);
    }

    close(fd);
    return 0;
}