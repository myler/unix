#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define PORT 1235
#define MAXSOCKFD 10

main()
{
    int sockfd,newsockfd,is_connected[MAXSOCKFD],fd;
    struct sockaddr_in addr;
    // struct sockaddr *addrt;
    int addr_len = sizeof(struct sockaddr_in);
    fd_set readfds;
    char buffer[256];
    char msg[] ="Welcome to server!";
    if ((sockfd = socket(AF_INET,SOCK_STREAM,0))<0){

        perror("socket");
        exit(1);
    }
    printf("%d\n", sockfd);

    bzero(&addr,sizeof(addr));
    // memset(&addr,0,sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    // addrt = &addr;
    if(bind(sockfd,(struct sockaddr *)&addr,sizeof(addr))<0){
        perror("connect");
        exit(1);
    }
    printf("%d\n", sockfd);
    if(listen(sockfd,3)<0){
        perror("listen");
        exit(1);
    }
    printf("%d\n", sockfd);
    for(fd=0;fd<MAXSOCKFD;fd++)
        is_connected[fd]=0;

    while(1){
        FD_ZERO(&readfds);
        FD_SET(sockfd,&readfds);
        printf("%d\n",sockfd );

        for(fd=0;fd<MAXSOCKFD;fd++) {
            if(is_connected[fd])
                FD_SET(fd,&readfds);
        }

        if(!select(MAXSOCKFD,&readfds,NULL,NULL,NULL))
            continue;

        for(fd=0;fd<MAXSOCKFD;fd++) {
            if(FD_ISSET(fd,&readfds)){
                if(sockfd ==fd){
                    if((newsockfd = accept (sockfd,(struct sockaddr *)&addr,&addr_len))<0)
                        perror("accept");
                    write(newsockfd,msg,sizeof(msg));
                    is_connected[newsockfd] =1;
                    printf("cnnect from %s\n",inet_ntoa(addr.sin_addr));
                }else{
                    bzero(buffer,sizeof(buffer));
                    if(read(fd,buffer,sizeof(buffer))<=0){
                        printf("connect closed.\n");
                        is_connected[fd]=0;
                        close(fd);
                    }else
                        printf("%s",buffer);
                }
            }
        }
    }
}
