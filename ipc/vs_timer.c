#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

#include <string.h>
#include <stdlib.h>   		// for malloc()
#include <unistd.h>         // for sleep()
#include <sys/time.h>         // for setitimer()
#include <time.h>
#include <signal.h>         // for signal()

//#include "vs_main_rountin.h"
//#include "vs_config.h"
#include "vs_timer.h"
#include "logger.h"

s_timer_chain_node  g_timer_chain_node_root;
s_timer_manager_data g_timer_manager_data;
// timer_t IDList[20]; //use to save timer id;

int     g_quit_timer = 0;    // 置1 时退出timer_main 线程


// 获取到当前时间的最近的整点时间的秒数
int timer_next_hour_get(time_t time, int *second)
{
    int ret;
    struct tm *p;

    ret = timer_hour_judge(time);
    if(0 == ret)
    {
        *second = 0;
        return 0;
    }

    p = gmtime( &time );
    *second =(60 - p->tm_min -1) * 60 + (60 - p->tm_sec);
    return 0;
}

// 判断给定的time是否为整点 返回值 0, 整点 1,非整点
int timer_hour_judge(time_t time)
{   
    int ret;
    struct tm *p;
    
    p = gmtime( &time );  
    ret = p->tm_min;
    if(0 != ret)
        return 1;
    ret = p->tm_sec;
    if(0 != ret)
        return 1;
        
    return 0;
}


// 打印当前timer队列的节点号
int vs_printf_timer_queue()
{
    s_timer_chain_node *ptimer_node;            // timer节点指针

//    logger(TLOG_NOTICE, "*** 当前timer队列节点:");
    
    ptimer_node = g_timer_chain_node_root.next;   
    while(NULL != ptimer_node)
    {
//        logger(TLOG_NOTICE, "%d, ", ptimer_node->timer_usr_data.tm_id);
        ptimer_node = ptimer_node->next;
    }
//    logger(TLOG_NOTICE, "\n");

    return 0;
}

int timer_flag_wait_set()
{
    pthread_mutex_lock(&g_timer_manager_data.mutex_wait);
    g_timer_manager_data.flag_wait= 1;
    pthread_cond_signal(&g_timer_manager_data.cond_wait);
    pthread_mutex_unlock(&g_timer_manager_data.mutex_wait);
    return 0;
}

int timer_flag_wait_clear()
{
    pthread_mutex_lock(&g_timer_manager_data.mutex_wait);
    g_timer_manager_data.flag_wait= 0;
    pthread_cond_signal(&g_timer_manager_data.cond_wait);
    pthread_mutex_unlock(&g_timer_manager_data.mutex_wait);
    return 0;
}

// 获取第一个节点的等待时间 = 第一个节点的到期时间 - 当前系统时间
int timer_get_frist_node_wt(time_t *time_wait)
{
    time_t time_current; 
    s_timer_chain_node *timer_chain_node_frist;
    
    timer_chain_node_frist = g_timer_chain_node_root.next;

    // 判断timer链表是否为空。前面的阻塞机制应该使得该情况不会发生。
    if(timer_chain_node_frist == NULL)
    {
        logger(TLOG_ERROR, "第一个节点为空,无法获取第一个节点的等待时间\n");
        return 1;
    }
 
    time_current = time((time_t *)NULL);
    *time_wait = timer_chain_node_frist->timer_usr_data.tm_first- time_current;

    return 0;
}


int timer_usr_data_cp(s_timer_chain_node *timer_chain_node_new,s_timer_usr_data *timer_usr_data)
{
    timer_chain_node_new->timer_usr_data.mode = timer_usr_data->mode;
    timer_chain_node_new->timer_usr_data.tm_first = timer_usr_data->tm_first;
    timer_chain_node_new->timer_usr_data.tm_id = timer_usr_data->tm_id;
    timer_chain_node_new->timer_usr_data.tm_intervel = timer_usr_data->tm_intervel;
    timer_chain_node_new->timer_usr_data.timer_handler = timer_usr_data->timer_handler;
    timer_chain_node_new->timer_usr_data.timer_handler_data = timer_usr_data->timer_handler_data;
    
    return 0;
}


void timer_sinal_timer_handler()
{
#ifdef debug_printf_timer
//    logger(TLOG_NOTICE, "发送信号的timer到期\n");
#endif

    return ;
}

