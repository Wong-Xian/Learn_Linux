#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdio.h>
#include<unistd.h>

int main()
{
    // define return status.
    int ret;
    
    // define the lenth to copy
    size_t len = 1000;  // data type: long unsigned int.


    // define buffle pointer
    // void* buff = NULL;  this is not how it works...
    char buff[1024];


    // open the existing file.
    int fd_exist = open ("./source.txt",O_RDONLY);
    if (fd_exist==-1)
    {
        printf ("open file error, check the existing fiile!\n");
        return fd_exist;
    }

    // create a new file.
    int fd_toCreate = open ("./dest_file.txt",
                            O_CREAT|O_WRONLY|O_EXCL,
                            S_IRWXU|S_IRGRP|S_IROTH);
    if (fd_toCreate==-1)
    {
        printf ("create file error, check debug!\n");
        ret = fd_toCreate;
        goto err1;
    }


    // define read starting point.
    off_t set = lseek(fd_exist, 500, SEEK_SET);
    if (set==-1)
    {
        printf("set read start point error!\n");
        ret = set;
        goto err2;
    }
    else printf("read start from: %d\n", (int)set);


    // read 1KByte from source.txt
    ssize_t readResult = read (fd_exist, buff, sizeof(buff));    // data type: long int.
    if (readResult==-1)
    {
        printf("read data failed! Check debug!\n");
        ret = readResult;
        goto err2;
    }
    else printf("%d byte of data have been read.\n",(int)readResult);


    // define write starting point.
    off_t set2 = lseek (fd_toCreate, 0, SEEK_SET);
    if (set2==-1)
    {
        printf("set write start point error!\n");
        ret = set2;
        goto err2;
    }
    else printf("write start from: %d\n", (int)set2);


    // write data to created file.
    ssize_t writeResult = write (fd_toCreate, buff, sizeof(buff));
    if (writeResult==-1)
    {
        printf("write data failed! Check debug!\n");
        ret = writeResult;
    }
    else printf("%d byte of data have been written.\n", (int)writeResult);

    // close file
err2:
    close(fd_toCreate);
err1:
    close(fd_exist);
    return ret;
}
