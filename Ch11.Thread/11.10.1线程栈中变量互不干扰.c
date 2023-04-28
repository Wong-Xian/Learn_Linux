#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

static void *new_thread(void *arg)
{
    int number = *((int *)arg);
    unsigned long int tid = pthread_self();

    printf("当前为<%d>号线程, 线程 ID<%lu>\n", number, tid);

    return (void *)0;
}

static int nums[5] = {0, 1, 2, 3, 4};

int main(int argc, char *argv[])
{
    pthread_t tid[5];
    int j;

    /* 创建 5 个线程 */
    for (j = 0; j < 5; j++)
        pthread_create(&tid[j], NULL, new_thread, &nums[j]);

    /* 等待线程结束 */
    for (j = 0; j < 5; j++)
        pthread_join(tid[j], NULL);//回收线程

    exit(0);
}

/*
Sum:
    main函数创建了5个子线程，每个线程都执行new_thread函数，
    每个线程都在自己的栈空间中存在两个同名变量，但不同线程之
    间的同名变量不会相互影响。
*/