// 添加一个到时发送信号的timer
// 此函数用于插入的新节点在第一个节点之前的时候，调用此函数增加一个n秒的timer。
// 此timer单独存在，不加到timer模块的链表中。到时发送alarm信号，来中断主timer线程
// 用此函数是个权宜之计，本来应该在插入的新节点在第一个节点之前的时候，直接发送alarm信号，来中断主timer线程
// 但是，目前不知道怎么直接发送信号
int timer_add(int it_sec, CallBack_operation_timer handler)
{
    struct itimerval value;

    signal(SIGALRM, handler);//timer_sinal_timer_handler);   
    //value.it_interval.tv_sec = it_sec;
    value.it_interval.tv_sec = 0;
    value.it_interval.tv_usec = 0;
    value.it_value.tv_sec = it_sec;
    value.it_value.tv_usec = 0;
    setitimer(ITIMER_REAL, &value, NULL);

    return 0;
}

int timer_signal_timer_add(int it_sec)
{
    struct itimerval value;

    signal(SIGALRM, timer_sinal_timer_handler);   
    //value.it_interval.tv_sec = it_sec;
    value.it_interval.tv_sec = 0;
    value.it_interval.tv_usec = 0;
    value.it_value.tv_sec = it_sec;
    value.it_value.tv_usec = 0;
    setitimer(ITIMER_REAL, &value, NULL);

    return 0;
}

// 向timer等待队列中增加一个timer,此函数提供给外部模块调用。
int timer_chain_node_add(s_timer_usr_data *timer_usr_data)
{
    timer_chain_node_instert(timer_usr_data);
    
    return 0;
}


// 清空timer链，应sx要求，专门提供此函数；用于在强行推出前，free所有节点 ; pgh ,今后在强行终止程序时记得调用此函数
int timer_chain_free()
{
    s_timer_chain_node *p_timer_chain_node_cur;             // 当前节点
    s_timer_chain_node *p_timer_chain_node_pre;
    s_timer_chain_node *p_timer_chain_node_next;

    p_timer_chain_node_cur = g_timer_chain_node_root.next;
    if(p_timer_chain_node_cur == NULL)
        return 0;

    while(p_timer_chain_node_cur != NULL)
    {
        p_timer_chain_node_pre = p_timer_chain_node_cur->pre;
        p_timer_chain_node_next = p_timer_chain_node_cur->next;
        if(p_timer_chain_node_next != NULL)
        {
            p_timer_chain_node_next->pre = p_timer_chain_node_pre;
        }
       
        p_timer_chain_node_pre->next = p_timer_chain_node_next;
        g_timer_manager_data.node_num--;
        free(p_timer_chain_node_cur);

        p_timer_chain_node_cur = p_timer_chain_node_next;
    }

    return 0;
}


// 向timer等待队列中删除一个timer,此函数提供给外部模块调用。
// 当删除的节点为第一个节点的时候，发信号, 使timer主线程中断sleep  timer_signal_timer_add(1);    
// 返回值: 0, 未找到匹配id, 1: 匹配，并已经删除
int timer_chain_node_del_by_timerid(int timer_id)
{
    int match;                              // 是否找到timer_id相同的节点

    match = 0;
    s_timer_chain_node *p_timer_chain_node_cur;             // 当前节点
    s_timer_chain_node *p_timer_chain_node_pre;
    s_timer_chain_node *p_timer_chain_node_next;
    
    p_timer_chain_node_cur = g_timer_chain_node_root.next;

    if(p_timer_chain_node_cur == NULL)
    {
#ifdef debug_printf_timer
        logger(TLOG_ERROR, "当前timer队列空，无法删除指定timer，timer_id=%d\n", timer_id);
#endif
        return match;
    }    
    
    // 查找节点，并删除
    while(p_timer_chain_node_cur != NULL)
    {
        if(p_timer_chain_node_cur->timer_usr_data.tm_id != timer_id)
        {
            p_timer_chain_node_cur = p_timer_chain_node_cur->next;
        }
        else
        {
            match = 1;

            // 将要删除的节点为第一个节点的时候，发信号, 使timer主线程中断sleep  
            if(p_timer_chain_node_cur == g_timer_chain_node_root.next)
                timer_signal_timer_add(1);
        
            p_timer_chain_node_pre = p_timer_chain_node_cur->pre;
            p_timer_chain_node_next = p_timer_chain_node_cur->next;
            if(p_timer_chain_node_next != NULL)
            {
                p_timer_chain_node_next->pre = p_timer_chain_node_pre;
            }
           
            p_timer_chain_node_pre->next = p_timer_chain_node_next;
            g_timer_manager_data.node_num--;
            free(p_timer_chain_node_cur);

#ifdef debug_printf_timer
            logger(TLOG_NOTICE, "timer_chain_node_del_by_timerid(),队列中直接删除节点成功,节点号=%d\n",timer_id);       
#endif
#ifdef debug_printf_timer_queue
            vs_printf_timer_queue();
#endif

            // 如果timer链空，设置等待标志
            if(g_timer_chain_node_root.next == NULL)
                timer_flag_wait_set();
            
            break; 
        }                
    }

    if(0 == match)
    {
#ifdef debug_printf_timer
            logger(TLOG_NOTICE, "当前timer队列不空，但是找不到指定timer，timer_id=%d\n", timer_id);  
#endif
    }


    return match;
}

