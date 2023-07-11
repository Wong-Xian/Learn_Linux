/*
本测试例程目的：
    通过 __thread 修饰，创建线程局部变量，在主线程和子线程中分别向变量副本写入数据，并打印输出。
现象：
    主线程和子线程打印输出的变量内容不同，因为子线程中的变量是一个副本。
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>

// 声明线程局部变量
static __thread char buf[100];

// 定义线程初始化函数
static void* thread_start(void *arg)
{
    strcpy(buf,"Child Thread\n");
    printf("子线程: buf(%p)=%s", buf, buf); // 输出 buf 的地址和内容
    pthread_exit(NULL); // 结束线程
}

// 主函数
int main(int argc, char* argv[])
{
    pthread_t tid;  // 线程id变量
    int ret;

    strcpy(buf, "Main Thread\n");

    // 创建子线程
    if (ret = pthread_create(&tid, NULL, thread_start, NULL))
    {
        fprintf(stderr, "pthread_create error:%d\n", ret);
        exit(-1);
    }

    // 等待回收子线程
    if (ret = pthread_join(tid, NULL))
    {
        fprintf(stderr, "pthread_join error: %d\n", ret);
        exit(-1);
    }

    printf("主线程: buf(%p)=%s", buf, buf); // 输出 buf 的地址和内容
    
    exit(0);
}