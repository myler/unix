#include "apue.h"
#include <pwd.h>

struct passwd *ptr;

static void
my_alarm(int signo)
{
	struct passwd *rootptr;

	printf("in signal handler\n");
	if ((rootptr = getpwnam("root")) == NULL)
		err_sys("getpwnam(root) error");
	if (strcmp(ptr->pw_name, "root") != 0)
			printf("return value corrupted!, pw_name = %s\n", ptr->pw_name);
	//alarm(1);
}

int
main(void)
{
	signal(SIGALRM, my_alarm);
	alarm(1);
	sleep(5);
	// while(1)
	// {
	// 	if ((ptr = getpwnam("myl")) == NULL)
	// 		err_sys("getpwnam error");
	// 	if (strcmp(ptr->pw_name, "myl") != 0)
	// 		printf("return value corrupted!, pw_name = %s\n", ptr->pw_name);
	// }
}