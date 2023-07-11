#include <stdio.h>
#include <stdlib.h>
#include <sys/sysinfo.h>

char* switchtime(long t)
{
    int h,m,s;
    static char a[10]={0};

    h = t/3600;
    m = (t-h*3600)/60;
    s = t-3600*h-60*m;
    
    sprintf(a, "%dh %dm %ds", h, m, s);

    return a;
}

int main(void)
{
    struct sysinfo sys_info;
    int ret;

    /* 获取信息 */
    ret = sysinfo(&sys_info);
    if (-1 == ret)
    {
        perror("sysinfo error");
        exit(-1);
    }

    /* 打印信息 */
    printf("uptime: %s\n", switchtime(sys_info.uptime));
    printf("totalram: %luGB\n", sys_info.totalram/1073741824);
    printf("freeram: %luGB\n", sys_info.freeram/1073741824);
    printf("procs: %u\n", sys_info.procs);

    exit(0);
}