// 在timer链中插入一个节点
// timer链表按到期的时间先后顺序排序
// 当插入的节点在第一个节点前的时候，需要发信号，使timer主线程中断sleep
int timer_chain_node_instert(s_timer_usr_data *timer_usr_data)
{
    s_timer_chain_node *p_timer_chain_node_new;             // 要插入的节点指针
    s_timer_chain_node *p_timer_chain_node_cur;             // timer链搜索时的每个节点的指针
    s_timer_chain_node *p_timer_chain_node_pre;             // 当前节点的前一个节点
    int nofind;

    // 因为对于多次型timer,需要在删除节点前加入一个后续节点，所以为了简化，这里使用最大值-1
    if((g_timer_manager_data.node_num + 1) == MAX_TIMER_NODE_NUM)
    {
        logger(TLOG_NOTICE, "增加timer失败，timer队列已经达到上限值\n");
        return 1;
    }
    
    // 申请空间
    p_timer_chain_node_new = (s_timer_chain_node *)malloc(sizeof(s_timer_chain_node));
    if(p_timer_chain_node_new == NULL)
    {
        logger(TLOG_NOTICE, "增加timer失败，内存分配失败\n");
        return 1;
    }

    // 获得timer_id
    timer_usr_data->tm_id = g_timer_manager_data.timer_id;  
    g_timer_manager_data.timer_id++;
    
    // 拷贝数据
    timer_usr_data_cp(p_timer_chain_node_new,timer_usr_data);      
    p_timer_chain_node_new->pre = NULL;
    p_timer_chain_node_new->next = NULL;
   
    // 搜索timer链表，插入节点。
    // timer链表按expire_time的时间先后顺序排序，目前搜索顺序为从前向后，今后优化可改成从后向前。
    nofind = 1;
    p_timer_chain_node_cur = g_timer_chain_node_root.next;
  
    // 在p_timer_chain_node_cur节点前插入新节点,如果链表为空链表，直接插入到根后
    // 这个时候，timer线程应该正在被阻塞住，而不是在sleep,所以不需要发信号来中断sleep
    if(p_timer_chain_node_cur == NULL)
    {
        p_timer_chain_node_new->next = NULL;
        g_timer_chain_node_root.next = p_timer_chain_node_new;
        p_timer_chain_node_new->pre = &g_timer_chain_node_root;  

        // 发信号, 使timer主线程中断sleep
        //timer_signal_timer_add(1);
    }
    else
    {     
        while(nofind && (p_timer_chain_node_cur != NULL))   // 查找第一个节点:节点到期时间 >= 新节点到期时间
        {
            
            if(p_timer_chain_node_cur->timer_usr_data.tm_first < p_timer_chain_node_new->timer_usr_data.tm_first)
            {
                p_timer_chain_node_pre = p_timer_chain_node_cur;
                p_timer_chain_node_cur = p_timer_chain_node_cur->next;
            }
            else
            {
                nofind = 0;
                break;
            }     
        }

        // 找到节点的到期时间大于新增节点，将新节点插入到p_timer_chain_node_cur节点之前
        // 当插入的新节点在第一个节点之前的时候，发信号，中断timer线程sleep  
        if(nofind == 0)         // 找到一个节点，新节点插入到该节点之前
        {
            // 插入新节点到当前节点之前
            p_timer_chain_node_pre = p_timer_chain_node_cur->pre;   
            p_timer_chain_node_new->next = p_timer_chain_node_cur;
            p_timer_chain_node_cur->pre = p_timer_chain_node_new;
            p_timer_chain_node_pre->next = p_timer_chain_node_new;
            p_timer_chain_node_new->pre = p_timer_chain_node_pre;

            // 当前节点为第一个节点的时候，发信号, 使timer主线程中断sleep
            timer_signal_timer_add(1);
            
        }
        else                    // 没找到节点，当前节点已经到空，将新节点插入p_timer_chain_node_pre之后
        {
            p_timer_chain_node_new->next = NULL;
            p_timer_chain_node_pre->next = p_timer_chain_node_new;
            p_timer_chain_node_new->pre = p_timer_chain_node_pre;
            
        }
    }

    // 清除等待标志
    timer_flag_wait_clear();  
    
    g_timer_manager_data.node_num++;
    //g_timer_manager_data.node_num = g_timer_manager_data.node_num % MAX_TIMER_NODE_NUM;

#ifdef debug_printf_timer
//    logger(TLOG_NOTICE, "已经加入一个节点，当前节点数量=%d\n",g_timer_manager_data.node_num);
#endif
  
    return 0;
}

