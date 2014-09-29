#include <stdio.h>
#include <sys/select.h>
#include <unistd.h>
#include <string.h>

int main(void) {
	char rbuf[10];
	fd_set rd_fds;
	int ret, len;
	struct timeval tv;
	tv.tv_sec = 3;
	tv.tv_usec = 0;

	while(1) {
		FD_ZERO(&rd_fds);
		FD_SET(STDIN_FILENO, &rd_fds);
		tv.tv_sec = 3;
		tv.tv_usec = 0;

		ret = select(STDIN_FILENO + 1, &rd_fds, NULL, NULL, &tv);
		switch(ret) {
			case -1:
				perror("select");
				break;
			case 0:
				printf("timeout, goto next loop\n");
			default:
				printf("ret = %d\n", ret);
				if (FD_ISSET(STDIN_FILENO, &rd_fds)) {
					len = read(STDIN_FILENO, rbuf, 9);
					rbuf[len] = '\0';
					printf("%s", rbuf);
				}
		}
	}
}
