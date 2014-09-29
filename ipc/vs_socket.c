/***********************************************************************************
*              Copyright 2007 - 2010, Megaeyes. Co., Ltd.
*                           ALL RIGHTS RESERVED
* FileName: hi_server.c
* Description: main model .
*
* History:
* Version   Date              Author        DefectNum    Description
* 1.1       2007-08-22   q60002125     NULL            Create this file.
***********************************************************************************/
#ifdef __cplusplus
#if __cplusplus
extern "C"
{
#endif
#endif /* __cplusplus */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <semaphore.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>                             // for sleep()
#include <sys/wait.h>

#include "vs_socket.h"
#include "logger.h"
#include "vs_thread.h"
#include "receiver.h"
#include "debug.h"
#include "sem.h"
#include "protocol.h"

fd_set  g_sock_fd;
int     g_fd_max;
int     g_quit_sock = 0;    // 置1 时退出socket_main 线程

extern pthread_t th_recv_from_con_sockfd;
extern s_syn_ctrl syn_ctrl_sys;
extern s_syn_ctrl syn_ctrl_alarm;
extern s_syn_ctrl syn_ctrl_del;
extern s_syn_ctrl syn_ctrl_dosfsck;


int g_alart_type = 0;			// 报警类型0 无告警, 1 磁盘空间告警, 2 移动侦测告警,  4 严重错误告警(这个时候RTU应该重启硬件)

int g_deling;
int g_dosfscking = 0;


char buf[MAX_SOCKET_BUF_SIZE];
char buf_inner[MAX_SOCKET_BUF_INNER_SIZE];
char *buf_msg1, *buf_msg2;


s_socket_maindata socket_maindata;   // 客户端连接变量

int vs_send( int sockid, char *buf, int ilen )
{
    if ((sockid <= 0) || (NULL == buf) || (ilen <= 0))
        return -1;

    int len = 0;


    /* pgh 20080703 changed
        if( sockid <= MAX_CONNECT_TO_SERVER )
        {
            len = send( g_vs_sock[ sockid ], buf, ilen, 0 );
            //logger(TLOG_NOTICE, "\n%d, sended %d bytes! \n", g_vs_sock[sockid], len );
        }
        else
        {
            len = send( sockid, buf, ilen, 0 );
            //logger(TLOG_NOTICE, "\n%d, sended %d bytes \n", sockid, len );
        }
    */
    len = send( sockid, buf, ilen, 0 );

    if ( len < 0 )
    {
        logger(TLOG_ERROR,  "\nSocket send error! Code : %d, Info: '%s'\n", errno, strerror(errno) );
        return -1;
    }

    return 0;
}

int package_send( char *buf, int ilen, int type, int send_type, int socketid )
{
    if ( socketid != 0)
    {
        vs_send( socketid, buf, ilen );
    }
    else
    {
        if ( type == SENDTYPE_TCP )
        {
            vs_send( g_vs_sock[send_type], buf, ilen );
        }
    }
    return 0;
}


int listen_sock(int socket_id, int port)
{
    struct  sockaddr_in myaddr;
    int yes = 1;

    if ( setsockopt( socket_id, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof( int ) ) == -1 )
    {
        logger(TLOG_ERROR,  "\n vs_socket.c : setsockopt error! socket_id=%d\n", socket_id );
        return -1;
    }

    myaddr.sin_family = AF_INET;
    myaddr.sin_addr.s_addr = INADDR_ANY;
    myaddr.sin_port = htons( port );
    memset( &(myaddr.sin_zero), '\0', 8 );
    if ( bind( socket_id, (struct sockaddr *)&myaddr, sizeof(myaddr) ) == -1 )
    {
        logger(TLOG_ERROR,  "\n vs_socket.c : bind error! socket_id=%d\n", socket_id );
        return -1;
    }


    if ( listen( socket_id, 10 ) == -1 )
    {
        logger(TLOG_ERROR,  "\n vs_socket.c : listen error! socket_id=%d\n",  socket_id);
        return -1;
    }

    FD_SET( socket_id, &g_sock_fd );

    if (g_fd_max < socket_id)
    {
        g_fd_max = socket_id;
    }

    //logger(TLOG_NOTICE,  "\nvs_socket.c : Waitting connect with port %d and sock %d......\n", port, socket_id );
    return 0;
}

// 创建socket并监听
int socket_setup(int socket_port, int *socket_id)
{
    if (( *socket_id = socket( AF_INET, SOCK_STREAM, 0 )) == -1)
    {
        logger(TLOG_ERROR, "socket create error, socket_port=%d", socket_port);
        return -1;
    }
    if (listen_sock(*socket_id, socket_port) == -1)
    {
        logger(TLOG_ERROR, "socket listen error, socket_port=%d", socket_port);
        return -1;
    }

//	logger(TLOG_NOTICE, "socket:%d\n", socket_port);

    return 0;
}

int thread_socket_msg_main()
{
    fd_set	read_fds;
    struct  sockaddr_in remoteaddr;
    struct  timeval tv;
    int     socket_msg_id, socket_video_id;

    int     newfd;
    int     nbytes;
    int     addrlen;
    int     i;
    int     ret;

    g_fd_max = 0;
    FD_ZERO( &g_sock_fd );
    FD_ZERO( &read_fds );

    // 创建socket，并监听。如果出现错误，则停止所有其他线程。这个时候，整个应用程序停止，由RTU负责重启
    ret = socket_setup(MSGPORT, &socket_msg_id);
    if (ret != 0)
    {
        logger(TLOG_ERROR, "msg socket setup error, system will stop.");
        thread_syn_flag_set(&syn_ctrl_sys.mutex_r, &syn_ctrl_sys.cond_r, &syn_ctrl_sys.flag_r);
        return -1;
    }

    ret = socket_setup(VIDEOPORT, &socket_video_id);
    if (ret != 0)
    {
        logger(TLOG_ERROR, "video socket setup error, system will stop.");
        thread_syn_flag_set(&syn_ctrl_sys.mutex_r, &syn_ctrl_sys.cond_r, &syn_ctrl_sys.flag_r);
        return -1;
    }

    while ( !mapThreadID2Handler[THREAD_SOCKET].thread_quit_flag )
    {
#ifdef socket_debug2
        logger(TLOG_NOTICE, "thread_socket_main running:flag-%d.\n", mapThreadID2Handler[THREAD_SOCKET].thread_quit_flag);
#endif
        tv.tv_sec = 3;
        tv.tv_usec = 0;
        read_fds = g_sock_fd;
        ret = select( g_fd_max + 1, &read_fds, NULL, NULL, &tv );
        if (ret == -1)
        {
            logger(TLOG_ERROR, "socket select error, system will stop.");
            thread_syn_flag_set(&syn_ctrl_sys.mutex_r, &syn_ctrl_sys.cond_r, &syn_ctrl_sys.flag_r);
            return -1;
        }
        else if (ret == 0)
        {
            continue;
        }

        for (i = 0; i <= g_fd_max; i++)
        {
            if (FD_ISSET(i, &read_fds))
            {
                // 是否为监听SOCKET 的事件
                if ( i == socket_msg_id  || i == socket_video_id)
                {
                    addrlen = sizeof( remoteaddr );
                    if (( newfd = accept( i, ( struct sockaddr* )&remoteaddr, &addrlen )) == -1 )
                    {
                        logger(TLOG_ERROR, "socket accept error");
                    }
                    else
                    {
                        FD_SET( newfd, &g_sock_fd );
                        if ( newfd > g_fd_max )
                        {
                            g_fd_max = newfd;
                        }
                        logger(TLOG_NOTICE, "thread_socket_main:connect with %s(%d)", inet_ntoa(remoteaddr.sin_addr), newfd );
                    }
                }

                // 接收数据
                else
                {
                    nbytes = recv( i, buf, MAX_SOCKET_BUF_SIZE, 0);
                    if ( nbytes > 0 )
                    {
                        logger(TLOG_NOTICE, "thread_socket_main:%s(%d) send:%s.", inet_ntoa(remoteaddr.sin_addr), i, buf+sizeof(s_cmd_req_head));

                        *(int *)buf_inner = i;
                        memcpy(buf_inner+4, buf, nbytes);

                        // 将数据形成节点,加入到链表,并唤醒解析线程
                        receiver_core(buf_inner, nbytes+4);

                        memset(buf, 0, MAX_SOCKET_BUF_SIZE);
                        memset(buf_inner, 0, MAX_SOCKET_BUF_INNER_SIZE);
                    }
                    else if ( nbytes == 0 )
                    {
                        // 通知某个socket不再发送实时视频
                        rtv_user_end(i);
                        close( i );
                        FD_CLR( i, &g_sock_fd );

                        logger(TLOG_NOTICE, "Socket %d close", i);
                    }
                    else if ( nbytes < 0 )
                    {
                        // 通知某个socket不再发送实时视频
                        rtv_user_end(i);
                        close( i );
                        FD_CLR( i, &g_sock_fd );

                        logger(TLOG_NOTICE, "Socket %d recv error, errno=%d: %s.\n", i, errno, strerror(errno));
                    }
                }
            }
        }
    }

    logger(TLOG_NOTICE, "%s quit\n", __FUNCTION__);
    return 0;
}


int vs_connect_initiative( char *ip, int port, int *socket_id )
{
    struct sockaddr_in dest;

    if ( !ip || !port )
    {
        return -1;
    }

    if (( *socket_id = socket( AF_INET, SOCK_STREAM, 0 )) < 0 )
    {
        logger(TLOG_ERROR, "Vs_Connect_Initiative socket error!");
        return -1;
    }

    bzero( &dest, sizeof( dest ) );
    dest.sin_family = AF_INET;
    dest.sin_port = htons( port );
    if ( inet_aton( ip, (struct in_addr *)&dest.sin_addr.s_addr ) == 0 )
    {
        return -1;
    }

    ipc_setnoblocking(socket_id);

    if ( connect( *socket_id, (struct sockaddr *) &dest, sizeof(dest)) != 0)
    {
        logger(TLOG_ERROR,  "Vs_Connect_Initiative connet error!" );
        return -1;
    }

    return 0;
}

// 主动发送数据，不接受响应了。用于IPC的主动告警
int vs_send_initiative(char *buf, int len, char *ip, int port)
{
    int socket_id;

    if (0 != vs_connect_initiative(ip, port, &socket_id))
        return -1;

    if (0 != vs_send(socket_id, buf, len))
        return -1;

    close(socket_id);
    return 0;
}

int alert_send_start(int alert_type)
{
    if ((1 != alert_type)&&(2 != alert_type)&&(4 != alert_type))
        return -1;

    if (syn_ctrl_alarm.flag_r != 0)
        return -1;


    g_alart_type |= alert_type;
    thread_syn_flag_set(&syn_ctrl_alarm.mutex_r, &syn_ctrl_alarm.cond_r, &syn_ctrl_alarm.flag_r);
    return 0;
}


/* pgh 20100124 
*/
int thread_alert_send_main()
{

    while ( !mapThreadID2Handler[THREAD_ALERT_SEND].thread_quit_flag )
    {
        thread_syn_wait(&syn_ctrl_alarm.mutex_r, &syn_ctrl_alarm.cond_r, &syn_ctrl_alarm.flag_r);

        if (0 != (1 & g_alart_type))
        {
            rt_alarm_disk_set_req(NULL);
            g_alart_type = g_alart_type - 1;
        }
        if (0 != (2 & g_alart_type))
        {
            rt_md_report_set_req(NULL);
            g_alart_type = g_alart_type - 2;
        }
        if (0 != (4 & g_alart_type))
        {
            rt_alarm_error_set_req(NULL);
            g_alart_type = g_alart_type - 4;
        }

        thread_syn_flag_clr(&syn_ctrl_alarm.mutex_r, &syn_ctrl_alarm.cond_r, &syn_ctrl_alarm.flag_r);
    }

    return 0;
}

void dosfsck_sd()
{
    system("/ipc/html/cgi-bin/dosfsck  -v -a /dev/mmc/blk0/part1");
    return;
}

int thread_dosfsck_main()
{
    g_dosfscking = 0;
    system("/ipc/html/cgi-bin/dosfsck  -v -a /dev/mmc/blk0/part1");
//    sleep(4);
    
    while ( !mapThreadID2Handler[THREAD_DOSFSCK].thread_quit_flag )
    {   
        thread_syn_wait(&syn_ctrl_dosfsck.mutex_r, &syn_ctrl_dosfsck.cond_r, &syn_ctrl_dosfsck.flag_r);
        g_dosfscking = 1;
		logger(TLOG_WARNING, "dosfsck start to repair sd card");
		system("/ipc/html/cgi-bin/dosfsck  -v -a /dev/mmc/blk0/part1");
		logger(TLOG_WARNING, "dosfsck repair done");
		
	   	sleep(4);
		g_config.sys_quit.flag.var = 0;
		sys_quit();

		g_dosfscking = 0;
		
        thread_syn_flag_clr(&syn_ctrl_dosfsck.mutex_r, &syn_ctrl_dosfsck.cond_r, &syn_ctrl_dosfsck.flag_r);
    }

    return 0;
}

int file_del_start()
{
    if (syn_ctrl_del.flag_r != 0)
        return -1;

	g_deling = 1;
    thread_syn_flag_set(&syn_ctrl_del.mutex_r, &syn_ctrl_del.cond_r, &syn_ctrl_del.flag_r);
    return 0;
}

#if 0
int call_rm_exe()
{
    char szProcname[]="/bin/rm";
    char *Para[]={"/bin/rm", "-rf", "/ipc/ipc_data/*", NULL};
    int ret;

    printf("ffffffffffffffffffffffffffffffffffffff\n");
//    ret = execvp(szProcname,Para);
    ret = execlp("rm", "rm", "-rf", "/ipc/ipc_data/*", NULL);
//	ret = execlp("ls", "ls", "-lh", NULL);
    logger(TLOG_NOTICE, "execl returnnnnnnnnnnnnnnnnnnnnnn ret=%d.", ret);
    if (-1 == ret)
    {
        // 打印执行程序名称和执行参数
        logger(TLOG_ERROR, "call_exe failed.");
    }
    printf("aaaaaaaaaaaaaaaaaaaaaaaa\n");    // pgh!!! 这句会让整个程序kill, why!!!!!!!!!
    logger(TLOG_NOTICE, "execl return ret=%d.", ret);

    return ret;
}



int file_del_core()
{

    int status;
    int n;
    int ret;
    char szProcname[]="/sbin/rm";
    char *Para[]={"-fR", "/ipc/ipc_data", NULL};


    ret = call_exe();
    if (-1 == ret)
    {
        logger(TLOG_ERROR, "call_exe failed!");
        return -1;
    }

    // 等待该外部程序结束
    if ((n = wait(&status)) < 0)
    {
        logger(TLOG_ERROR, "file_del_core, Waitpid error : %s", strerror(errno));
        return -1;
    }
    ret == WEXITSTATUS(status);
    logger(TLOG_NOTICE, "file_del_core, child process return=%d", ret);
    return 0;
}

int file_del_core(void)
{
    int ret;
    pid_t pid_del;

    pid_del = fork();
    if (pid_del < 0)
    {
        logger(TLOG_ERROR, "Unable to fork!");
        return -1;
    }
    if (pid_del > 0)
    {
        int status;

        int n;

        if ((n = waitpid(pid_del, &status, 0)) < 0)
        {
            logger(TLOG_ERROR, "Waitpid error : %s", strerror(errno));
//           exit(0);
            return pid_del;
        }

        ret == WEXITSTATUS(status);
        logger(TLOG_NOTICE, "del process return ret=%d", ret);
        return ret;
    }
    else
    {
        logger(TLOG_NOTICE, "bbbbbbbbbbbbbbbbbbbbbbbb");
        call_rm_exe();
        return 0;
    }
    return 0;

}

#endif

int file_del_core()
{

    int status;

	static int del_count = 0;
	
rmdirs:
	if(del_count++ == 3){
		logger(TLOG_ERROR, "disk del error, ipc will restart.");
		sys_quit();
	}
	
    status = 0;
    errno = 0;
	sync();
	sleep(2);
    status  = system("rm -fr /ipc/ipc_data/*");

//	status  = remove("/ipc/ipc_data/");
    if (status == -1)
    {
        logger(TLOG_ERROR, "execute rm error:%d-%s\n", errno, strerror(errno));
        goto rmdirs;
    }
    if (!WIFEXITED(status))
    {
        logger(TLOG_ERROR, "rm run error:%d,%d-%s\n", status, errno, strerror(errno));
        goto rmdirs;
    }

    if (WEXITSTATUS(status) != 0)
    {
        logger(TLOG_NOTICE, "rm failed:%d,%d-%s\n", status, errno, strerror(errno));
        goto rmdirs;
    }
	del_count = 0;
	
    dir_constrcut();
    logger(TLOG_WARNING, "disk mkdiiiiiiiiiiiiiiiiiiiiiir done\n");

}



int thread_file_del_main()
{

    while ( !mapThreadID2Handler[THREAD_FILE_DEL].thread_quit_flag )
    {
        thread_syn_wait(&syn_ctrl_del.mutex_r, &syn_ctrl_del.cond_r, &syn_ctrl_del.flag_r);

        g_deling = 1;
//        printf("dddddddddddddddddddddddddddddddddddddddddddddddddddddddddd\n");
//		system("rm -rf /ipc/ipc_data/*");
        file_del_core();
//	call_rm_exe();
//        printf("XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n");
        g_deling = 0;

        thread_syn_flag_clr(&syn_ctrl_del.mutex_r, &syn_ctrl_del.cond_r, &syn_ctrl_del.flag_r);
    }

    return 0;
}




#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

