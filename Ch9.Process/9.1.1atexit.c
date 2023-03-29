#include <stdlib.h>
#include <stdio.h>

static void bye(void)
{
    puts("Bye!\n");
}

int main(void)
{
    if (atexit(bye))
    {
        fprintf(stderr, "atexit failed\n");
        exit(-1);
    }

    exit(0);
}