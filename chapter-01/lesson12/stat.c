#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main(){
    struct stat statbuf;
    int ret = stat("hello.txt", &statbuf);
    if(ret == -1){
        perror("open");
        return -1;
    }
    printf("smode: %d\n", statbuf.st_mode);

    return 0;
}