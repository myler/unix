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
extern "C"{
#endif
#endif /* __cplusplus */

#include <stdlib.h>      // for exit()
#include <unistd.h>     // for sleep()
#include <stdio.h>
#include <pthread.h>

#include "vs_thread.h"
#include "logger.h"
#include "watchdog.h"

//#define THREAD_NUM_MAX		6

extern int thread_socket_msg_main();
extern int thread_parser_main();
extern int thread_usb_monitor_main();
extern int thread_rtv_main(int *param);
extern int thread_rtv_send_main(int *param);
extern int thread_cgi_main();
extern int thread_alert_send_main();
extern int thread_file_del_main();
extern int thread_watchdog_main();
extern int thread_dosfsck_main();
//extern  void thread_timer_test();
//extern  void thread_timer_test2();
//extern int thread_sd_mount();

/* 线程编号,handler对应表   */
s_mapThreadID2Handler  mapThreadID2Handler[THREAD_NUM_MAX]=
{
		{	THREAD_SOCKET     ,     0,	    thread_socket_msg_main	},
		{	THREAD_PARSER     , 	0,		thread_parser_main	 	},
		{	THREAD_USB_MONITOR  , 	0,		thread_usb_monitor_main },
		{	THREAD_RTV_0        , 	0,		thread_rtv_main	        },
		{	THREAD_RTV_SEND_0	,	0,		thread_rtv_send_main	},
		//{	THREAD_RTV_1        , 	0,		thread_rtv_main	        },
		//{	THREAD_RTV_SEND_1	,	0,		thread_rtv_send_main	},
		{	THREAD_CGI			,	0,		thread_cgi_main			},
		{	THREAD_ALERT_SEND	,  	0, 		thread_alert_send_main	},
		{	THREAD_FILE_DEL		,  	0, 		thread_file_del_main	},
		{	THREAD_WATCHDOG		,  	0, 		thread_watchdog_main	},
		{	THREAD_DOSFSCK		,  	0, 		thread_dosfsck_main	    }
		
};

/*   数组threadID[] 中存放所有线程ID */
pthread_t threadID[THREAD_NUM_MAX];
//int  num_threadID = 0;

extern s_watchdog_idevent2idthread g_watchdog_idevent2idthread[ID_EVENT_BUTT];


/****************************************************************************************************/

/* 查线程编号，handler对应表，返回匹配数组单元号  */
static int getHandlerMatch(int threadID)
{
	int i;

	for(i=0; mapThreadID2Handler[i].threadHandler!= NULL; i++)
		if(threadID == mapThreadID2Handler[i].threadID)
			return i;
	return -1;

}

 /*等待所有线程结束*/
void thread_wait(void)
{
	int i;
	for(i = 0; i < THREAD_NUM_MAX; i++){
		pthread_join(threadID[i], NULL);
		logger(TLOG_NOTICE, "线程%d停止\n", i);
	}
	logger(TLOG_NOTICE, "system halt\n");
	return;
}

//#define debug_printf_thread_create 1

/* 创建线程 */
int thread_create(void *handler, int num_threadID, void *param)
{
	int ret;
//	int pid;
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setscope(&attr, PTHREAD_SCOPE_SYSTEM);
//	pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED);
	ret=pthread_create(&(threadID[num_threadID]),&attr,handler,param);
	if(ret!=0){

#ifdef debug_printf_thread_create
		printf ("Create pthread error!\n");
#endif

	    return -1;
	}

#ifdef debug_printf_thread_create
	logger(TLOG_NOTICE, "线程创建成功，线程号=%d\n",threadID[num_threadID]);
#endif

//	num_threadID++;
	return 0;

}

/* 根据不同的线程编号，查编号，handler对应表，得到线程入口，创建相应线程
     线程ID号与线程入口函数定义见vs_def.h  */
int vs_thread_create(int threadID, void *param)
{
	int *handler;
	int ret;
	int num_mapThreadID2Handler;
	
	handler = 0;

	num_mapThreadID2Handler = getHandlerMatch(threadID);
	if(num_mapThreadID2Handler < 0)
		return -1;

	mapThreadID2Handler[num_mapThreadID2Handler].thread_quit_flag = 0;
	handler = mapThreadID2Handler[num_mapThreadID2Handler].threadHandler;

//	logger(TLOG_NOTICE, "%d", threadID);
	ret = thread_create(handler, threadID, param);
	
	return 0;
}

// 根据id号得到线程退出控制变量，并将其置1,使线程主动退出
int vs_thread_stop(int threadID)
{
	int num_mapThreadID2Handler;

	num_mapThreadID2Handler = getHandlerMatch(threadID);
	if(num_mapThreadID2Handler < 0)
		return -1;
    mapThreadID2Handler[num_mapThreadID2Handler].thread_quit_flag = 1;    
		
    return 0;
}

int thread_stop_all()
{
    int i;

    for(i=0; i<THREAD_NUM_MAX; i++)
    {
        vs_thread_stop(i);
    }

    return 0;
}

int thread_cancel(int num)
{
    int ret;
	int threadID_rtv, threadID_send;

	threadID_rtv = g_watchdog_idevent2idthread[num].id_thread;
	threadID_send = g_watchdog_idevent2idthread[num].id_thread_send;
	
    ret = pthread_cancel(threadID[threadID_rtv]);
    if(0 == ret)
    {
        // pgh， 注意rtv线程取消对发送线程的影响，还有代码需要添加   
        logger(TLOG_WARNING, "thread cancel success! ipc id_thread=%d, real pthread_i=%d\n", threadID_rtv, threadID[threadID_rtv]);
		ret = pthread_cancel(threadID[threadID_send]);
		if(0 == ret)
		{
			logger(TLOG_WARNING, "thread cancel success! ipc id_thread=%d, real pthread_i=%d\n", threadID_send, threadID[threadID_send]);
			return 0;
		}
		else
		{
        // pgh , 应该取消的send线程没有取消掉，这里应该停止整个进程
	        logger(TLOG_ERROR, "thread cancel failed! ipc id_thread=%d, real pthread_i=%d\n", threadID_send, threadID[threadID_send]);
			sys_quit();
			return -1;
    	}
		
    }
    else
    {
        // pgh , 应该取消的rtv线程没有取消掉，这里应该停止整个进程
        logger(TLOG_ERROR, "thread cancel failed! ipc id_thread=%d, real pthread_i=%d\n", threadID_rtv, threadID[threadID_rtv]);
		sys_quit();
		return -1;
    }
    
    
    
    return 0;
}

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
