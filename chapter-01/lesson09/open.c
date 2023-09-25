/*
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

//打开一个已经存在的文件
int open(const char *pathname, int flags);

//创建一个新文件
int open(const char *pathname, int flags, mode_t mode);

#include <stdio.h>
void perror(const char *s);

*/

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main(){
    int fd = open("a.txt", O_RDONLY);
    if(fd == -1){
        perror("open");
    }
    close(fd);
    return 0;
}