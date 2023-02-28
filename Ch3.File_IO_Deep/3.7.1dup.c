#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(void)
{
    unsigned char buffer1[4], buffer2[4];
    int fd1, fd2;
    int ret;
    int i;


    /* 创建新文件 test_file 并打开 */
    fd1 = open("./test_file", O_RDWR | O_CREAT | O_EXCL,
                S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    if (-1 == fd1)
    {
        perror("open error");
        exit(-1);
    }


    /* 复制文件描述符 */
    fd2 = dup(fd1);
    if (-1 == fd2)
    {
        perror("dup error");
        ret = -1;
        goto err1;
    }
    
    printf("fd1: %d\nfd2: %d\n", fd1, fd2); // 输出fd1和fd2
    
    
    /* buffer 数据初始化 */
    buffer1[0] = 0x11;
    buffer1[1] = 0x22;
    buffer1[2] = 0x33;
    buffer1[3] = 0x44;

    buffer2[0] = 0xAA;
    buffer2[1] = 0xBB;
    buffer2[2] = 0xCC;
    buffer2[3] = 0xDD;
    
    
    /* 循环写入数据 */
    for (i = 0; i < 4; i++)
    {
        ret = write(fd1, buffer1, sizeof(buffer1));
        if (-1 == ret)
        {
            perror("write error");
            goto err2;
        }
        ret = write(fd2, buffer2, sizeof(buffer2));
        if (-1 == ret)
        {
            perror("write error");
            goto err2;
        }
    }
    
    
    /* 将读写位置偏移量移动到文件头 */
    ret = lseek(fd1, 0, SEEK_SET);
    if (-1 == ret)
    {
        perror("lseek error");
        goto err2;
    }
    
    
    /* 读取数据 */
    for (i = 0; i < 8; i++)
    {
        ret = read(fd1, buffer1, sizeof(buffer1));
        if (-1 == ret) {
        perror("read error");
        goto err2;
    }
    printf("%x%x%x%x", buffer1[0], buffer1[1],
    buffer1[2], buffer1[3]);
    }
    printf("\n");
    ret = 0;

err2:
    close(fd2);
err1:
    /* 关闭文件 */
    close(fd1);
    exit(ret);
}