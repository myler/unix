#include <stdio.h>
#include <sys/wait.h>

int
main(void)
{
	pid_t pid1, pid2;

	if ((pid1 = fork()) < 0)
		printf("fork error");
	else if (pid1 == 0) {
		printf("child, %ld\n", (long)getpid());
		sleep(5);
	} else {

		do {
			pid2 = waitpid(pid1, NULL, WNOHANG);
			if (pid2 == 0) {
				printf("No child exited\n");
				sleep(1);
			}
		} while (pid2 == 0);

		if (pid2 == pid1)
			printf("successfully get child %ld\n", (long)pid2);
		else
			printf("some error occured\n");
	}

	return 0;
}