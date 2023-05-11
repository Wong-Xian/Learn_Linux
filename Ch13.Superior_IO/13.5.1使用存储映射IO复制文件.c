#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/mman.h>
#include<string.h>

int main(int argc, char *argv[])
{
    /* 定义变量 */
    int srcfd, dstfd;   // 源文件描述符，目标文件描述符
    void *srcaddr;      // 源地址
    void *dstaddr;      // 目标地址
    int ret;
    struct stat sbuf;   // stat 结构体

    if (argc != 3)      // 若输入参数不为2
    {
        fprintf(stderr, "usage: %s<srcfile><dstfile>\n", argv[0]);
        exit(-1);
    }

    /* 打开源文件 */
    srcfd = open(argv[1], O_RDONLY);
    if (srcfd == -1)
    {
        perror("open error");
        exit(-1);
    }

    /* 打开目标文件 */
    dstfd = open(argv[2], O_RDWR | O_CREAT | O_TRUNC, 0664);
    if (dstfd == -1)
    {
        perror("open error");
        ret = -1;
        goto out1;
    }

    /* 获取源文件的大小 */
    fstat(srcfd, &sbuf);

    /* 设置目标文件大小 */
    ftruncate(dstfd, sbuf.st_size);

    /* 将源文件映射到进程内存区域 */
    srcaddr = mmap(NULL, sbuf.st_size, PROT_READ, MAP_SHARED, srcfd, 0);
    if (srcaddr == MAP_FAILED)
    {
        perror("mmap error");
        ret = -1;
        goto out2;
    }

    /* 将目标文件映射到内存区域 */
    dstaddr = mmap(NULL, sbuf.st_size, PROT_WRITE, MAP_SHARED, dstfd, 0);
    if (dstaddr == MAP_FAILED)
    {
        perror("mmap error");
        ret = -1;
        goto out3;
    }

    /* 将源文件中的内容复制到目标文件中 */
    memcpy(dstaddr, srcaddr, sbuf.st_size);
    // 把文件映射到内存中后，对内存的读写，就相当于对文件的读写了。

    /* 程序退出前清理工作 */
    
    out4:
        /* 解除目标文件映射 */
        munmap(dstaddr, sbuf.st_size);
    
    out3:
        /* 解除源文件映射 */
        munmap(srcaddr, sbuf.st_size);
    
    out2:
        /* 关闭目标文件 */
        close(dstfd);
    
    out1:
        /* 关闭源文件并退出 */
        close(srcfd);
        exit(ret);
    
}