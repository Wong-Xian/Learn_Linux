#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(void)
{
    pid_t pid;
    int fd;
    int i;

    fd = open("./test.txt", O_RDWR | O_TRUNC);// 打开文件
    if (0 > fd)
    {
        perror("open error");
        exit(-1);
    }
    
    pid = fork();   // 创建子进程
    switch (pid)
    {
        case -1:
            perror("fork error");
            close(fd);
            exit(-1);
        case 0:
            /* 子进程 */
            for (i = 0; i < 4; i++) //循环写入 4 次
            write(fd, "1122", 4);
            close(fd);
            _exit(0);
        default:
            /* 父进程 */
            for (i = 0; i < 4; i++) //循环写入 4 次
            write(fd, "AABB", 4);
            close(fd);
            exit(0);
    }
}