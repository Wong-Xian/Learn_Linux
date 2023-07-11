/*
O_TRUNC
    If the file already exists and is a regular file and the access mode allows writing (i.e., is O_RDWR or
    O_WRONLY) it will be truncated to length 0.  If the file is a FIFO or terminal device file, the O_TRUNC
    flag is ignored.  Otherwise, the effect of O_TRUNC is unspecified.
O_APPEND
    The  file  is opened in append mode.  Before each write(2), the file offset is positioned at the end of
    the file, as if with lseek(2).  The modification of the file offset and the write  operation  are  per‐
    formed as a single atomic step.
*/

#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>


// Learn O_TRUNC
// int main()
// {
//     // open file, if it do not exist, create it.
//     int fd = open ("./testfile.txt", O_RDWR|O_TRUNC);
//     if (fd==-1)
//     {
//         perror("open error");
//         exit(fd);
//     }

//     close(fd);
//     exit(0);
// }

/*
Sum:
    the size of the exist file "testfile.txt" shrink from 128 Bytes to 0.
*/

// Learn O_APPEND
int main()
{
    char buffer[16];
    int fd;
    int ret;
    /* 打开文件 */
    fd = open("./testfile.txt", O_RDWR | O_APPEND);
    if (-1 == fd)
    {
        perror("open error");
        exit(-1);
    }
    /* 初始化 buffer 中的数据 */
    memset(buffer, 0x55, sizeof(buffer));
    /* 写入数据: 写入 4 个字节数据 */
    ret = write(fd, buffer, 4);
    if (-1 == ret)
    {
        perror("write error");
        goto err;
    }
    /* 将 buffer 缓冲区中的数据全部清 0 */
    memset(buffer, 0x00, sizeof(buffer));
    /* 将位置偏移量移动到距离文件末尾 4 个字节处 */
    ret = lseek(fd, -4, SEEK_END);
    if (-1 == ret)
    {
        perror("lseek error");
        goto err;
    }
    /* 读取数据 */
    ret = read(fd, buffer, 4);
    if (-1 == ret)
    {
        perror("read error");
        goto err;
    }
    printf("0x%x 0x%x 0x%x 0x%x\n", buffer[0], buffer[1],
    buffer[2], buffer[3]);
    ret = 0;
err:
    /* 关闭文件 */
    close(fd);
    exit(ret);
}