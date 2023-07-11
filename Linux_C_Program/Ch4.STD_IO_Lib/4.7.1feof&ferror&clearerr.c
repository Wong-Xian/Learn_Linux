#include<stdio.h>
#include<stdlib.h>

int main()
{
    // 定义变量
    FILE* fp=NULL;
    char buf[100]={0};
    

    // 打开文件
    if (NULL == (fp=fopen("./test_file","r")))
    {
        perror("fopen error");
        exit(-1);
    }
    printf("open file success!\n");

    // 读取到文件末尾，造成feof置位
    printf("reading file...\n");
    if (sizeof(buf) > fread(buf, 1, sizeof(buf), fp))
    {
        if (feof(fp))
        {
            printf("reach the end of file!\n");
        }
        else
        {
            perror("fread error");
            fclose(fp);
            exit(-1);
        }
    }

    // 尝试造成ferror置位
    if (ferror(fp))
    {
        printf("ferror: file error flag was set!\n");
    }

    // 调用clearerr
    printf("clearing error flag...\n");
    clearerr(fp);

    if (!feof(fp))
    {
        printf ("eof flag cleared!\n");
    }

    // 再次造成feof置位
    printf("reading file...\n");
    if (sizeof(buf) > fread(buf, 1, sizeof(buf), fp))
    {
        if (feof(fp))
        {
            printf("reach the end of file!\n");
        }
        else
        {
            perror("fread error");
            fclose(fp);
            exit(-1);
        }
    }

    // 利用fseek清除feof置位
    if (-1 == fseek(fp, 0, SEEK_END))
    {
        perror("fseek error");
        fclose(fp);
        exit(-1);
    }
    if (feof(fp))
    {
        printf("eof flag still set! wired!\n");
    }
    else
    {
        printf("eof flag not set!\n");
    }

    // 关闭文件，退出程序
    fclose(fp);
    exit(0);
}

/*
Sum:
    feof()可以判断读写标志符是否在文档末尾。
    21到33行的内容，是fread()结合feof()判断读取文件内容是否成功。
    通过clearerr()和fseek()可以清空feof标志
*/