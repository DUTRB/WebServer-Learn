#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
    printf("hello\n");
    printf("world");


    //exit(0);
    _exit(0);

    return 0;
}