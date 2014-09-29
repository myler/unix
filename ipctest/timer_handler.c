#ifdef __cplusplus
#if __cplusplus
extern "C"
{
#endif
#endif /* __cplusplus */

#include "vs_timer.h"
#include "vs_thread.h"
#include "vs_save.h"
#include "config.h"
#include "logger.h"

extern int g_htv_enabled[2];
extern AllConfig g_config;

void timer_hour_start(CallBack_operation_timer handler)
{
    int second;
    time_t timep;

    time(&timep);
    timer_next_hour_get(timep, &second);

 //   second = 10;
    timer_add(second, handler);
    return;
}

//返回值说明:
//	0:2个频道均没有命中
//	1:频道0命中
//	2:频道1命中
//	3:频道0，1均命中
int plan_hour_check()
{
    int position;
    int ret = 0;
    time_t timep;
    struct tm *p;
    time(&timep);
    p=gmtime(&timep);

    position = (p->tm_wday)*24 + (p->tm_hour + 23) % 24;

    if (g_config.alert.week_alert_plan_1.var[position] == '1')
    {
        ret += 1;
    }
    if (g_config.alert.week_alert_plan_2.var[position] == '1')
    {
        ret += 2;
    }
    return ret;
}

int plan_cap_stop_channel_0(void *data)
{
    htv_disable(0, 1);
    return 0;
}

int plan_cap_stop_channel_1(void *data)
{
    htv_disable(1, 1);
    return 0;
}


int plan_cap_action(int channel)
{
//    int second;
//    time_t timep;
    if (channel == 1 || channel == 3) // channel 0 自动命中， 使能channel 0
    {
        if (1 == g_config.alert.plan_cap_enalbe_1.var)
            htv_enable(0, 1);
        else
        {
            htv_disable(0, 1);
        }
    }
    else
    {
        htv_disable(0, 1);
    }

    if (channel == 2 || channel == 3) // channel 1 自动命中， 使能channel 0
    {
        if (1 == g_config.alert.plan_cap_enalbe_2.var)
            htv_enable(1, 1);
        else
        {
            htv_disable(1, 1);
        }
    }
    else
    {
        htv_disable(1, 1);
    }

	return 0;
}

int alert_timer_handler(void *data)
{
    // 建立录像文件的目录: /ipc/ipc_data/20091208/1
    dir_constrcut();

    int ret = plan_hour_check();
    plan_cap_action(ret);

    timer_hour_start(alert_timer_handler);
    return 0;
}

void timer_init()
{
    timer_hour_start(alert_timer_handler);
}

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
