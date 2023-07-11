#define _GNU_SOURCE

#include <stdio.h>
#include <string.h>

#define MAX_ERROR_LEN 256

static char buf[MAX_ERROR_LEN];


static char *strerror(int errnum)
{
    if (errnum < 0 || errnum >= _sys_nerr || NULL == _sys_errlist[errnum])
        snprintf(buf, MAX_ERROR_LEN, "Unknown error %d", errnum);
    else
    {
        strncpy(buf, _sys_errlist[errnum], MAX_ERROR_LEN - 1);
        buf[MAX_ERROR_LEN - 1] = '\0';//终止字符
    }
    
    return buf;
}