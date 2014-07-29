#include <linux/cdrom.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/types.h>

int
main(void)
{
	int fd_cdrom;

	if ((fd_cdrom = open("/dev/cdrom", O_RDONLY | O_NONBLOCK)) < 0)
		printf("can't open cdrom\n"), exit(1);

	if (ioctl(fd_cdrom, CDROMEJECT) < 0)
		printf("can't eject cdrom\n"), exit(1);

	close(fd_cdrom);
	exit(0);
}