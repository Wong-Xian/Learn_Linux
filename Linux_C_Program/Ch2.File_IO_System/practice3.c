#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>       // for open();

#include<unistd.h>      // for write();close();read();

#include<stdio.h>       // for printf()

int main()
{
    // init variable.
    int fd1 = 0;
    int status = 0;
    char zeros[1024] = {'0'};
    char ones[1024] = {'1'};


    // open or create file.
    fd1 = open ("./test1.txt",
                O_WRONLY|O_CREAT,
                S_IRWXU|S_IRGRP|S_IROTH);
    if (fd1==-1)
    {
        printf ("open file failed!\n");
        status = fd1;
        goto err;
    }
    

    // write datas.
    status = write(fd1, zeros, sizeof(zeros));
    if (status==-1)
    {
        printf("write failed.\n");
        goto err;
    }
    status = write(fd1, ones, sizeof(ones));
    if (status==-1)
    {
        printf("write failed.\n");
        goto err;
    }
    else status = 0;

    // quit
err:
    close(fd1);
    return status;
}