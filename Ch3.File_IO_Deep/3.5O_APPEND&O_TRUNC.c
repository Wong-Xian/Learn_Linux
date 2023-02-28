/*
O_TRUNC
    If the file already exists and is a regular file and the access mode allows writing (i.e., is O_RDWR or
    O_WRONLY) it will be truncated to length 0.  If the file is a FIFO or terminal device file, the O_TRUNC
    flag is ignored.  Otherwise, the effect of O_TRUNC is unspecified.
*/

#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>

int main()
{
    // open file, if it do not exist, create it.
    int fd = open ("./testfile.txt", O_RDWR|O_TRUNC);
    if (fd==-1)
    {
        perror("open error");
        exit(fd);
    }

    close(fd);
    exit(0);
}

/*
Sum:
    the size of the exist file "testfile.txt" shrink from 128 Bytes to 0.
*/