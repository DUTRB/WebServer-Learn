#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main(){
    //获取当前的工作目录
    char buf[128];
    getcwd(buf, sizeof(buf));
    printf("当前的工作目录为：%s\n", buf);

    //修改工作目录
    int ret = chdir("/home/void/Documents/C++_webServer/chapter-01/lesson14-change");
    if(ret == -1){
        perror("chdir");
        return -1;
    }
    int fd = open("chdir.txt", O_CREAT | O_RDWR, 0644);
    if(fd == -1){
        perror("open");
        return -1;
    }
    close(fd);

    char buf_2[128];
    getcwd(buf_2, sizeof(buf_2));
    printf("当前新的工作目录为：%s\n", buf_2);


    return 0;
}