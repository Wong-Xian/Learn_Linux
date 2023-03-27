#include<stdio.h>
#include<stdlib.h>
#include<signal.h>

int main()
{
    sigset_t signalSet;
    unsigned long int num;

    int ret = sigfillset(&signalSet);
    if (-1 == ret)
    {
        perror("sigemptyset error");
        exit(-1);
    }

    num = signalSet.__val[0];
    printf("val[0] is %lu\n", num);

    exit(0);
}