// 在timer链中删除第一个节点
int timer_chain_node_delete()
{
    s_timer_chain_node *p_timer_chain_node_first;
    s_timer_chain_node *p_timer_chain_node_second;

    if(g_timer_chain_node_root.next == NULL)
    {
//        logger(TLOG_NOTICE, "timer链表空，不能删除第一个节点\n");
#ifdef debug_printf_timer_queue
        vs_printf_timer_queue();
#endif
        return 1;
    }
    

    p_timer_chain_node_first = g_timer_chain_node_root.next;
#ifdef debug_printf_timer
logger(TLOG_NOTICE, "timer_chain_node_delete()即将删除第一个节点，节点号=%d\n", p_timer_chain_node_first->timer_usr_data.tm_id);
#endif
    p_timer_chain_node_second = p_timer_chain_node_first->next;
    if(p_timer_chain_node_second == NULL)
    {
#ifdef debug_printf_timer
 //       logger(TLOG_NOTICE, "timer链表只有一个节点, ");
#endif
        g_timer_chain_node_root.next = NULL;
    }
    else
    {
        g_timer_chain_node_root.next = p_timer_chain_node_second;
        p_timer_chain_node_second->pre = &g_timer_chain_node_root;
    }

    free(p_timer_chain_node_first);

    // 如果timer链空，设置等待标志
    if(g_timer_chain_node_root.next == NULL)
        timer_flag_wait_set();
    
    g_timer_manager_data.node_num--;
    
#ifdef debug_printf_timer_queue
            vs_printf_timer_queue();
#endif

    return 0;
}

// 获得等待队列的第一个节点，到期，则执行相应操作,处理完毕，从等待队列中删除此节点，返回0
//                           未到期，则返回需要还需要等待的秒数,返回值>0
int timer_chain_node_handler()
{
    int ret;
    int timer_id;                                   // 此次进行调用timer处理函数的timer_id
    time_t time_wait;                                                   // 此timer的等待秒数
    s_timer_chain_node *timer_chain_node_frist;
	s_timer_usr_data timer_usr_data;


    // timer时间到，但是，此时该timer已经被直接从队列中删除掉了。
    // 如果此时队列为空，则直接设置等待时间为1秒
    // 如果此时队列不空，则解析第一个节点。此时可能发生这种情况，即这个第一个节点比直接从队列中删除的节点的到期时间早，
    // 也就是，在此刻，新的节点的早已经到期，则直接处理。
    // 严格说来，加入比第一个节点到期时间早的节点的时候，应该停止sleep,来重新设置sleep的时间，但是这里简化了
    if(g_timer_chain_node_root.next == NULL)
    {
        time_wait = 1;
        return time_wait;
    }
    
    // 获取第一个节点的等待时间 = 第一个节点的到期时间 - 当前系统时间
    timer_get_frist_node_wt(&time_wait);
    
#ifdef debug_printf_timer
//    logger(TLOG_NOTICE, "第一个节点的等待时间=%d\n", time_wait);
#endif

    // 如果此节点未到期，则返回还需等待的秒数
    if(time_wait > 0)
    {
        return time_wait;
    }

    timer_chain_node_frist = g_timer_chain_node_root.next;

    // 如果本次timer为重复型timer,需要将此重复型timer加入到等待队列中
    if(timer_chain_node_frist->timer_usr_data.mode != 1)
    {
        
        // 永久重复型，设置mode = 0 ; 多次型,设置mode = mode -1;
        if(timer_chain_node_frist->timer_usr_data.mode == 0)
            timer_usr_data.mode = 0;
        else
            timer_usr_data.mode--;
        
        timer_usr_data.timer_handler = timer_chain_node_frist->timer_usr_data.timer_handler;
        timer_usr_data.timer_handler_data = timer_chain_node_frist->timer_usr_data.timer_handler_data;
        timer_usr_data.tm_first = timer_chain_node_frist->timer_usr_data.tm_first + timer_chain_node_frist->timer_usr_data.tm_intervel;
        timer_usr_data.tm_intervel = timer_chain_node_frist->timer_usr_data.tm_intervel;
        
        pthread_mutex_lock(&g_timer_manager_data.mutex_chain_opt);
        timer_chain_node_add(&timer_usr_data);
        pthread_mutex_unlock(&g_timer_manager_data.mutex_chain_opt);
    }
 
    // 执行该节点的到期执行函数, 执行函数返回后，删除该节点
//    pthread_mutex_lock(&g_timer_manager_data.mutex_chain_opt);            // 注意，如果这个进行互斥会因为timer执行函数中也调用此函数而造成死锁，但是居然能看视频，奇怪!
    timer_id = timer_chain_node_frist->timer_usr_data.tm_id;
#ifdef debug_printf_timer
    logger(TLOG_NOTICE, "执行timer到期处理函数，timer_id=%d\n",timer_chain_node_frist->timer_usr_data.tm_id);
#endif
    timer_chain_node_frist->timer_usr_data.timer_handler(timer_chain_node_frist->timer_usr_data.timer_handler_data);
    pthread_mutex_lock(&g_timer_manager_data.mutex_chain_opt);

    /************************************************************************
     *** 这里原来调用timer_chain_node_delete() ， 现在调用timer_chain_node_del_by_timerid()
     *** 因为，在main_rountine中的心跳函数中，增加新timer之前会删除旧timer, 因为考虑到这个时候timer可能还没有到期，
               但是如果这个时候该timer到期了，则执行完处理函数后，继续删除当前第一个节点会造成重复删除。
         故，目前改为删除指定timer_id号的节点。

    **************************************************************************/
    //ret = timer_chain_node_delete();                                  
    ret = timer_chain_node_del_by_timerid(timer_id);

    pthread_mutex_unlock(&g_timer_manager_data.mutex_chain_opt);
        
    return 0;
}


