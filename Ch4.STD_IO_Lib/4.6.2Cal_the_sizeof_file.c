#include<stdio.h>
#include<stdlib.h>

int main()
{
    // 定义变量
    FILE* fp;
    long cur;

    // 打开文件（只读）
    if (NULL == (fp=fopen("./4.5.1Format_IO_fwrite.c","r")))
    {
        perror("fopen error");
        exit(-1);
    }

    // 偏移量设为启始
    if (-1 == fseek(fp, 0, SEEK_SET))
    {
        perror("fseek error");
        fclose(fp);
        exit(-1);
    }

    // 偏移量设为末尾
    if (-1 == fseek(fp, 0, SEEK_END))
    {
        perror("fseek error");
        fclose(fp);
        exit(-1);
    }

    // 读出偏移量
    if (-1 == (cur = ftell(fp)))
    {
        perror("ftell error");
        fclose(fp);
        exit(-1);
    }

    // 计算并输出文件大小
    printf("文件大小为：%ld字节\n", cur);

    fclose(fp);
    exit(0);
}