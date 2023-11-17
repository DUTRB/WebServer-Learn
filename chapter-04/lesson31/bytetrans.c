#include <stdio.h>
#include <arpa/inet.h>


int main(){

    union 
    {
        short value;
        char bytes[sizeof(short)];
    }test;

    test.value = 0x0102;
    if((test.bytes[0] == 1) && (test.bytes[1] == 2)){
        printf("大端字节序\n");
    }
    else if((test.bytes[0] == 2) && (test.bytes[1] == 1)){
        printf("小端字节序\n");
    }else{
        printf("未知\n");
    }


    //htons 转换端口
    unsigned short a = 0x0102;
    printf("a: %x\n", a);
    unsigned short b = htons(a);
    printf("b: %x\n", b);

    //htonl 转换IP
    char buf[4] = {192, 168, 1, 100};
    int num = *(int *)buf;
    int res = htonl(num);
    unsigned char *p = (char *)&res;

    printf("%d %d %d %d \n", *p, *(p+1), *(p+2),*(p+3));

    //ntohs
    unsigned short a1 = 0x0102;
    printf("a1: %x\n", a1);
    unsigned short b1 = ntohs(a1);
    printf("b1: %x\n", b1);

    //ntohl
    char buf1[4] = {192, 168, 1, 100};
    int num1 = *(int *)buf1;
    int res1 = ntohl(num1);
    unsigned char *p1 = (char *)&res1;
    printf("%d %d %d %d \n", *p1, *(p1+1), *(p1+2),*(p1+3));


    return 0;
}