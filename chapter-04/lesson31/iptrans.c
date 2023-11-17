#include <stdio.h>
#include <arpa/inet.h>

int main(){

    //创建一个ip字符串，点分十进制的IP地址字符串

    char buf[] = "192.168.1.4";

    unsigned int num = 0;
    //将点分十进制的IP字符串转换成网络字节序的整数
    inet_pton(AF_INET, buf, &num);

    unsigned char * p = (unsigned char *)&num;

    printf("%d %d %d %d\n", *p, *(p+1), *(p+2),*(p+3));

    //将网络字节序的IP整数转换成点分十进制的IP字符串
    char ip[16] = "";

    const char * str = inet_ntop(AF_INET, &num, ip, 16);
    
    printf("%s\n", str);

    return 0;
}