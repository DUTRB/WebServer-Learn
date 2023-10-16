#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>

int main(){

    int ret = mkfifo("fifo1", 0664);
    if(ret == -1){
        perror("makefifo");
        exit(0);
    }

    return 0;
}