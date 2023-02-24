#include <stdio.h>
#include <errno.h>  // where the errno is defined.

int main(void)
{
    printf("Error Number is %d\n", errno);
    return 0;
}