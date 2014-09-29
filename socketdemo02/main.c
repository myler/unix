#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
#include <string.h>
#include <arpa/inet.h>

#define SERV_PORT           9999
#define BUFF_SIZE           4096

void
str_cli(FILE *fp, int sockfd) {
    int ret;
    char send_buf[BUFF_SIZE];
    memset(send_buf, 0, BUFF_SIZE);

    while (fputs("msg: ", stdout) && fgets(send_buf, BUFF_SIZE, fp) != NULL) {
        //memset(recv_buf, 0, sizeof(recv_buf));
        if (strlen(send_buf) > 1) {
            send(sockfd, send_buf, strlen(send_buf), 0);
        }

        //memset(send_buf, 0, sizeof(send_buf));
        fflush(stdout);
    }
}

int
main(int argc, char* argv[])
{
    int                     sockfd, ret;
    char                    buf[BUFF_SIZE];
    struct sockaddr_in      addr;
    size_t                  addrlen;
    pid_t pid;

    if (argc != 2) {
        printf("usage: %s <ip address>\n", argv[0]);
        exit(1);
    }

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        printf("create socket error: %s(errno: %d)\n", strerror(errno), errno);
        exit(1);
    }

    addrlen = sizeof(struct sockaddr_in);
    memset(&addr, 0, addrlen);
    addr.sin_family =       AF_INET;
    addr.sin_port =         htons(9999);
    if (inet_pton(AF_INET, argv[1], &addr.sin_addr) <= 0) {
        printf("ip address <%s> error or useless\n", argv[1]);
        exit(1);
    }

    if (connect(sockfd, (struct sockaddr *)&addr, addrlen) == -1) {
        printf("connect socket error: %s(errno: %d)\n", strerror(errno), errno);
        exit(1);
    } else {
        printf("connect to server success...\n");
    }
    if (recv(sockfd, buf, BUFF_SIZE, 0) <= 0)
        printf("recv error\n");
    fputs(buf, stdout);
    fflush(stdout);


//    str_cli(stdin, sockfd);
//    close(sockfd);
    if ((pid = fork()) < 0) {
        printf("fork error");
        exit(1);
    } else if (pid == 0) {
        while (1) {
            ret = recv(sockfd, buf, BUFF_SIZE, 0);
            if (ret == -1)
                printf("recv error\n");
            if (ret == 0)
                printf("recv error\n");
            fputs(buf, stdout);
            fflush(stdout);
        }
    } else {
        str_cli(stdin, sockfd);
    }

    if (waitpid(pid, NULL, 0) != pid)
        printf("waitpid error");
    close(sockfd);

    return 0;
}
