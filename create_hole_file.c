#include "apue.h"
#include <fcntl.h>

char buf_1[] = "abcdefghij";
char buf_2[] = "ABCDEFGHIJ";

int
main(void)
{
	int		fd;

	if ((fd = creat("file.hole", FILE_MODE)) < 0)
		err_sys("create error");

	if(write(fd, buf_1, 10) != 10)
		err_sys("buf_1 write error");

	if(lseek(fd, 16384, SEEK_SET) == -1)
		err_sys("lseek error");

	if(write(fd, buf_2, 10) != 10)
		err_sys("buf_2 write error");

	exit(0);
}