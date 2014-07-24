#include "apue.h"

int
main(void)
{
	struct stat stat_buf;

	if (stat("chmod_test.txt", &stat_buf) < 0)
		err_sys("stat error for chmod_test.txt");

	if (chmod("chmod_test.txt", (stat_buf.st_mode & ~S_IXGRP) | S_ISGID) < 0)
		err_sys("chmod error for chmod_test.txt");

	exit(0);
}