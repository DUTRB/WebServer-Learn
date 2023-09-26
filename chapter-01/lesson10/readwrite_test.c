#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main(){
    //1.使用open函数打开source.txt文件
    int source_fd = open("source.txt", O_RDONLY);
    if(source_fd == -1){
        perror("open_error");
        return -1;
    }
    //2.创建一个新的文件（拷贝文件）
    int copy_fd = open("copy.txt", O_WRONLY | O_CREAT, 0777);
    if(copy_fd == -1){
        perror("copy_error");
        return -1;
    }
    //3. 频繁的读写操作
    char buf[1024] = {0};
    int len = 0;
    while((len = read(source_fd, buf, sizeof(buf))) > 0){
        write(copy_fd, buf, len);
    }

    close(source_fd);
    close(copy_fd);

    return 0;
}