#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>

#define SERV_PORT           9999
#define MAX_CONN            10
#define BUFF_SIZE           4096

int
main(void)
{
    int                     listen_sockfd, conn_sockfd;
    int                     n;
    char                    buf[BUFF_SIZE];
    struct sockaddr_in      addr;
    size_t                  addrlen;

    if ((listen_sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        printf("create socket error: %s(errno: %d)\n", strerror(errno), errno);
        exit(1);
    }

    addrlen = sizeof(struct sockaddr_in);
    memset(&addr, 0, addrlen);
    addr.sin_family =       AF_INET;
    addr.sin_addr.s_addr =  htonl(INADDR_ANY);
    addr.sin_port =         htons(SERV_PORT);

    if (bind(listen_sockfd, (struct sockaddr *)&addr, addrlen) == -1) {
        printf("bind socket error: %s(errno: %d)\n", strerror(errno), errno);
        exit(1);
    }

    if (listen(listen_sockfd, MAX_CONN) == -1) {
        printf("listen socket error: %s(errno: %d)\n", strerror(errno), errno);
        exit(1);
    }

    while (1) {
        if ((conn_sockfd = accept(listen_sockfd, (struct sockaddr *)NULL, NULL)) == -1) {
            printf("accept socket error: %s(errno: %d)\n", strerror(errno), errno);
            continue;
        } else {
            printf("new socket connect...\nthe client socketfd: %d\n", conn_sockfd);
        }
        n = recv(conn_sockfd, &buf, BUFF_SIZE, 0);
        buf[n] = '\0';
        printf("received msg from client<%d>: %s\n", conn_sockfd, buf);
        close(conn_sockfd);
    }
    close(listen_sockfd);

    return 0;
}
