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

    lock.l_type = F_WRLCK;
    lock.l_start = 3;
    lock.l_whence = SEEK_SET;
    lock.l_len = 2;

    printf("lock\n");
    printf("lock.l_type: %s\n",
           (lock.l_type == F_WRLCK) ? "F_WRLCK" : "NOT F_WRLCK");
    printf("lock.l_start: %ld\n", lock.l_start);
    printf("lock.l_whence: %s\n",
           (lock.l_whence == SEEK_SET) ? "SEEK_SET" : "NOT SEEK_SET");
    printf("lock.l_len: %ld\n", lock.l_len);
    printf("lock.l_pid: %d\n\n\n", lock.l_pid);

    if (fcntl(fd, F_GETLK, &lock) < 0)
        perror("fcntl");

    if (lock.l_type == F_UNLCK)
        printf("no lock\n");
    else {
        printf("lock\n");
        printf("lock.l_type: %s\n",
               (lock.l_type == F_WRLCK) ? "F_WRLCK" : "NOT F_WRLCK");
        printf("lock.l_start: %ld\n", lock.l_start);
        printf("lock.l_whence: %s\n",
               (lock.l_whence == SEEK_SET) ? "SEEK_SET" : "NOT SEEK_SET");
        printf("lock.l_len: %ld\n", lock.l_len);
        printf("lock.l_pid: %d\n", lock.l_pid);
    }

    exit(0);
}