// 初始化timer链，建立根节点
int vs_timer_chain_init()
{
    g_timer_chain_node_root.timer_usr_data.tm_first = 0;
    g_timer_chain_node_root.timer_usr_data.tm_intervel = 0;
    g_timer_chain_node_root.timer_usr_data.mode  = 0;
    g_timer_chain_node_root.timer_usr_data.timer_handler = NULL;
    g_timer_chain_node_root.pre = NULL;
    g_timer_chain_node_root.next = NULL;

    pthread_mutex_init(&g_timer_manager_data.mutex_chain_opt,NULL);
    pthread_mutex_init(&g_timer_manager_data.mutex_wait,NULL);   
	pthread_cond_init(&g_timer_manager_data.cond_wait,NULL);
	g_timer_manager_data.node_num = 0;
	g_timer_manager_data.timer_id = 0;
	timer_flag_wait_set();
    
    return 0;
} 

/*
// 加入以当前时间为起点的1次性timer,此接口目前专门给心跳使用
int vs_timer_add(int second, int mode,int *timer_id ) 
{
    s_timer_usr_data timer_usr_data;
     
    timer_usr_data.mode = mode;
    timer_usr_data.timer_handler = rountin_sigroutine;
    timer_usr_data.timer_handler_data = NULL;
    timer_usr_data.tm_first = time(NULL) + second; 

    pthread_mutex_lock(&g_timer_manager_data.mutex_chain_opt);
    timer_chain_node_add(&timer_usr_data);
    pthread_mutex_unlock(&g_timer_manager_data.mutex_chain_opt);

    *timer_id = timer_usr_data.tm_id;

#ifdef debug_printf_timer
    logger(TLOG_NOTICE, "vs_timer_add()增加一个timer节点成功，节点号=%d\n", *timer_id);
#endif

#ifdef debug_printf_timer_queue
        vs_printf_timer_queue();                            // 打印timer队列节点号
#endif

    return 0;
}
*/

