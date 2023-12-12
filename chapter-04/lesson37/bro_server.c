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

    //2. set
    int op = 1;
    setsockopt(fd, SOL_SOCKET, SO_BROADCAST, &op, sizeof(op));

    struct sockaddr_in cliaddr;
    cliaddr.sin_family = AF_INET;
    cliaddr.sin_port = htons(9999);
    inet_pton(AF_INET, "192.168.160.255", &cliaddr.sin_addr.s_addr);
    //cliaddr.sin_addr.s_addr = INADDR_ANY;

    int num = 0;
    while(1){
        char sendbuf[128];

        sprintf(sendbuf, "hello, client...%d\n", num++);

        sendto(fd, sendbuf, strlen(sendbuf) + 1, 0, (struct sockaddr *)&cliaddr, sizeof(cliaddr));

        printf("data : %s\n", sendbuf);
    
        sleep(1);
       
    }
    close(fd);
    return 0;
}