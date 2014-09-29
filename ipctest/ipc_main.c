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

//wxw

#ifdef __cplusplus
#if __cplusplus
extern "C"
{
#endif
#endif /* __cplusplus */


#include <stdio.h>
#include <semaphore.h>
#include <signal.h>
#include <pthread.h>
#include <stdlib.h>             // for system()
#include <sys/reboot.h>         // for reboot(RB_AUTOBOOT)
#include <errno.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/wait.h>


#include "vs_thread.h"
#include "vs_socket.h"
#include "config.h"
#include "vs_sd.h"
#include "sem.h"
#include "logger.h"
#include "rtv.h"
#include "timer_handler.h"
#include "vs_save.h"

extern pthread_t threadID[THREAD_NUM_MAX];

pid_t mainpid = -1;		/* 主进程的pid */

s_syn_ctrl syn_ctrl_sys;
s_syn_ctrl syn_ctrl_parse;
s_syn_ctrl syn_ctrl_rtv;
s_syn_ctrl syn_ctrl_alarm;
s_syn_ctrl syn_ctrl_del;
s_syn_ctrl syn_ctrl_watchdog;
s_syn_ctrl syn_ctrl_dosfsck;

struct vdIn videoIn[2];
s_syn_ctrl frame_syn_ctrl[2][OUTFRMNUMB];


int channel_0 = 0;
int channel_1 = 1;

int sd_mount_ret;

int thread_start()
{
    int ret = 0;

    ret = vs_thread_create(THREAD_SOCKET, NULL);   // 网络通信线程
    if (ret!=0)
        return ret;

    ret = vs_thread_create(THREAD_PARSER, NULL);   // 消息解析线程
    if (ret!=0)
        return ret;

    ret = vs_thread_create(THREAD_USB_MONITOR, NULL);   // USB设备监控线程
    if (ret!=0)
        return ret;
	
	ret = vs_thread_create(THREAD_CGI, NULL);      // CGI服务线程
    if (ret!=0)
        return ret;

	ret = vs_thread_create(THREAD_RTV_SEND_0, &channel_0);      // RTV发送服务线程1
    if (ret!=0)
        return ret;

   // ret = vs_thread_create(THREAD_RTV_SEND_1, &channel_1);      // RTV发送服务线程1
   // if (ret!=0)
     //   return ret;


    ret = vs_thread_create(THREAD_ALERT_SEND, NULL);      // 报警线程
    if (ret!=0)
        return ret;

	ret = vs_thread_create(THREAD_FILE_DEL, NULL);      // 删除线程
    if (ret!=0)
        return ret;

	vs_thread_create(THREAD_WATCHDOG, NULL);      // watchdog服务线程
	if (ret!=0)
        return ret;
	
    vs_thread_create(THREAD_DOSFSCK, NULL);      // dosfsck服务线程
	if (ret!=0)
        return ret;
      
	
    vs_thread_create(THREAD_RTV_0, &channel_0);      // RTV服务线程1
    vs_thread_create(THREAD_RTV_1, &channel_1);      // RTV服务线程1

	

	
    //	pthread_detach(threadID[THREAD_RTV_0]);
    //	pthread_detach(threadID[THREAD_RTV_1]);
    return ret;

}

void rtv_syn_init(int channel)
{
    int i;
    for (i = 0; i < OUTFRMNUMB; i++)
    {
        thread_syn_init(&frame_syn_ctrl[channel][i].mutex_r,
                        &frame_syn_ctrl[channel][i].cond_r,
                        &frame_syn_ctrl[channel][i].flag_r);
        thread_syn_init(&frame_syn_ctrl[channel][i].mutex_w,
                        &frame_syn_ctrl[channel][i].cond_w,
                        &frame_syn_ctrl[channel][i].flag_w);
    }
}

int ipc_init()
{
    int j;

    if (config_read("/etc/ipc.conf") != 0)
    {
        logger(TLOG_ERROR, "configure file load failed.\n");
        return -1;
    }
	thread_syn_init(&syn_ctrl_parse.mutex_r, &syn_ctrl_parse.cond_r, &syn_ctrl_parse.flag_r);
    thread_syn_init(&syn_ctrl_sys.mutex_r, &syn_ctrl_sys.cond_r, &syn_ctrl_sys.flag_r);
    thread_syn_init(&syn_ctrl_rtv.mutex_r, &syn_ctrl_rtv.cond_r, &syn_ctrl_rtv.flag_r);
	thread_syn_init(&syn_ctrl_alarm.mutex_r, &syn_ctrl_alarm.cond_r, &syn_ctrl_alarm.flag_r);
	thread_syn_init(&syn_ctrl_del.mutex_r, &syn_ctrl_del.cond_r, &syn_ctrl_del.flag_r);
	thread_syn_init(&syn_ctrl_watchdog.mutex_r, &syn_ctrl_watchdog.cond_r, &syn_ctrl_watchdog.flag_r);
	thread_syn_init(&syn_ctrl_dosfsck.mutex_r, &syn_ctrl_dosfsck.cond_r, &syn_ctrl_dosfsck.flag_r);
	

    for (j = 0; j < 2; j++)
    {
		rtv_syn_init(j);
    }
	timer_init();
	
    return 0;
}


int main_core(void)
{
    int ret;

//    system("ulimit -m 20480");
	logger(TLOG_NOTICE, "IPC core begin to run");
	
    ret = ipc_init();
    if (ret !=0)
    {
        logger(TLOG_ERROR, "ipc init failed, ipc core closed.");
        return -1;
    }

    ret = thread_start();
    if (ret!=0)
    {
        logger(TLOG_ERROR, "thread create failed, ipc core closed.");
        return -1;
    }

	sd_init(10);
	dir_constrcut();						// 建立当天的文件夹

	thread_syn_wait(&syn_ctrl_sys.mutex_r, &syn_ctrl_sys.cond_r, &syn_ctrl_sys.flag_r);
    logger(TLOG_NOTICE, "all threads finished, ipc core closed.");

	if(1 == g_config.sys_quit.flag.var){
		logger(TLOG_WARNING, "ipc core exit 1, ipc exit normal");
    	exit(1);						// 手动要求退出ipc，后续主进程不重启该进程
	}
	else{
		logger(TLOG_WARNING, "ipc core exit 0, ipc exit error, ipc will restart");
		exit(0);						// 异常ipc退出，后续主进程重启该进程
	}
}

/* 主函数 */
int main(void)
{
	logger(TLOG_NOTICE, "IPC start now");
  monitor:
//    daemon(1, 0);

    mainpid = fork();
    if (mainpid < 0) {
	logger(TLOG_ERROR, "Unable to fork!");
	exit(-1);
    }
    if (mainpid > 0) {
	int status;

	int n;

	if ((n = waitpid(mainpid, &status, 0)) < 0) {
	    logger(TLOG_ERROR, "Waitpid error : %s", strerror(errno));
	    exit(0);
	    
	}
/*
	if(1 == g_config.sys_quit.flag.var){
		logger(TLOG_WARNING, "child process stop=%d\n", g_config.sys_quit.flag.var);
		return 0;
    } else 
    	{
    		logger(TLOG_WARNING, "child process stop=%d\n", g_config.sys_quit.flag.var);
			goto monitor;
    	}
	
*/
//	if (WIFEXITED(status)) {
	    if (1 == WEXITSTATUS(status)) {
			logger(TLOG_WARNING, "child process return=%d", 1);
			return 0;
	    } else 
	    	{
	    		logger(TLOG_WARNING, "child process return=%d", 0);
				goto monitor;
	    	}
		
//	}

/*
	if (WIFSIGNALED(status)) {
	    logger(TLOG_WARNING,
		   "Automatically restarting netcrosser! \n");
	    goto monitor;
	}
*/
    } else 
    {
        main_core();
        return 0;
    }
    return 0;

}

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

