#include "apue.h"
#include <sys/wait.h>

char *env_init[] = { "USER=unknown", "PATH=/tmp", NULL};

int
main(void)
{
	pid_t pid;

	if ((pid = fork()) < 0)
		err_sys("fork error");
	else if (pid == 0) {
		if (execle("/home/myl/Workspace/unix/hello",
		 "hello", (char *)0, env_init) < 0)
			err_sys("execle error");
	}

	if (waitpid(pid, NULL, 0) < 0)
		err_sys("wait error");

	if ((pid = fork()) < 0)
		err_sys("fork error");
	else if (pid == 0) {
		if (execlp("ioctl_get_addr", "ioctl_get_addr", "eth0", (char *)0) < 0)
			err_sys("execlp error");
	}

	return 0;
}