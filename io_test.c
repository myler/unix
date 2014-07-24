#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

int
main(void)
{
	int fd;
	char buf_1[] = "hello world\n";
	char buf_2[50];

	if ((fd = open("hello_test.txt",
					O_WRONLY | O_CREAT | O_TRUNC, 0666)) == -1)
		printf("can't open or create hello_test.txt\n");

	if (write(fd, buf_1, sizeof(buf_1)) == -1)
		printf("can't write to hello_test.txt\n");

	if (close(fd) == -1)
		printf("can't close\n");

	if ((fd = open("hello_test.txt",O_RDONLY)) == -1)
		printf("can't open hello_test.txt\n");

	if (read(fd, buf_2, sizeof(buf_2)) == -1)
		printf("can't read hello_test.txt\n");
	else
		printf("%s", buf_2);

	if (close(fd) == -1)
		printf("can't close\n");

	if ((fd = open("hello_test.txt",O_RDONLY)) == -1)
		printf("can't open hello_test.txt\n");

	if (lseek(fd, 6, SEEK_SET) == -1)
		printf("can't lseek\n");

	if (read(fd, buf_2, sizeof(buf_2)) == -1)
		printf("can't read hello_test.txt\n");
	else
		printf("%s", buf_2);

	if (close(fd) == -1)
		printf("can't close\n");

	exit(0);
}