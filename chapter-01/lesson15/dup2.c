#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
int main()
{
    int fd = open("1.txt", O_RDWR | O_CREAT, 0664);
    if (fd == -1)
    {
        perror("open");
        return -1;
    }

    int fd1 = open("2.txt", O_RDWR | O_CREAT, 0664);
    if (fd1 == -1)
    {
        perror("open");
        return -1;
    }

    printf("fd：%d\nfd1：%d\n", fd, fd1);

    int fd2 = dup2(fd, fd1);
    if (fd2 == -1)
    {
        perror("dup2");
        return -1;
    }

    // 通过fd1去写数据，实际操作的是1.txt，而不是2.txt
    char *str = "hello, dup2";
    int len = write(fd1, str, strlen(str));

    printf("fd：%d\nfd1：%d\nfd2：%d\n", fd, fd1, fd2);

    close(fd);
    close(fd1);
    // close(fd2); fd1、fd2文件描述符相同可选一个关

    return 0;
}
