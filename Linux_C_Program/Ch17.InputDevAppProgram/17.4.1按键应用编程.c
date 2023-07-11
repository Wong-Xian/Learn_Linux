#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/input.h>

#define KEYBORD "/dev/input/event1"

int main(int argc, char *argv[])
{
    struct input_event in_ev = {0};
    int fd = -1;
    int value = -1;

    /* 打开文件 */
    if (0 > (fd = open(KEYBORD, O_RDONLY)))
    {
        perror("open error");
        exit(-1);
    }
    for ( ; ; )
    {
        /* 循环读取数据 */
        if (sizeof(struct input_event) != read(fd, &in_ev, sizeof(struct input_event)))
        {
            perror("read error");
            exit(-1);
        }
        if (EV_KEY == in_ev.type) //按键事件
        {
            switch (in_ev.value)
            {
                case 0:
                    printf("code<%d>: 松开\n", in_ev.code);
                    break;
                case 1:
                    printf("code<%d>: 按下\n", in_ev.code);
                    break;
                case 2:
                    printf("code<%d>: 长按\n", in_ev.code);
                    break;
            }
        }
    }
}