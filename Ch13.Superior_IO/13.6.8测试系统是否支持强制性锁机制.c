#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    /* 定义变量 */
    struct stat sbuf = {0};     // 定义stat类型结构体sbuf
    int fd = -1;                // 定义文件描述符
    pid_t pid;                  // 定义进程号数据类型变量

    /* 校验传参 */
    if (argc != 2)
    {
        fprintf(stderr, "usage: %s <file>\n", srgv[0]);
        exit(-1);
    }

    /* 打开文件 */
    fd = open(argv[1], O_RDWR | O_CREAT | O_TRUNC, 0664);
    if (fd == -1)
    {
        perror ("open error");
        exit(-1);
    }

    /* 写入一行字符 */
    if (12 != write(fd, "Hello World!", 12))
    {
        perror("write error");
        exit(-1);
    }

    /* 开启强制性锁机制 */
    if (fstat(fd, &sbuf) < 0)   // 获取文件属性，存到sbuf中
    {
        perror("fstat error");
        exit(-1);
    }
    if (fchmod(fd, (sbuf.st_mode & ~S_IXGRP) | S_ISGID) < 0)
    {               // 先删除S_IXGRP标志位，在加入S_ISGID标志位
        perror("fchmod error");
        exit(-1);
    }

    /* 用fork创建子进程 */
    if ((pid = fork()) < 0) // 返回负值，代表出错
        perror("fork error");
    else if (pid > 0)
    {/********* 调用成功，向父进程返回子进程号，这段代码父进程执行 *********/
        struct flock lock = {0};

        /* 对整个文件加写锁 */
        lock.l_type = F_WRLCK;
        lock.l_whence = SEEK_SET;
        lock.l_start = 0;   // 起始为0
        lock.l_len = 0; // 全文
        if (fcntl(fd, F_SETLK, &lock) < 0)
            perror("父进程：加写锁失败");
        else
            printf("父进程：加写锁成功\n");
        
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

        if (wait(NULL) < 0)     // 等待子进程被终结，NULL表示不接收子进程终结的状态信息
            perror("wait error");
    }
    else
    {/********* fork函数向子进程返回0，子进程执行以下程序 *********/
        struct flock lock = {0};
        int flag;
        char buf[20] = {0};

        sleep(1);   // 休眠1秒，让父进程先运行

        /* 设置为非阻塞方式 */
        flag = fcntl (fd, F_GETFL); // 获取fd的flag标志
        flag |= O_NONBLOCK;     // 向flag中添加非阻塞标志
        fcntl(fd, F_SETFL, flag);// 更新文件的flag标志

        /* 对整个文件加读锁 */
        lock.l_type = F_RDLCK;
        lock.l_whence = SEEK_SET;
        lock.l_start = 0;
        lock.l_len = 0;
        if (fcntl(fd, F_SETLK, &lock) == -1)
            perror("子进程：加读锁失败")；
        else
            printf("子进程：加读锁成功\n");

        /* 读文件 */
        if (lseek(fd, 0, SEEK_SET) < 0)
            perror("lseek error");
        if (read(fd, buf, 12) < 0)
            perror("子进程：read error");
        else
            printf("子进程：read OK, buf = %s\n", buf);
    }

    exit(0);
}