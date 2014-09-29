/******************************************************************************

  Copyright (C), 2001-2011, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : hi_thread.h
  Version       : Initial Draft
  Author        : 
  Created       : 
  Last Modified :
  Description   : hi_thread.c header file
  Function List :
  History       :
  1.Date        : 
    Author      : Monster
    Modification: Created file

******************************************************************************/


#ifndef __VS_SOCKET_H__
#define __VS_SOCKET_H__


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <unistd.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include "config.h"

#define   MAXBUF  1024


extern AllConfig g_config; 

#if 0
#define VIDEOPORT                           3001   /* 视频服务器的VideoPort    */
#define AUDIOPORT                           4601    /* 视频服务器的AudioPort    */
#define MSGPORT                             3000/* 视频服务器的MsgPort      */
#endif

#if 1
#define VIDEOPORT                           g_config.network.rtv_port.var   /* 视频服务器的VideoPort    */
#define AUDIOPORT                           4601    /* 视频服务器的AudioPort    */
#define MSGPORT                             g_config.network.socket_port.var/* 视频服务器的MsgPort      */
#endif

#define MAX_SOCKET_BUF_SIZE    10240          // 注意一条控制消息的总长度小于该值，并且小于网络MTU阀值
#define MAX_SOCKET_BUF_INNER_SIZE    MAX_SOCKET_BUF_SIZE + 4         // 注意一条控制消息的总长度小于该值，并且小于网络MTU阀值




// 接入服务器
#define ACCESS_SERVER       0

// 分发服务器
#define BRODCAST_SERVER     1

// 备份服务器
#define BACKUP_SERVER       2

// 被动连接
#define PASSIVENESS_CONNECT 3

// 最大主动连接数
#define MAX_CONNECT_TO_SERVER   4

#define BUF_REC_BLK_SIZE 1024

/*  网络传送类型定义  */
#define SENDTYPE_TCP    	1
#define SENDTYPE_UDP    	2


// 主动连接Socket 数组
int g_vs_sock[ MAX_CONNECT_TO_SERVER ];
int g_rtv_sock[MAX_CONNECT_TO_SERVER][2];

int listen_sock(int socket_id, int port);
int thread_socket_msg_main();
int thread_socket_msg_usr_main();
int thread_recv_from_con(void *param);
int thread_recv_from_con();

int vs_send( int sockid, char *buf, int ilen );
int vs_send_real( int sockid, char *buf, int ilen );

int vs_connect( char *ip, int port, int type );
int package_send( char *buf, int ilen, int type, int send_type, int socketid );
int thread_access_reconnnet_main();
int alert_send_start(int alert_type);
int thread_file_del_main();
int thread_alert_send_main();
int thread_dosfsck_main();

typedef struct tag_thread_socket_maindata
{
	fd_set	read_fds;
    struct  sockaddr_in remoteaddr;
    struct  timeval tv;
    int     listener_msg, listener_video;
    int     newfd;
    int     nbytes;
    int     addrlen;
    int     i;
    int     ret;
    char    *msg_buf;
    
} s_thread_socket_maindata;

typedef struct tag_socket_maindata
{
	fd_set  g_sock_fd;
    int     g_fd_max;
    int     g_quit_sock;    
    char    buffer[BUF_REC_BLK_SIZE];
    char    *buf_msg;
} s_socket_maindata;

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __VS_SOCKET_H__ */

