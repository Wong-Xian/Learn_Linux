#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
    printf("更改前进程组 ID<%d>\n", getpgrp());
    setpgid(0, 266);
    printf("更改后进程组 ID<%d>\n", getpgrp());

    exit(0);
}