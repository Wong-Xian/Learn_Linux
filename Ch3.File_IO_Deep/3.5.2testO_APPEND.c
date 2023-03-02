/*
main purpose:
    open file with O_APPEND flag, then try lseek() before write(), see if it works.
*/
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>

int main()
{
    /*Step0. define var*/
    int fd1, ret;
    char buf[8]={'0','1','2','3','4','5','6','7'};
    char bufout[16];

    /*Step1. create a file and write sth in it.*/
    fd1 = open("./3.5.2testfile.txt", O_RDWR|O_CREAT|O_TRUNC, S_IWUSR|S_IRUSR|S_IRGRP|S_IROTH);
    if (fd1==-1)
    {
        perror("open error");
        exit(fd1);
    }

    ret = write(fd1, buf, 8);// write buf into file
    if (ret==-1)
    {
        perror("write error");
        goto err;
    }

    close(fd1);// close file.


    /*Step2. open with flag O_APPEND*/
    fd1 = open("./3.5.2testfile.txt", O_RDWR|O_APPEND);
    if (fd1==-1)
    {
        perror("open error");
        exit(fd1);
    }

    ret = read(fd1, bufout, sizeof(bufout));    // read data to bufout
    if (ret==-1)
    {
        perror("read error");
        goto err;
    }
    else
    {
        printf("%d bytes read.\n",ret);
        printf("%sdone\n",bufout);
    }

    // ret = lseek(fd1, 0, SEEK_SET);    // set cursor
    // if (ret==-1)
    // {
    //     perror("lseek error");
    //     goto err;
    // }

    lseek(fd1, 0, SEEK_SET);
    ret = write(fd1, buf, 4);// write buf
    printf("%d bytes wirtten.\n",ret);
    if (ret==-1)
    {
        perror("write error");
        goto err;
    }

    lseek(fd1, 0, SEEK_SET);
    ret = read(fd1, bufout, sizeof(bufout));    // read data to bufout
    if (ret==-1)
    {
        perror("read error");
        goto err;
    }
    else
    {
        printf("%d bytes read.\n",ret);
        printf("%sdone\n",bufout);
    }


err:
    close(fd1);
    exit(ret);
}