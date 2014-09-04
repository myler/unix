#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(void) {
    struct flock lock;
    int fd;

    if ((fd = open("/home/myl/Workspace/unix/locktest.txt", O_RDWR)) < 0) {
        perror("open");
        return -1;
    }

    printf("pid = %d\n", getpid());

    lock.l_type = F_WRLCK;
    lock.l_start = 4;
    lock.l_whence = SEEK_SET;
    lock.l_len = 1;

    if (fcntl(fd, F_SETLK, &lock) < 0) {
        perror("fcntl");
        return -1;
    }

    while (1)
        sleep(1);

    exit(0);
}
