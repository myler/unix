#ifdef __cplusplus
#if __cplusplus
extern "C"
{
#endif
#endif /* __cplusplus */

#include <stdio.h>
#include <stdlib.h>

#include "cgic.h"
//#include "cgi_sem_utils.h"
#include "cgi_types.h"
#include "config.h"
#include "sem.h"
#include "vs_thread.h"
#include "vs_save.h"
#include "sm_routine.h"
#include "logger.h"

int login_check(char *name, char *pwd)
{
    int ret = 1;
    int i = 0;

    char *username = (char  *)(&(g_config.user.username_0.var));
    char *password = username + sizeof(D_string);
    for (i = 0; i < g_config.user.user_num.var; i++)
    {
        if ((0 ==  strcmp(name, username))&& (0 ==  strcmp(pwd, password)))
        {
            ret = 0;
        }
        username += sizeof(D_string)*2+sizeof(D_int)*2;
        password += sizeof(D_string)*2+sizeof(D_int)*2;
    }

    return ret;
}

int handler_cgi_login_action(char *p_shm)
{
    int ret;
    char name[_MAX_LEN_LOGIN_USERNAME];
    char pwd[_MAX_LEN_LOGIN_PASSWORD];
    s_cgi_login_action *cgi_login_action;

    // 得到用户名、密码
    cgi_login_action = (s_cgi_login_action *)(p_shm + sizeof(int)*3);
    memcpy(name, cgi_login_action->username, _MAX_LEN_LOGIN_USERNAME);
    memcpy(pwd, cgi_login_action->password, _MAX_LEN_LOGIN_PASSWORD);

    // 检查用户名，密码是否合法,并将结果填写到共享内存相应位置
    ret = user_info_check(name, pwd);
    *(int *)(p_shm) =  ret;

    // 登录非法，返回错误
    if (0 != ret)
    {
        logger(TLOG_NOTICE, "web cgi login failed. ret=%d", ret);
        return -1;
    }

    return 0;
}



int handler_cgi_rtv_action(char *p_shm)
{
    int ret;

    s_var_video *rtv_setting;

    rtv_setting = (s_var_video *)(p_shm + sizeof(int)*3);

    if (CGI_GET_DATA == *(int *)(p_shm+sizeof(int)*2))
    {
#if DEBUG
        logger(TLOG_NOTICE, "RTV_GET_DATA.\n");
#endif
        memset(rtv_setting, 0, sizeof(s_var_video));
        xxx2varxxx_video(rtv_setting);
//		memcpy(rtv_setting, &(g_config.video), sizeof(s_var_video));
        //	rtv_setting->rtv_num.var= g_config.rtv_setting.rtv_num.var;
        //	rtv_setting->solution_x_1.var= g_config.rtv_setting.solution_x_1.var;
        ret = 0;
    }
    else if (CGI_SET_DATA == *(int *)(p_shm +sizeof(int)*2))
    {
#if DEBUG
        logger(TLOG_NOTICE, "RTV_SET_DATA.\n");
#endif
//		memcpy(rtv_setting, &(g_config.rtv_setting), sizeof(s_rtv_setting));
		vm_para_set(rtv_setting);
		varxxx2xxx_video(rtv_setting);
		limit_video_para();
        vs_config_write();
        ret = 0;
    }

    return ret;
}

int handler_cgi_network_action(char *p_shm)
{
    int ret;
    s_var_network *network_setting;

    network_setting = (s_var_network *)(p_shm + sizeof(int)*3);

    if (CGI_GET_DATA == *(int *)(p_shm+sizeof(int)*2))
    {
#if DEBUG
        logger(TLOG_NOTICE, "NETWORK_GET_DATA.\n");
#endif
        memset(network_setting, 0, sizeof(s_var_network));
        xxx2varxxx_network(network_setting);
        ret = 0;
    }
    else if (CGI_SET_DATA == *(int *)(p_shm +sizeof(int)*2))
    {
#if DEBUG
        logger(TLOG_NOTICE, "NETWORK_SET_DATA.\n");
#endif

        varxxx2xxx_network(network_setting);
        vs_config_write();
        ret = 0;

		sys_quit();
    }

    return ret;
}

int handler_cgi_alert_action(char *p_shm)
{
    int ret;
    s_var_alert *alert_setting;

    alert_setting = (s_var_alert *)(p_shm + sizeof(int)*3);

    if (CGI_GET_DATA == *(int *)(p_shm+sizeof(int)*2))
    {
#if DEBUG
        logger(TLOG_NOTICE, "ALERT_GET_DATA.\n");
#endif
        memset(alert_setting, 0, sizeof(s_var_alert));
        xxx2varxxx_alert(alert_setting);
//        logger(TLOG_NOTICE, "ALERT_GET_DATA DONE\n");
        ret = 0;
    }
    else if (CGI_SET_DATA == *(int *)(p_shm +sizeof(int)*2))
    {
#if DEBUG
        logger(TLOG_NOTICE, "ALERT_SET_DATA.\n");
#endif

        varxxx2xxx_alert(alert_setting);

        vs_config_write();
        ret = 0;
    }

    return ret;
}

int handler_cgi_store_action(char *p_shm)
{
    int ret;
    s_var_store *store_setting;

    store_setting = (s_var_store *)(p_shm + sizeof(int)*3);

    if (CGI_GET_DATA == *(int *)(p_shm+sizeof(int)*2))
    {
#if DEBUG
        logger(TLOG_NOTICE, "STORE_GET_DATA.\n");
#endif
        long size_useable;
        long size_sum;
        int percent_useable;

        xx_space_get(&size_useable, &size_sum, &percent_useable);
        memset(store_setting, 0, sizeof(s_var_store));
        xxx2varxxx_store(store_setting);
//        logger(TLOG_NOTICE, "STORE_GET_DATA DONE\n");
        ret = 0;
    }
    else if (CGI_SET_DATA == *(int *)(p_shm +sizeof(int)*2))
    {
#if DEBUG
        logger(TLOG_NOTICE, "STORE_SET_DATA.\n");
#endif
        varxxx2xxx_store(store_setting);
		limit_store_para();
        vs_config_write();
        ret = 0;
    }

    return ret;
}

int handler_cgi_user_action(char *p_shm)
{
    int ret;
    s_var_user *user_setting;

    user_setting = (s_var_user *)(p_shm + sizeof(int)*3);

    if (CGI_GET_DATA == *(int *)(p_shm+sizeof(int)*2))
    {
#if DEBUG
        logger(TLOG_NOTICE, "USER_GET_DATA.\n");
#endif
        memset(user_setting, 0, sizeof(s_var_user));
        xxx2varxxx_user(user_setting);
        ret = 0;
    }
    else if (CGI_SET_DATA == *(int *)(p_shm +sizeof(int)*2))
    {
#if DEBUG
        logger(TLOG_NOTICE, "USER_SET_DATA.\n");
#endif
        varxxx2xxx_user(user_setting);
        vs_config_write();
        ret = 0;
    }

    return ret;
}

int handler_cgi_sys_action(char *p_shm)
{
    int ret;
    s_var_sys *sys_setting;

    sys_setting = (s_var_sys *)(p_shm + sizeof(int)*3);

    if (CGI_GET_DATA == *(int *)(p_shm+sizeof(int)*2))
    {
#if DEBUG
        logger(TLOG_NOTICE, "SYS_GET_DATA.\n");
#endif
        memset(sys_setting, 0, sizeof(s_var_sys));
        xxx2varxxx_sys(sys_setting);
        ret = 0;
    }
    else if (CGI_SET_DATA == *(int *)(p_shm +sizeof(int)*2))
    {
#if DEBUG
        logger(TLOG_NOTICE, "SYS_SET_DATA.\n");
#endif
		system("cp -f /ipc/thirdparty/ipc.conf /etc/");
		sys_quit();
        ret = 0;
    }

    return ret;
}

s_map_CGI_flag2Handler  map_CGI_flag2Handler[]=
{
    {ID_CGI_LOGIN_ACTION,		 	handler_cgi_login_action},
    {ID_CGI_RTV_SET_ACTION,			handler_cgi_rtv_action},
    {ID_CGI_NETWORK_SET_ACTION, 	handler_cgi_network_action},
    {ID_CGI_ALERT_SET_ACTION, 		handler_cgi_alert_action},
    {ID_CGI_STORE_SET_ACTION, 		handler_cgi_store_action},
    {ID_CGI_USER_SET_ACTION,		handler_cgi_user_action},
    {ID_CGI_SYS_SET_ACTION,		handler_cgi_sys_action}
};

/* 查handler对应表，返回匹配数组单元号  */
int cgi_getHandlerMatch(int id_cgi_handler)
{
    int i;
//    logger(TLOG_NOTICE, "id_cgi_handler=%d\n", id_cgi_handler);
    for (i=0; map_CGI_flag2Handler[i].cgi_handler!= '\0'; i++)
        if (id_cgi_handler == map_CGI_flag2Handler[i].id_cgi_handler)
        {
            return i;
        }
    return -1;
}

int thread_cgi_main()
{
//	logger(TLOG_NOTICE, "thread %s id %d\n", __FUNCTION__, getpid());
    key_t key;
    key_t key_cgi;                // 为外部CGI程序对共享内存操作信号量
    int shm_id,sem_id;
    int sem_id_cgi;                 // 外部CGI程序对共享内存操作信号量
    struct semid_ds buf;

    int id_cgi_handler;
    int id_cgi_data_DS;

    char *p_shm;
    // 创建并关联共享内存

    key = ftok("./vs_shm",0);
    key_cgi = ftok("./vs_shm_cgi",0);
    //shm_id = shmget(key,SEGSIZE,IPC_CREAT |0604);
    shm_id = shmget(key,SEGSIZE,IPC_CREAT |0777);
    if (-1 == shm_id)
    {
        logger(TLOG_ERROR, " create shared memory error\n");
        return -1;
    }
    p_shm = (char *)shmat(shm_id,0,0);
    if (-1 == (int)p_shm)
    {
        logger(TLOG_ERROR, " attach shared memory error\n");
        return -1;
    }

    // 创建互斥锁
    sem_id = sem_creat(key);                    // vs主程序对共享内存操作信号量
    sem_id_cgi = sem_creat(key_cgi);            // 外部CGI程序对共享内存操作信号量

    while (!mapThreadID2Handler[THREAD_CGI].thread_quit_flag)
    {
        p(sem_id);      // vs等待共享内存
//        logger(TLOG_NOTICE, "===p=== \n");

        id_cgi_data_DS = *(int*)(p_shm + sizeof(int));
        id_cgi_handler = cgi_getHandlerMatch(id_cgi_data_DS);
        if (-1 == id_cgi_handler)
        {
            logger(TLOG_NOTICE, "===没有相应的CGI处理程序\n");
            continue;
        }
        else
        {
            map_CGI_flag2Handler[id_cgi_handler].cgi_handler(p_shm);
        }

//        logger(TLOG_NOTICE, "===v===\n");
        v(sem_id_cgi);    // 外部程序操作共享内存使能

    }

    shmdt(p_shm);
    shmctl(shm_id,IPC_RMID,&buf);
    sem_del(sem_id);
    sem_del(sem_id_cgi);

    return 0;
    //gcc -o shm shm.c -g
}



#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


