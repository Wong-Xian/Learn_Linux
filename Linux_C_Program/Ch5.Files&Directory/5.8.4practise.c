/*
2023年3月15日

要求：
    打开一个目录、并将目录下的所有文件的名称以及其对应 inode 编号打印出来。
*/

#include <sys/types.h>
#include <dirent.h>

#include<stdio.h>
#include<stdlib.h>

#define PATH "./"

int main()
{
    DIR* dirpt;
    struct dirent* d1;

    if (NULL == (dirpt=opendir(PATH)))
    {
        perror("opendir error");
        exit(-1);
    }

    while (NULL!=(d1=readdir(dirpt)))
    {
        /* code */
        printf("inode: %ld\n",d1->d_ino);
        printf("file name: %s\n\n",d1->d_name);
    }
    
    if (-1 == closedir(dirpt))
    {
        perror("close dir error");
        exit(-1);
    }

    printf("done!\n");
    exit(0);
}
