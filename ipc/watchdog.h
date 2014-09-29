#ifndef __WATCHDOG_H__
#define __WATCHDOG_H__

#include <fcntl.h>
#include <pthread.h>

#define ID_WATCHDOG_EVENT_MAX      2       // 两路视频事件
//#define ID_WATCHDOG_

typedef enum {
	ID_EVENT_RTV_0 = 0,
	ID_EVENT_RTV_1,
	ID_EVENT_BUTT
} e_watchdog_event;

typedef struct tag_watchdog_event
{
    pthread_mutex_t mutex;
    int event_enable;                   //  watchdog 启动: 0 没有启动，不需要watchdog检查; 1已经启动，需要检查
    int event_counter; 
} s_watchdog_event;

typedef struct tag_watchdog_idevent2idthread
{
    int id_event;
    int id_thread;   
	int id_thread_send;
} s_watchdog_idevent2idthread;

#endif