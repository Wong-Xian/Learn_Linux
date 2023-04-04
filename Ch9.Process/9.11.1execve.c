#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    char *arg_arr[5] = {argv[1], "Hello", "World", NULL};
    char *env_arr[5] = {"NAME=app", "AGE=25", "SEX=man", NULL};

    if (2 > argc)
        exit(-1);

    // arg_arr[0] = argv[1];
    // arg_arr[1] = "Hello";
    // arg_arr[2] = "World";
    // arg_arr[3] = NULL;

    execve(argv[1], arg_arr, env_arr);
    // 把传入的参数argv[1]作为要运行的新程序的地址。
    // arg_arr是要传入的参数
    // env_arr是要传入的环境变量
    
    perror("execve error");
    exit(-1);
}