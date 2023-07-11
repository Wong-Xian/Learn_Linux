#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>


int main(void)
{
    int fd;
    int ret;
    int flag;


    /* 打开文件 test_file */
    fd = open("./test_file", O_RDWR);
    if (-1 == fd)
    {
        perror("open error");
        exit(-1);
    }


    /* 获取文件状态标志 */
    flag = fcntl(fd, F_GETFL);
    if (-1 == flag)
    {
        perror("fcntl F_GETFL error");
        ret = -1;
        goto err;
    }
    printf("flags: 0x%x\n", flag);


    /* 设置文件状态标志,添加 O_APPEND 标志 */
    ret = fcntl(fd, F_SETFL, flag | O_APPEND);
    if (-1 == ret)
    {
        perror("fcntl F_SETFL error");
        goto err;
    }
    ret = 0;
err:
    /* 关闭文件 */
    close(fd);
    exit(ret);
}