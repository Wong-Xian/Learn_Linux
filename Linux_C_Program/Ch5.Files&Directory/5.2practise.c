#include<sys/stat.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>

int main()
{
    struct stat s;
    int ret;

    if (-1==(ret=stat("./test_file",&s)))
    {
        perror("stat error");
        exit(-1);
    }

    printf("(1)获取文件的 inode 节点编号以及文件大小，并将它们打印出来。\n");
    printf("inode: %ld\n",s.st_ino);
    printf("size of file: %ld Bytes\n",s.st_size);

    printf("(2)获取文件的类型，判断此文件对于其它用户（Other）是否具有可读可写权限。\n");
    if (s.st_mode & (S_IROTH | S_IWOTH))
    {
        printf("\t对其他用户有可读可写权限\n");
    }
    else if (s.st_mode & S_IROTH)
    {
        printf("\t对其他用户有可读权限\n");
    }
    else if (s.st_mode & S_IWOTH)
    {
        printf("\t对其他用户有可写权限\n");
    }
    else
    {
        printf("\t对其他用户没有可读可写权限\n");
    }
    
    printf("(3)获取文件的时间属性\n");
    
    exit(0);
}