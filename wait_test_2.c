#include <stdio.h>
#include <sys/wait.h>

int
main(void)
{
	pid_t pid1, pid2;

	if ((pid1 = fork()) < 0)
		printf("fork error");
	else if (pid1 == 0) {
		printf("child, %d\n", getpid());
		sleep(5);
	} else {
		pid2 = wait(NULL);
		printf("father, %d\n", getpid());
		printf("wait %ld\n", (long)pid2);
	}
	return (0);
}