#include <sys/epoll.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/time.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>

#define SERV_PORT       9999
#define MAX_EVENTS      500
#define BUF_LEN         1024

typedef struct _CLIENT {
    int                 fd;
    struct sockaddr_in  addr;
} CLIENT;

char                    recvBuf[BUF_LEN];
int                     currentClient = 0;
int                     epollfd;
struct epoll_event      eventList[MAX_EVENTS];

void AcceptConn(int srvfd);
void RecvData(int fd);

int
main(void)
{
    int                 i, ret;
    int                 listenfd;
    int                 timeout;
    struct sockaddr_in  server_addr;
    char               *msg = "welcome!\n";

    if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        printf("create socket error: %s(errno: %d)\n", strerror(errno), errno);
        exit(1);
    } else {
        printf("create socket success...Done.\n");
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(SERV_PORT);

    if (bind(listenfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        printf("bind socket error: %s(errno: %d)\n", strerror(errno), errno);
        exit(1);
    } else {
        printf("bind socket success...Done.\n");
    }

    if (listen(listenfd, 5) == -1) {
        printf("listen socket error: %s(errno: %d)\n", strerror(errno), errno);
        exit(1);
    } else {
        printf("server is listening...\n");
    }

    epollfd = epoll_create(MAX_EVENTS);
    struct epoll_event event;
    event.events = EPOLLIN | EPOLLET;
    event.data.fd = listenfd;

    if (epoll_ctl(epollfd, EPOLL_CTL_ADD, listenfd, &event) == -1) {
        printf("epoll config error: %s(errno: %d)\n", strerror(errno), errno);
    }

    while (1) {
        timeout = 3000;
        if ((ret = epoll_wait(epollfd, eventList, MAX_EVENTS, timeout)) == -1) {
            printf("epoll wait error: %s(errno: %d)\n", strerror(errno), errno);
            break;
        }

        for (i = 0; i < ret; ++i) {
            if ((eventList[i].events & EPOLLERR) ||
                (eventList[i].events & EPOLLHUP) ||
                !(eventList[i].events & EPOLLIN)) {
                printf("epoll error\n");
                close(eventList[i].data.fd);
                exit(1);
            }

            if (eventList[i].data.fd == listenfd) {
                AcceptConn(listenfd);
            } else {
                send(eventList[i].data.fd, msg, sizeof(msg), 0);
                RecvData(eventList[i].data.fd);
            }
        }
    }

    return 0;
}

void
AcceptConn(int srvfd)
{
    struct sockaddr_in  sin;
    socklen_t           sockLen = sizeof(struct sockaddr_in);

    memset(&sin, 0, sockLen);
    int confd = accept(srvfd, (struct sockaddr *)&sin, &sockLen);

    if (confd < 0) {
        printf("create socket(fd: %d) error: %s(errno: %d)\n",
               confd, strerror(errno), errno);
        return;
    } else {
        printf("accept connection: %d\n", confd);
        struct epoll_event event;
        event.data.fd = confd;
        event.events = EPOLLIN | EPOLLET;
        epoll_ctl(epollfd, EPOLL_CTL_ADD, confd, &event);
    }
}

void
RecvData(int fd)
{
    int                 ret;
    int                 recvLen = 0;

    memset(recvBuf, 0, BUF_LEN);

    while (recvLen < BUF_LEN) {
        ret = recv(fd, (char *)recvBuf + recvLen, BUF_LEN - recvLen, 0);
        if (ret <= 0) {
            recvLen = 0;
            break;
        } else {
            recvLen += ret;
        }
    }
    printf("Recvmsg is %s\n", recvBuf);
}
