#include "apue.h"

int global_val = 1;
const char buf[] = "a write test to stdout.\n";

int
main(void)
{
	int auto_val = 2;
	pid_t pid;

	if (write(STDOUT_FILENO, buf, sizeof(buf) - 1) != sizeof(buf) - 1)
		err_sys("write error");

	printf("before fork\n");

	if ((pid = fork()) < 0)
		err_sys("fork error");
	else if (pid ==0)
	{
		global_val++;
		auto_val++;
	} else
		sleep(2);

	printf("pid = %ld, glob = %d, autoval = %d\n", 
		(long)getpid(), global_val, auto_val);

	exit(0);
}