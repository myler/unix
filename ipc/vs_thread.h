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


#ifndef __VS_THREAD_H__
#define __VS_THREAD_H__


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */


#define THREAD_NUM_MAX		12
/*  线程序号定义       */
#define THREAD_SOCKET  	            0
#define THREAD_PARSER    			1
#define THREAD_USB_MONITOR			2
#define THREAD_RTV_0  	            3
#define THREAD_RTV_SEND_0			4
#define THREAD_RTV_1  	            5
#define THREAD_RTV_SEND_1			6
#define THREAD_CGI  	            7
#define THREAD_ALERT_SEND			8
#define THREAD_FILE_DEL  			9
#define THREAD_WATCHDOG             10
#define THREAD_DOSFSCK             11

/*  线程序号，handler对应表   */
typedef void  (*s_threadHandler)(); 
typedef struct tagMapThreadID2Handler
{
	int threadID;
	int thread_quit_flag;       // 线程主动退出标志,置1时退出该线程
	void *threadHandler;
} s_mapThreadID2Handler;

extern s_mapThreadID2Handler  mapThreadID2Handler[];
void thread_wait(void);
int thread_create(void *handler, int num_threadID, void *param);
int vs_thread_create(int threadID, void *param);
int thread_stop_all();
int thread_cancel(int id_thread);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __VS_THREAD_H__ */

