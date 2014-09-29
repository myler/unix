#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define PORT 9999
#define SERVER_IP "222.18.159.80"
int main()
{
    int s;
    struct sockaddr_in addr;
    char buffer[256];
    if((s = socket(AF_INET,SOCK_STREAM,0))<0){
        perror("socket");
        exit(1);
    }
    /* 填写sockaddr_in结构*/
    bzero(&addr,sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port=htons(PORT);
    addr.sin_addr.s_addr = inet_addr(SERVER_IP);
    /* 尝试连线*/
    if(connect(s,(struct sockaddr *)&addr,sizeof(addr))<0){
        perror("connect");
        exit(1);
    }
    /* 接收由server端传来的信息*/
    recv(s,buffer,sizeof(buffer),0);
    printf("%s\n",buffer);
    while(1){
        bzero(buffer,sizeof(buffer));
        /* 从标准输入设备取得字符串*/
        printf("enter msg:\n");
        read(STDIN_FILENO,buffer,sizeof(buffer));
        /* 将字符串传给server端*/
        if(send(s,buffer,sizeof(buffer),0)<0){
            perror("send");
            exit(1);
        }
    }
    return 0;
}
