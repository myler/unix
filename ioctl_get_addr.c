#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/ioctl.h>
#include <net/if.h>

int
main(int argc, char *argv[])
{
	struct sockaddr_in *addr;
	struct ifreq ifr;
	char *name, *address;
	int socket_fd;

	if (argc != 2)
		printf("Usage: %s <ipconfig interface>\n", argv[0]),exit(1);
	else {
		name = argv[1];
		strcpy(ifr.ifr_name, name);
	}

	if ((socket_fd = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
		perror("can't get socket_fd\n"), exit(1);

	if (ioctl(socket_fd, SIOCGIFADDR, &ifr) == -1)
		perror("ioctl error"), exit(1);
	addr = (struct sockaddr_in *) &(ifr.ifr_addr);
	address = inet_ntoa(addr->sin_addr);
	printf("inet addr: %s\n", address);

	if (ioctl(socket_fd, SIOCGIFBRDADDR, &ifr) == -1)
		perror("ioctl error"), exit(1);
	addr = (struct sockaddr_in *) &(ifr.ifr_broadaddr);
	address = inet_ntoa(addr->sin_addr);
	printf("broad addr: %s\n", address);

	if (ioctl(socket_fd, SIOCGIFNETMASK, &ifr) == -1)
		perror("ioctl error"), exit(1);
	addr = (struct sockaddr_in *) &(ifr.ifr_addr);
	address = inet_ntoa(addr->sin_addr);
	printf("inet mask: %s\n", address);

	exit(0);
}