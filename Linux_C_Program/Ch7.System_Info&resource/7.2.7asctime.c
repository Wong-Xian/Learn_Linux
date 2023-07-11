#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main(void)
{
    struct tm local_t;
    char tm_str[100] = {0};
    time_t sec;

    /* 获取时间 */
    sec = time(NULL);
    if (-1 == sec)
    {
        perror("time error");
        exit(-1);
    }

    localtime_r(&sec, &local_t);// 将sec转换成local_t结构体
    asctime_r(&local_t, tm_str);// 将结构体转换成字符串形式

    printf("本地时间: %s", tm_str);

    exit(0);
}