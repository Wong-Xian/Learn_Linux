/*
验证：子进程共享父进程的地址空间
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int a = 10;

int main(int argc, char *argv[])
{
	pid_t pid;
	int b = 20;
	
	pid = vfork();	// 创建进程
	if(pid < 0){    // 出错
		perror("vfork");
	}
	
	if(0 == pid){   // 子进程
	
		a = 100, b = 200;
		printf("son: a = %d, b = %d\n", a, b);
		
		_exit(0);   // 退出子进程，必须
	}
    else if(pid > 0)// 父进程
    { 
		printf("father: a = %d, b = %d\n", a, b);	
	}
	
	return 0;
}

/*
运行结果得知，子进程修改 a, b 的值，会影响到父进程的 a, b
*/