/****************************************************************************************************************
功    能:　加入当前时间起的second秒到期的timer

输入参数:  mode          : timer的重复次数，0: 永久型timer   1: 单次型timer　　n:重复n次型timer
           second        : 当前时间起的second秒数
           tm_intervel   : 重复型timer的间隔时间
           timer_handler : timer对应的处理函数
           handler_data  : timer对应的处理函数，此数据在timer中不做处理，传递给timer对应的处理函数
           
输出参数:  tm_id         : timer id和队列中的timer一一对应，并返回给调用者。调用者今后可以使用id号来删除还没到期的timer

返 回 值:
*****************************************************************************************************************/
int vs_timer_add2(int mode,time_t second, int tm_intervel, void *handler, void *handler_data,int *timer_id)
{

    s_timer_usr_data timer_usr_data;
     
    timer_usr_data.mode = mode;
    timer_usr_data.tm_first = time(NULL) + second;
    timer_usr_data.tm_intervel = tm_intervel;
    timer_usr_data.timer_handler = handler;
    timer_usr_data.timer_handler_data = handler_data;
    //timer_usr_data.timer_handler_data = NULL;

    pthread_mutex_lock(&g_timer_manager_data.mutex_chain_opt);
    timer_chain_node_add(&timer_usr_data);
    pthread_mutex_unlock(&g_timer_manager_data.mutex_chain_opt);
    
    *timer_id = timer_usr_data.tm_id;

#ifdef debug_printf_timer
    logger(TLOG_NOTICE, "vs_timer_add2()****增加一个timer节点成功，节点号=%d\n", *timer_id);
#endif

#ifdef debug_printf_timer_queue
    vs_printf_timer_queue();                            // 打印timer队列节点号
#endif

    return 0;
}

// 删除timer_id对应的timer
int vs_timer_del(int timer_id)
{
    int ret;

    pthread_mutex_lock(&g_timer_manager_data.mutex_chain_opt);
    ret = timer_chain_node_del_by_timerid(timer_id);
    pthread_mutex_unlock(&g_timer_manager_data.mutex_chain_opt);
    if(0 == ret)
    {
#ifdef debug_printf_timer
logger(TLOG_NOTICE, "vs_timer_del****主动删除一个timer节点失败，未找到匹配节点，节点号=%d\n ", timer_id);
#endif
      
#ifdef debug_printf_timer_queue
vs_printf_timer_queue();                            // 打印timer队列节点号
#endif
        return ret;        
    }

#ifdef debug_printf_timer
logger(TLOG_NOTICE, "vs_timer_del****主动删除一个timer节点成功，节点号=%d\n", timer_id);
#endif
    
#ifdef debug_printf_timer_queue
vs_printf_timer_queue();                            // 打印timer队列节点号
#endif

    return ret;
}
    
int thread_timer_main()
{
   
    int ret;
	time_t time_wait;     
    time_wait = 0;
    
    while(!g_quit_timer)
    {
        // 等待。当timer链表中没有节点的时候，设置等待标志，timer管理线程阻塞；当向链表中插入节点的时候，清除等待标志
        pthread_mutex_lock(&g_timer_manager_data.mutex_wait);
        while(g_timer_manager_data.flag_wait)
            pthread_cond_wait(&g_timer_manager_data.cond_wait,&g_timer_manager_data.mutex_wait);
        pthread_mutex_unlock(&g_timer_manager_data.mutex_wait);

        // 判断timer链表是否为空。前面的阻塞机制应该使得该情况不会发生。
        if(g_timer_chain_node_root.next == NULL)
        {
            logger(TLOG_ERROR, "不能设置timer,timer链表空，严重错误，timer链表重新初始化!\n");
            vs_timer_chain_init();
            continue;        
        }

        while(!time_wait)
            time_wait = timer_chain_node_handler();
            
        // 等待第一个节点到期
#ifdef debug_printf_timer
//        logger(TLOG_NOTICE, "timer线程等待%d秒钟\n", time_wait);
#endif

        ret = sleep(time_wait);
        time_wait = 0;
        
#ifdef debug_printf_timer
        if(0 == ret)
        {
 //           logger(TLOG_NOTICE, "第一个timer节点到期\n");
        }
        else
        {
            logger(TLOG_NOTICE, "第一个timer节点未到期，有节点插入到第一个节点前，接收到SIGALRM, sleep中断，sleep剩余时间=%d\n",ret);
        }
#endif        

        
#if 0
        struct sigaction sysact;
        // 设置timer
        sigemptyset(&sysact.sa_mask);
        sysact.sa_flags = SA_SIGINFO;
        sysact.sa_sigaction = timer_chain_node_frist->timer_usr_data->timer_handler;
        sigaction(SIGMYTIMER, &sysact, NULL);
        timer_id = SetTimer(time_wait*1000, 0);
#endif
        
    }
    
//    logger(TLOG_NOTICE, "线程thread_timer_main()已经退出\n");
    return 0;
}

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

