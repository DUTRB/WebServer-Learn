#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>

int main(){
    //int ret = access("a.txt", F_OK);
    int ret = chmod("a.txt", 0777);
    if(ret == -1){
        perror("chmod");
        return -1;
    }
    printf("Change is over!\n");

    return 0;
}