#ifndef __VS_TIMER_H__
#define __VS_TIMER_H__


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */


#include <time.h>
#include <stdio.h>
#include <signal.h>
#include <pthread.h>  

//#include "vs_def_videoProtocol_3.h"
//#include "vs_def_dataType.h"

#define SIGMYTIMER (SIGRTMAX)

#define MAX_TIMER_NODE_NUM     30           // timer等待队列中节点最大数量: 0 ~ 30

typedef int(*CallBack_operation_timer)(void *data);

/***************************************************************************************************************
**** timer链表节点
**** 1. tm_first      :timer第一次到期时刻,2007.11.19 21:10:09
**** 2. tm_intervel   : 重复型timer的间隔时间, 如每300秒进行一次抓拍
**** 3. mode          : timer的重复次数，0: 永久型timer   1: 单次型timer　　n:重复n次型timer
                        单次型timer: (1) 根据当前时间和到第一次到期时刻，计算需要等待的秒数，启动单次timer
                        重复型timer: (1) 根据当前时间和第一次到期时刻，计算需要等待的秒数，启动单次timer
                                     (2) n = n-1;并且重新计算下一次的到期时刻，插入到等待队列中，直到变成单次型timer

**** 4. *timer_handler: timer对应的处理函数。目前为了统一管理，采用相同的回调函数。
***************************************************************************************************************/

typedef struct tag_timer_usr_data               // 外部用户需要发送给timer接口函数的数据
{
    int mode;                                   // timer的重复次数，0: 永久型timer   1: 单次型timer　　n:重复n次型timer
    time_t tm_first;                            // timer第一次到期时刻
    int tm_intervel;                            // 重复型timer的间隔时间    
    int tm_id;                                 // timer id和队列中的timer一一对应，并返回给调用者。调用者今后可以使用id号来删除还没到期的timer
    CallBack_operation_timer timer_handler;                        // timer对应的处理函数
    void *timer_handler_data;
} s_timer_usr_data;

typedef struct tag_timer_chain_node 
{
    s_timer_usr_data timer_usr_data;
    struct tag_timer_chain_node *pre;
    struct tag_timer_chain_node *next;   
} s_timer_chain_node;

// timer管理全局变量
typedef struct tag_timer_manager_data
{
    int flag_wait;                              // timer管理主线程是否等待标志
    pthread_mutex_t mutex_chain_opt;            // 对timer链表操作的互斥量
    pthread_mutex_t mutex_wait;                 // 用于读写线程的同步
    pthread_cond_t cond_wait;
    int node_num;                               // 等待队列的节点数，包括删除的节点。节点数量: 0 -- 100, 循环
    int timer_id;                               // 此timer_id,永远只做加运算
}s_timer_manager_data;

/******************************************************************************************************************/
int vs_printf_timer_queue();
int timer_flag_wait_set();
int timer_flag_wait_clear();
int timer_chain_node_add(s_timer_usr_data *timer_usr_data);          // 向timer等待队列中增加一个timer,此函数提供给外部模块调用。
int timer_chain_node_del_by_timerid(int timer_id);                   // 向timer等待队列中删除一个timer,此函数提供给外部模块调用。    
int timer_usr_data_cp(s_timer_chain_node *timer_chain_node_new,s_timer_usr_data *timer_usr_data);
void timer_sinal_timer_handler();
int timer_signal_timer_add(int it_sec);
int timer_add(int it_sec, CallBack_operation_timer handler);
int timer_chain_node_instert(s_timer_usr_data *timer_usr_data);          // 在timer链中插入一个节点
int timer_chain_free();
int timer_chain_node_delete();                                       // 在timer链中删除第一个节点
int timer_get_frist_node_wt(time_t *time_wait);                            // 获取第一个节点的等待时间 = 第一个节点的到期时间 - 当前系统时间                        
int timer_chain_node_handler();                                       // 获得等待队列的第一个节点，到期，则执行相应操作,处理完毕，从等待队列中删除此节点，返回0,未到期，则返回需要还需要等待的秒数,返回值>0
int vs_timer_chain_init();                                                  // 初始化timer链，建立根节点
int vs_timer_add(int second, int mode,int *timer_id );                   //　加入当前时间起的second秒到期的1次性timer
int vs_timer_add2(int mode,time_t second, int tm_intervel, void *handler, void *handler_data,int *timer_id);       
int vs_timer_del(int timer_id);                                             // 删除timer_id对应的timer
int thread_timer_main();

/******************************************************************************************************************/
#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __VS_TIMER_H__ */

