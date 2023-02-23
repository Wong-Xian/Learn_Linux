#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdio.h>
#include<unistd.h>

void func()
{
    // open the existing file.
    int fd_exist = open ("./source.txt",O_RDONLY);
    if (fd_exist==-1)
        printf ("open file error, check the existing fiile!\n");


    // create a new file.
    int fd_toCreate = open ("./dest_file.txt",
                            O_CREAT|O_WRONLY|O_EXCL,
                            S_IRWXU|S_IRGRP|S_IROTH);
    if (fd_toCreate==-1)
        printf ("create file error, check debug!\n");


    // define the lenth to copy
    size_t len = 1000;  // data type: long unsigned int.


    // define buffle pointer
    // void* buff = NULL;  this is not how it works...
    char buff[1024];


    // define read/write starting point.
    off_t set = lseek(fd_exist, 500, SEEK_SET);
    if (set==-1)
        printf("set read start point error!\n");
    else
        printf("read start from: %d\n", set);


    // read 1KByte from source.txt
    ssize_t readResult = read (fd_exist, buff, len);    // data type: long int.
    if (readResult==-1)
        printf("read data failed! Check debug!\n");
    else 
        printf("%d byte of data have been read.\n");


    // write data to created file.
    ssize_t writeResult = write (fd_toCreate, buff, len);
    if (writeResult==-1)
        printf("write data failed! Check debug!\n");
    else 
        printf("%d byte of data have been written.\n");

    // close file
    close(fd_exist);
    close(fd_toCreate);
}

void main()
{
    func();
}