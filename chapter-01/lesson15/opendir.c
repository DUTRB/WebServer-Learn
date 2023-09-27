#define _DEFAULT_SOURCE
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>


//读取目录下所有普通文件的个数
int getfileNum(const char* path){
    //打开目录
    DIR *dir = opendir(path);
    if(dir == NULL)
    {
        perror("opendir");
        exit(0);
    }

    struct dirent *ptr;
    
    int total = 0;
    while((ptr = readdir(dir)) != NULL){
        char *dname = ptr->d_name;
        if(strcmp(dname, ".") == 0 || strcmp(dname, "..") == 0){
            continue;
        }
        //判断是否是普通目录还是文件
        if(ptr->d_type == DT_DIR){
            char newpath[256];
            sprintf(newpath, "%s/%s", path, dname);
            total += getfileNum(newpath);
        }
        if(ptr->d_type == DT_REG){
            total++;
        }
    }
    closedir(dir);
    return total;
    
}


int main(int argc, char* argv[1])
{
    if(argc < 2){
        printf("%s path\n", argv[0]);
        return -1;
    }
    int num = getfileNum(argv[1]);
    printf("filenum is %d\n", num);

    return 0;
}