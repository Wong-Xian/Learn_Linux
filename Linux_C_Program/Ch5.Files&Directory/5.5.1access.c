#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define PATH "./test_file"

int main()
{
    if (0==access(PATH,F_OK))
    {
        printf("文件存在！\n");
        if (0==access(PATH, R_OK))
            printf("文件可读\n");
        else
            printf("文件不可读\n");
        if (0==access(PATH, W_OK))
            printf("文件可写\n");
        else
            printf("文件不可写\n");
        if (0==access(PATH, X_OK))
            printf("文件可执行\n");
        else
            printf("文件不可执行\n");

        exit(0);
    }
    else
    {
        printf("文件不存在！\n");
        exit(0);
    }
}