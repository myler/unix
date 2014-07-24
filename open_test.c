#include "apue.h"
#include <fcntl.h>

int
main(void)
{
	int fd;
	umask(0000);

	if ((fd = open("open_text.txt", O_RDWR | O_CREAT | O_TRUNC, 0777)) == -1)
		err_sys("can't open open_text.txt");
	else {
		printf("success\n");
		close(fd);
	}
	exit(0);
}