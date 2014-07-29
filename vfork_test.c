#include "apue.h"

int global_val = 1;
const char buf[] = "a write to test stdout.\n";

int
main(void)
{
	int auto_val = 2;
	pid_t pid;

	if (write(STDOUT_FILENO, buf, sizeof(buf) - 1) != sizeof(buf) - 1)
		err_sys("write error");
	printf("before vfork");

	if ((pid = vfork()) < 0)
		err_sys("vfork error");
	else if (pid == 0) {
		global_val++;
		auto_val++;
		_exit(0);
	} else
		global_val++;

	printf("pid = %ld, glob = %d, auto_val = %d\n",
		(long)getpid(), global_val, auto_val);

	exit(0);
}