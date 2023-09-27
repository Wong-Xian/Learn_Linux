#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdio.h>
#include<stdlib.h>

/*
origional Func
    int open(const char *pathname, int flags);
    int open(const char *pathname, int flags, mode_t mode);

use "man 2 open" to check the manual of open function.
*/

int main()
{
    int fd1 = open ("./app.c",O_RDONLY); // open an existing file with read only flag.
    printf("fd1 = %d\n",fd1);
    // if (fd1==-1)
    //     return fd1;
    
    int fd2 = open ("./app.c",O_WRONLY);// open an existing file with write only flag.
    printf("fd2 = %d\n",fd2);
    // if (fd2==-1)
    //     return fd2;
    
    int fd3 = open ("./app.c",O_RDWR);  // open an existing file with read & write flag.
    printf("fd3 = %d\n",fd3);
    // if (fd3==-1)
    //     return fd3;
    
    int fd4 = open ("./app.c",O_RDWR|__O_NOFOLLOW); // open with read&write flag, if it is 
                                                    // a symbolic link, the open fails.
    printf("fd4 = %d\n",fd4);    
    // if (fd4==-1)
    //     return fd4;

    int fd5 = open ("./a.cpp", O_RDWR|O_CREAT, S_IRWXU|S_IRGRP|S_IROTH);
    printf("fd5 = %d\n",fd5);    
    /*open a.cpp, if it doesn't exist, create it, & set its mode as above:
    user:rwx, group:r, other:r*/

    int fd6 = open ("./ln_a", O_NOFOLLOW);
    printf ("fd6 = %d\n",fd6);
    /* The flag O_NOFOLLOW allows function return -1 when the file to be open is a link */

    return 0;
}