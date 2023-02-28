#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>


int main(void)
{
    int fd1, fd2;
    int ret;


    /* 创建新文件 test_file 并打开 */
    fd1 = open("./test_file", O_RDWR | O_CREAT | O_EXCL,
                S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    if (-1 == fd1)
    {
        perror("open error");
        exit(-1);
    }


    /* 复制文件描述符 */
    fd2 = dup2(fd1, 100);   // 指定新的文件描述符fd2为100
    if (-1 == fd2)
    {
        perror("dup error");
        ret = -1;
        goto err1;
    }
    printf("fd1: %d\nfd2: %d\n", fd1, fd2);// 输出fd1和fd2
    ret = 0;

    close(fd2);
err1:
    /* 关闭文件 */
    close(fd1);
    exit(ret);
}