/*
验证通过 vfork() 创建的子进程会执行完后，才到父进程执行
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
 
int main(int argc, char *argv[])
{
	pid_t pid;
	
	pid = vfork();	// 创建进程
	if(pid < 0)     // 出错
    { 
		perror("vfork");
	}
	
	if(0 == pid)    // 子进程
    { 
		sleep(3);   // 延时 3 秒
		printf("i am son\n");
		_exit(0);   // 退出子进程，必须
	}
    else if(pid > 0)// 父进程
    { 
		printf("i am father\n");
	}
	
	return 0;
}