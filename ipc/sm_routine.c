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

#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>


#include "sm_routine.h"
#include "vs_package.h"
#include "config.h"
#include "logger.h"
//#include "vs_config_var_auto.h"
#include "vs_xml.h"
#include "protocol.h"
#include "vs_config_xxx2varxxx_auto.h"
#include "vs_socket.h"
#include "vs_thread.h"
#include "sem.h"
#include "sm_fileOption.h"

// int g_login_suc = 0;            // login成功置1
// time_t g_login_time;
extern s_syn_ctrl syn_ctrl_sys;
extern pthread_t threadID[THREAD_NUM_MAX];
extern AllConfig g_config;
extern  int log_file_select;      // 0: NETCROSSER_LOGFILE_1文件 1: NETCROSSER_LOGFILE_2文件
extern int g_rtv_sock[MAX_CONNECT_TO_SERVER][2];

/************************************************************************
* 函数名: rountin_common_flag
* 作  者: pgh, sx
* 描  述: 1.上面的rountin_common()函数,是发送一个带有后缀的消息. 如果需要发送一个错误的
*         返回结果,或者无后缀的消息,则不方便.所以这个函数就是不带后缀的消息
*         2.(仅向接入服务发送)
* 输入参数: int cmd_head_ID, 消息指令头编号
*           int flag, 对于res型的消息,可能带有一个flag标记, 0 成功 >0, 错误编号
* 输出参数: 无
* 返回值: 目前==0
************************************************************************/
int rountin_common_flag(int cmd_head_ID, int success_flag, int link_type, int ret_socketid)
{
    int headtype;

    headtype = vs_get_headtype(cmd_head_ID);
    if ( headtype == HEAD_REQ_4 )
    {
        s_cmd_req_head cmd_req_head;
        package_cmd_req_construct(&cmd_req_head, cmd_head_ID, 0, 0);
        package_send( (char *)&cmd_req_head, sizeof(s_cmd_req_head), SENDTYPE_TCP, link_type, ret_socketid);
    }
    else
    {
        s_cmd_res_head cmd_res_head;
        package_cmd_res_construct(&cmd_res_head, cmd_head_ID, 0, 0);
        cmd_res_head.flag = success_flag;
        package_send( (char *)&cmd_res_head, sizeof(s_cmd_res_head), SENDTYPE_TCP, link_type, ret_socketid);

    }
    return 0;
};


/************************************************************************
* 函数名: rountin_common_res_data
* 作  者: pgh, sx
* 描  述: 1. 这个仅用于回馈，有后缀，后缀可能是自编XML文件，可能是非XML字符串
*         2. (仅向接入服务发送)
* 输入参数: int cmd_head_ID, 消息指令头编号
*           data, 后缀数据
*           data_len, 后缀长度
*           int flag, res的标志位
* 输出参数: 无
* 返回值: 目前==0
************************************************************************/
int rountin_common_res_data(int cmd_head_ID, char *data, int data_len, int flag, int link_type, int ret_socketid)
{
    char *package;
    int len_package;


    if (data == NULL)
    {
        len_package = sizeof(s_cmd_res_head);
    }
    else
    {
        len_package = sizeof(s_cmd_res_head) + data_len;
    }

    //package = malloc(len_package + 24);
    package = malloc(len_package);
    if (package == NULL)
    {
        return 0;
    }
    package_cmd_res_construct( (s_cmd_res_head *)package, cmd_head_ID, data_len, 0);
    ((s_cmd_res_head *)package)->flag = flag;

    // 然后追加
    if (data_len > 0 && data != NULL)
    {
        memcpy(package + sizeof(s_cmd_res_head), data, data_len);
    }

    package_send( package, len_package, SENDTYPE_TCP, link_type, ret_socketid);

    free(package);
    return 0;
}


// IPC主动发送req
int rountin_common_req_data(int cmd_head_ID, char *data, int data_len, int link_type, int ret_socketid)
{
    char *package;
    int len_package;


    if (data == NULL)
    {
        len_package = sizeof(s_cmd_req_head);
    }
    else
    {
        len_package = sizeof(s_cmd_req_head) + data_len;
    }

    //package = malloc(len_package + 24);
    package = (char *)malloc(len_package);
    if (package == NULL)
    {
        return 0;
    }
    package_cmd_req_construct( (s_cmd_req_head *)package, cmd_head_ID, data_len, 0);

    // 然后追加
    if (data_len > 0 && data != NULL)
    {
        memcpy(package + sizeof(s_cmd_req_head), data, data_len);
    }

    package_send( package, len_package, SENDTYPE_TCP, link_type, ret_socketid);

    free(package);
    return 0;
}

int xml_get(char *buf, s_xml *xml)
{
    xml->context = buf + sizeof(int) * 5;
    xml->len = *(int *)(buf + sizeof(int)*2);

    return 0;
}

int srand_id_get(char *buf, int *srand_id)
{
    *srand_id = *(int *)(buf + sizeof(int)*4);
    return 0;
}


// 操作密码验证, 成功返0
int xml_pw_validate(char *xml, int xml_len)
{
    char password[_LEN_NORMAL];

    // 1. 解析xml的Password
    findxml_string(xml, xml_len, "Password", password);

    // 2. 验证
    //memcmp(g_config.para_login.password.var, password, _LEN_NORMAL);

    return 0;
}

// 验证用户名和密码，成功返0, 1, 2,3 ,分别对应4组用户名和密码
int user_info_check(char *username, char *password)
{
   if ((0 == strcmp(g_config.user.username_0.var,  username))
            &&(0 == strcmp(g_config.user.password_0.var,  password)))
        return 0;

    if ((0 == strcmp(g_config.user.username_1.var,  username))
            &&(0 == strcmp(g_config.user.password_1.var,  password)))
        return 1;

    if ((0 == strcmp(g_config.user.username_2.var,  username))
            &&(0 == strcmp(g_config.user.password_2.var,  password)))
        return 2;

    if ((0 == strcmp(g_config.user.username_3.var,  username))
            &&(0 == strcmp(g_config.user.password_3.var,  password)))
        return 3;

    return -1;
}

// 仅验证用户名，成功返0, 1, 2,3 ,分别对应4组用户名
int user_match(char *username)
{
    /*
        if(0 == memcmp(g_config.para_login.username.var,  username, _LEN_NORMAL))
            return 0;

        if(0 == memcmp(g_config.para_login_1.username.var,  username, _LEN_NORMAL))
            return 1;

        if(0 == memcmp(g_config.para_login_2.username.var,  username, _LEN_NORMAL))
            return 2;

        if(0 == memcmp(g_config.para_login_3.username.var,  username, _LEN_NORMAL))
            return 3;
    */
    return -1;
}



/* 密码强度检查
   只能是: A ~ Z a ~ b 0 ~ 9*/
int passwd_check(char *passwd)
{
    char *loc;
    int is_upper = 0, is_lower = 0, is_digital = 0;

    loc = passwd;
    while (0 != *loc)
    {
        if ((*loc > 'A')&&(*loc < 'Z'))
        {
            is_upper = 1;
            continue;
        }
        if ((*loc > 'a')&&(*loc < 'z'))
        {
            is_lower = 1;
            continue;
        }
        if ((*loc > '0')&&(*loc < '9'))
        {
            is_digital = 1;
            continue;
        }

        return -1;
    }
    if ((1 == is_upper)&&(1 == is_lower)&&(1 == is_digital))
        return 0;

    return -1;
}

/* 更新系统的日期，格式如下: 2008-10-12 13:14:34*/
/*
格式是date后跟月日时分年
注意年是4位年，例如：2007年10月26日 10：00：00
date 101213142007.34
*/
int sys_datetime_set(const char *dateformat)
{
    char buf[128];
	int c1, c2, c3, c4, c5, c6;
	
    if ( NULL == dateformat )
        return -1;
	
    memset(buf, 0, 128);
    if (sscanf(dateformat, "%d-%d-%d %d:%d:%d", &c1, &c2, &c3, &c4, &c5, &c6) != 6)
        return -1;

    sprintf(buf, "/bin/date %02d%02d%02d%02d%04d.%02d", c2, c3, c4, c5,c1,c6);
    system(buf);
    system("/sbin/hwclock -w");
	dir_constrcut();
    return 0;
}

// pgh 20100124 add 移动侦测报警后，清空移动侦测区域
void md_reset()
{
    g_config.md_report.md_area_0_0.var = 0;
    g_config.md_report.md_area_0_1.var = 0;
    g_config.md_report.md_area_0_2.var = 0;
    g_config.md_report.md_area_0_3.var = 0;
    g_config.md_report.md_area_1_0.var = 0;
    g_config.md_report.md_area_1_1.var = 0;
    g_config.md_report.md_area_1_2.var = 0;
    g_config.md_report.md_area_1_3.var = 0;

    return;
}

// pgh 20100124 add
void alarm_error_set(int alarm_error_id, char *alarm_error_name)
{
    g_config.alarm_error.alarm_error_id.var= alarm_error_id;
    memset(g_config.alarm_error.alarm_error_name.var, 0, _LEN_NORMAL);
    strcpy(g_config.alarm_error.alarm_error_name.var, alarm_error_name);
    
    return;
}

int rtv_user_start(int channel, int socket_id)
{
    int i;

    for (i=0; i<MAX_CONNECT_TO_SERVER; i++)
        if (0 == g_rtv_sock[i][1])
        {
            struct timeval timeout={3,0};//3s
            int ret=setsockopt(socket_id,SOL_SOCKET,SO_SNDTIMEO,&timeout,sizeof(timeout));
            g_rtv_sock[i][0] = socket_id;
            g_rtv_sock[i][1] = channel;		
            break;
        }

    return 0;
}

int rtv_user_end(int socket_id)
{
    int i;

    for (i=0; i<MAX_CONNECT_TO_SERVER; i++)
        if (socket_id == g_rtv_sock[i][0])
        {
            g_rtv_sock[i][1] = 0;
			g_rtv_sock[i][0] = 0;
            break;
        }

    return 0;
}

//拔USB,停止抓取和发送线程
int rtv_usb_remove(int channel)
{
    if (channel == 1)
    {
        if (0 == mapThreadID2Handler[THREAD_RTV_SEND_0].thread_quit_flag)
        {
            mapThreadID2Handler[THREAD_RTV_SEND_0].thread_quit_flag = 1;
            pthread_join(threadID[THREAD_RTV_SEND_0], NULL);
//            logger(TLOG_NOTICE, "usb send cancel, channel:%d\n", channel);
        }
        if (0 == mapThreadID2Handler[THREAD_RTV_0].thread_quit_flag)
        {
            mapThreadID2Handler[THREAD_RTV_0].thread_quit_flag = 1;
            pthread_join(threadID[THREAD_RTV_0], NULL);
//            logger(TLOG_NOTICE, "usb remove, channel:%d\n", channel);
        }
    }
    else if (channel == 2)
    {
        if (0 == mapThreadID2Handler[THREAD_RTV_SEND_1].thread_quit_flag)
        {
            mapThreadID2Handler[THREAD_RTV_SEND_1].thread_quit_flag = 1;
            pthread_join(threadID[THREAD_RTV_SEND_1], NULL);
//            logger(TLOG_NOTICE, "usb send cancel, channel:%d\n", channel);
        }
        if (0 == mapThreadID2Handler[THREAD_RTV_1].thread_quit_flag)
        {
            mapThreadID2Handler[THREAD_RTV_1].thread_quit_flag = 1;
            pthread_join(threadID[THREAD_RTV_1], NULL);
//            logger(TLOG_NOTICE, "usb remove, channel:%d\n", channel);
        }
    }
    return 0;
}

void sys_quit()
{
//    int i = 0;
    thread_syn_flag_set(&syn_ctrl_sys.mutex_r, &syn_ctrl_sys.cond_r, &syn_ctrl_sys.flag_r);
	return;
}


// 亮度、对比度取值限制
int limit_video_para()
{
    if(g_config.video.bright_1.var > 255)
        g_config.video.bright_1.var = 255;
    if(g_config.video.bright_1.var < 0)
        g_config.video.bright_1.var = 0;
    if(g_config.video.bright_2.var > 255)
        g_config.video.bright_2.var = 255;
    if(g_config.video.bright_2.var < 0)
        g_config.video.bright_2.var = 0;

    if(g_config.video.contrast_1.var > 255)
        g_config.video.contrast_1.var = 255;
    if(g_config.video.contrast_1.var < 0)
        g_config.video.contrast_1.var = 0;
    if(g_config.video.contrast_2.var > 255)
        g_config.video.contrast_2.var = 255;
    if(g_config.video.contrast_2.var < 0)
        g_config.video.contrast_2.var = 0;
    return 0;     
}

int limit_store_para(){
	if(g_config.store.sd_status.var == 0){
		if(g_config.store.percent_del.var < 30)
			g_config.store.percent_del.var = 30;
		if(g_config.store.percent_alarm.var < 35)
			g_config.store.percent_alarm.var = 35;
	}

	return 0;
}

// 获取ipc进程信息
int process_info_get(char * buf)
{
  FILE   *stream;

  char * command = "(sleep 1; echo q) | top | grep ipc | sort | awk 'BEGIN{CPU=0, MEM=0, MEMP=0}{print \"PID=\"$1,\"MEM=\"$4,\"%MEM=\"$7,\"%CPU=\"$6; CPU += $6; MEM = $4; MEMP=$7}END{print \"TOTAL:MEM=\"MEM, \"%MEM=\"MEMP,\"%CPU=\"CPU}'";
  stream = popen( command, "r" );
  if (stream == NULL){
        return -1;
  }

  fread(buf, sizeof(char), 1024, stream);
  pclose(stream);

  return strlen(buf);
}

/*********************** IPC  被动 RT begin ********************************/
void rt_login_get_req(char *buf)
{
    int ret;
    s_xml xml;
    char outbuf[10240];
    int srand_id;
    s_var_login var_login;
    s_var_login_get_req   var_login_get_req;

    ROUNTINE_COMM_1(CMD_ID_LOGIN_GET_RES, var_login_get_req, s_var_login_get_req, s_var_login_get_req_index, buf, outbuf, xml, srand_id, ret);
    xxx2varxxx_login(&var_login);
    struct2xml((char *)(&var_login), outbuf, s_var_login_index, all_xml_find_desc);
    rountin_common_res_data(CMD_ID_LOGIN_GET_RES, outbuf, strlen(outbuf), MSG_RES_FLAG_SUC, 0, *(int *)buf);

    return;
}

void rt_login_set_req(char *buf)
{
    int ret;
    s_xml xml;
    char outbuf[10240];
    int srand_id;
    s_var_login_set_req   var_login_set_req;

    ROUNTINE_COMM_1(CMD_ID_LOGIN_SET_RES, var_login_set_req, s_var_login_set_req, s_var_login_set_req_index, buf, outbuf, xml, srand_id, ret);
    varxxx2xxx_login(&var_login_set_req.var_login);
    vs_config_write();
    rountin_common_flag(CMD_ID_LOGIN_SET_RES, MSG_RES_FLAG_SUC, 0, *(int *)buf);

    return;
}

void rt_user_get_req(char *buf)
{
    int ret;
    s_xml xml;
    char outbuf[10240];
    int srand_id;
    s_var_user var_user;
    s_var_user_get_req   var_user_get_req;

    ROUNTINE_COMM_1(CMD_ID_USER_GET_RES, var_user_get_req, s_var_user_get_req, s_var_user_get_req_index, buf, outbuf, xml, srand_id, ret);
    if (0 != ret)
    {
        rountin_common_flag(CMD_ID_USER_GET_RES, MSG_RES_FLAG_ERR_LOGIN_PWD, srand_id, *(int *)buf);
        return;
    }

    xxx2varxxx_user(&var_user);
    struct2xml((char *)(&var_user), outbuf, s_var_user_index, all_xml_find_desc);
    rountin_common_res_data(CMD_ID_USER_GET_RES, outbuf, strlen(outbuf), MSG_RES_FLAG_SUC, 0, *(int *)buf);

    return;
}

void rt_user_set_req(char *buf)
{
    int ret;
    s_xml xml;
    char outbuf[10240];
    int srand_id;
    s_var_user_set_req   var_user_set_req;

    ROUNTINE_COMM_1(CMD_ID_USER_SET_RES, var_user_set_req, s_var_user_set_req, s_var_user_set_req_index, buf, outbuf, xml, srand_id, ret);
    if (0 != ret)
    {
        rountin_common_flag(CMD_ID_USER_SET_RES, MSG_RES_FLAG_ERR_LOGIN_PWD, srand_id, *(int *)buf);
        return;
    }

    if((0 == strlen(var_user_set_req.var_user.username_0)) || 
       (0 == strlen(var_user_set_req.var_user.password_0)))
    {
        rountin_common_flag(CMD_ID_USER_SET_RES, MSG_RES_FLAG_ERR_ADMIN_NULL, srand_id, *(int *)buf);
        return;
    }

    varxxx2xxx_user(&var_user_set_req.var_user);
    vs_config_write();
    rountin_common_flag(CMD_ID_USER_SET_RES, MSG_RES_FLAG_SUC, 0, *(int *)buf);

    return;
}

void rt_video_get_req(char *buf)
{
    int ret;
    s_xml xml;
    char outbuf[10240];
    int srand_id;
    s_var_video var_video;
    s_var_video_get_req   var_video_get_req;

    ROUNTINE_COMM_1(CMD_ID_VIDEO_GET_RES, var_video_get_req, s_var_video_get_req, s_var_video_get_req_index, buf, outbuf, xml, srand_id, ret);
    if (0 != ret)
    {
        rountin_common_flag(CMD_ID_USER_GET_RES, MSG_RES_FLAG_ERR_LOGIN_PWD, srand_id, *(int *)buf);
        return;
    }
    xxx2varxxx_video(&var_video);
    struct2xml((char *)(&var_video), outbuf, s_var_video_index, all_xml_find_desc);
    rountin_common_res_data(CMD_ID_VIDEO_GET_RES, outbuf, strlen(outbuf), MSG_RES_FLAG_SUC, 0, *(int *)buf);

    return;
}

void rt_video_set_req(char *buf)
{
    int ret;
    s_xml xml;
    char outbuf[10240];
    int srand_id;
    s_var_video_set_req   var_video_set_req;

    ROUNTINE_COMM_1(CMD_ID_VIDEO_SET_RES, var_video_set_req, s_var_video_set_req, s_var_video_set_req_index, buf, outbuf, xml, srand_id, ret);
    if (0 != ret)
    {
        rountin_common_flag(CMD_ID_USER_GET_RES, MSG_RES_FLAG_ERR_LOGIN_PWD, srand_id, *(int *)buf);
        return;
    }

	vm_para_set(&var_video_set_req.var_video);
	varxxx2xxx_video(&var_video_set_req.var_video);
	limit_video_para();
    vs_config_write();
	
    rountin_common_flag(CMD_ID_VIDEO_SET_RES, MSG_RES_FLAG_SUC, 0, *(int *)buf);

    return;
}

void rt_network_get_req(char *buf)
{
    int ret;
    s_xml xml;
    char outbuf[10240];
    int srand_id;
    s_var_network var_network;
    s_var_network_get_req   var_network_get_req;

    ROUNTINE_COMM_1(CMD_ID_NETWORK_GET_RES, var_network_get_req, s_var_network_get_req, s_var_network_get_req_index, buf, outbuf, xml, srand_id, ret);
    if (0 != ret)
    {
        rountin_common_flag(CMD_ID_USER_GET_RES, MSG_RES_FLAG_ERR_LOGIN_PWD, srand_id, *(int *)buf);
        return;
    }
    xxx2varxxx_network(&var_network);
    struct2xml((char *)(&var_network), outbuf, s_var_network_index, all_xml_find_desc);
    rountin_common_res_data(CMD_ID_NETWORK_GET_RES, outbuf, strlen(outbuf), MSG_RES_FLAG_SUC, 0, *(int *)buf);

    return;
}

void rt_network_set_req(char *buf)
{
    int ret;
    s_xml xml;
    char outbuf[10240];
    int srand_id;
    s_var_network_set_req   var_network_set_req;

    ROUNTINE_COMM_1(CMD_ID_NETWORK_SET_RES, var_network_set_req, s_var_network_set_req, s_var_network_set_req_index, buf, outbuf, xml, srand_id, ret);
    if (0 != ret)
    {
        rountin_common_flag(CMD_ID_NETWORK_SET_RES, MSG_RES_FLAG_ERR_LOGIN_PWD, srand_id, *(int *)buf);
        return;
    }
    varxxx2xxx_network(&var_network_set_req.var_network);
    vs_config_write();
    rountin_common_flag(CMD_ID_NETWORK_SET_RES, MSG_RES_FLAG_SUC, 0, *(int *)buf);

	sys_quit();
	
    return;
}

void rt_alert_get_req(char *buf)
{
    int ret;
    s_xml xml;
    char outbuf[10240];
    int srand_id;
    s_var_alert var_alert;
    s_var_alert_get_req   var_alert_get_req;

    ROUNTINE_COMM_1(CMD_ID_ALERT_GET_RES, var_alert_get_req, s_var_alert_get_req, s_var_alert_get_req_index, buf, outbuf, xml, srand_id, ret);
    if (0 != ret)
    {
        rountin_common_flag(CMD_ID_USER_GET_RES, MSG_RES_FLAG_ERR_LOGIN_PWD, srand_id, *(int *)buf);
        return;
    }
    xxx2varxxx_alert(&var_alert);
    struct2xml((char *)(&var_alert), outbuf, s_var_alert_index, all_xml_find_desc);
    rountin_common_res_data(CMD_ID_ALERT_GET_RES, outbuf, strlen(outbuf), MSG_RES_FLAG_SUC, 0, *(int *)buf);

    return;
}

void rt_alert_set_req(char *buf)
{
    int ret;
    s_xml xml;
    char outbuf[10240];
    int srand_id;
    s_var_alert_set_req   var_alert_set_req;

    ROUNTINE_COMM_1(CMD_ID_ALERT_SET_RES, var_alert_set_req, s_var_alert_set_req, s_var_alert_set_req_index, buf, outbuf, xml, srand_id, ret);
    if (0 != ret)
    {
        rountin_common_flag(CMD_ID_USER_GET_RES, MSG_RES_FLAG_ERR_LOGIN_PWD, srand_id, *(int *)buf);
        return;
    }
    varxxx2xxx_alert(&var_alert_set_req.var_alert);
    vs_config_write();
    rountin_common_flag(CMD_ID_ALERT_SET_RES, MSG_RES_FLAG_SUC, 0, *(int *)buf);

    return;
}

void rt_store_get_req(char *buf)
{
    int ret;
    s_xml xml;
    char outbuf[10240];
    int srand_id;
    s_var_store var_store;
    s_var_store_get_req   var_store_get_req;

    ROUNTINE_COMM_1(CMD_ID_STORE_GET_RES, var_store_get_req, s_var_store_get_req, s_var_store_get_req_index, buf, outbuf, xml, srand_id, ret);
    if (0 != ret)
    {
        rountin_common_flag(CMD_ID_USER_GET_RES, MSG_RES_FLAG_ERR_LOGIN_PWD, srand_id, *(int *)buf);
        return;
    }
    xxx2varxxx_store(&var_store);
    struct2xml((char *)(&var_store), outbuf, s_var_store_index, all_xml_find_desc);
    rountin_common_res_data(CMD_ID_STORE_GET_RES, outbuf, strlen(outbuf), MSG_RES_FLAG_SUC, 0, *(int *)buf);

    return;
}

void rt_store_set_req(char *buf)
{
    int ret;
    s_xml xml;
    char outbuf[10240];
    int srand_id;
    s_var_store_set_req   var_store_set_req;

    ROUNTINE_COMM_1(CMD_ID_STORE_SET_RES, var_store_set_req, s_var_store_set_req, s_var_store_set_req_index, buf, outbuf, xml, srand_id, ret);
    if (0 != ret)
    {
        rountin_common_flag(CMD_ID_USER_GET_RES, MSG_RES_FLAG_ERR_LOGIN_PWD, srand_id, *(int *)buf);
        return;
    }
    varxxx2xxx_store(&var_store_set_req.var_store);
	limit_store_para();
    vs_config_write();
    rountin_common_flag(CMD_ID_STORE_SET_RES, MSG_RES_FLAG_SUC, 0, *(int *)buf);

    return;
}

void rt_sys_get_req(char *buf)
{
    int ret;
    s_xml xml;
    char outbuf[10240];
    int srand_id;
    s_var_sys var_sys;
    s_var_sys_get_req   var_sys_get_req;

    ROUNTINE_COMM_1(CMD_ID_SYS_GET_RES, var_sys_get_req, s_var_sys_get_req, s_var_sys_get_req_index, buf, outbuf, xml, srand_id, ret);
    if (0 != ret)
    {
        rountin_common_flag(CMD_ID_USER_GET_RES, MSG_RES_FLAG_ERR_LOGIN_PWD, srand_id, *(int *)buf);
        return;
    }
    xxx2varxxx_sys(&var_sys);
    struct2xml((char *)(&var_sys), outbuf, s_var_sys_index, all_xml_find_desc);
    rountin_common_res_data(CMD_ID_SYS_GET_RES, outbuf, strlen(outbuf), MSG_RES_FLAG_SUC, 0, *(int *)buf);

    return;
}

void rt_sys_set_req(char *buf)
{
    int ret;
    s_xml xml;
    char outbuf[10240];
    int srand_id;
    s_var_sys_set_req   var_sys_set_req;

    ROUNTINE_COMM_1(CMD_ID_SYS_SET_RES, var_sys_set_req, s_var_sys_set_req, s_var_sys_set_req_index, buf, outbuf, xml, srand_id, ret);
    if (0 != ret)
    {
        rountin_common_flag(CMD_ID_USER_GET_RES, MSG_RES_FLAG_ERR_LOGIN_PWD, srand_id, *(int *)buf);
        return;
    }
    varxxx2xxx_sys(&var_sys_set_req.var_sys);
    vs_config_write();
    rountin_common_flag(CMD_ID_SYS_SET_RES, MSG_RES_FLAG_SUC, 0, *(int *)buf);

    return;
}

void rt_rtv_start_get_req(char *buf)
{
    int ret;
    s_xml xml;
    char outbuf[10240];
    int srand_id;
    s_var_rtv_start var_rtv_start;
    s_var_rtv_start_get_req   var_rtv_start_get_req;

    ROUNTINE_COMM_1(CMD_ID_RTV_START_GET_RES, var_rtv_start_get_req, s_var_rtv_start_get_req, s_var_rtv_start_get_req_index, buf, outbuf, xml, srand_id, ret);
    xxx2varxxx_rtv_start(&var_rtv_start);
    struct2xml((char *)(&var_rtv_start), outbuf, s_var_rtv_start_index, all_xml_find_desc);
    rountin_common_res_data(CMD_ID_RTV_START_GET_RES, outbuf, strlen(outbuf), MSG_RES_FLAG_SUC, 0, *(int *)buf);

    return;
}

void rt_rtv_start_set_req(char *buf)
{
    int ret;
    s_xml xml;
    char outbuf[10240];
    int srand_id;
    s_var_rtv_start_set_req   var_rtv_start_set_req;

    ROUNTINE_COMM_1(CMD_ID_RTV_START_SET_RES, var_rtv_start_set_req, s_var_rtv_start_set_req, s_var_rtv_start_set_req_index, buf, outbuf, xml, srand_id, ret);

    varxxx2xxx_rtv_start(&var_rtv_start_set_req.var_rtv_start);
    vs_config_write();
    rountin_common_flag(CMD_ID_RTV_START_SET_RES, MSG_RES_FLAG_SUC, 0, *(int *)buf);

    rtv_user_start(var_rtv_start_set_req.var_rtv_start.channel, *(int *)buf);

    return;
}

void rt_htv_start_get_req(char *buf)
{
    int ret;
    s_xml xml;
    char outbuf[10240];
    int srand_id;
    s_var_htv_start var_htv_start;
    s_var_htv_start_get_req   var_htv_start_get_req;

    ROUNTINE_COMM_1(CMD_ID_HTV_START_GET_RES, var_htv_start_get_req, s_var_htv_start_get_req, s_var_htv_start_get_req_index, buf, outbuf, xml, srand_id, ret);
    xxx2varxxx_htv_start(&var_htv_start);
    struct2xml((char *)(&var_htv_start), outbuf, s_var_htv_start_index, all_xml_find_desc);
    rountin_common_res_data(CMD_ID_HTV_START_GET_RES, outbuf, strlen(outbuf), MSG_RES_FLAG_SUC, 0, *(int *)buf);

    return;
}

void rt_htv_start_set_req(char *buf)
{
    int ret;
    s_xml xml;
    char outbuf[10240];
    int srand_id;
    s_var_htv_start_set_req   var_htv_start_set_req;

    ROUNTINE_COMM_1(CMD_ID_HTV_START_SET_RES, var_htv_start_set_req, s_var_htv_start_set_req, s_var_htv_start_set_req_index, buf, outbuf, xml, srand_id, ret);

    varxxx2xxx_htv_start(&var_htv_start_set_req.var_htv_start);
    vs_config_write();
    rountin_common_flag(CMD_ID_HTV_START_SET_RES, MSG_RES_FLAG_SUC, 0, *(int *)buf);

    htv_enable(var_htv_start_set_req.var_htv_start.channel, 2);
    return;
}

void rt_htv_end_get_req(char *buf)
{
    int ret;
    s_xml xml;
    char outbuf[10240];
    int srand_id;
    s_var_htv_end var_htv_end;
    s_var_htv_end_get_req   var_htv_end_get_req;

    ROUNTINE_COMM_1(CMD_ID_HTV_END_GET_RES, var_htv_end_get_req, s_var_htv_end_get_req, s_var_htv_end_get_req_index, buf, outbuf, xml, srand_id, ret);
    xxx2varxxx_htv_end(&var_htv_end);
    struct2xml((char *)(&var_htv_end), outbuf, s_var_htv_end_index, all_xml_find_desc);
    rountin_common_res_data(CMD_ID_HTV_END_GET_RES, outbuf, strlen(outbuf), MSG_RES_FLAG_SUC, 0, *(int *)buf);

    return;
}

void rt_htv_end_set_req(char *buf)
{
    int ret;
    s_xml xml;
    char outbuf[10240];
    int srand_id;
    s_var_htv_end_set_req   var_htv_end_set_req;

    ROUNTINE_COMM_1(CMD_ID_HTV_END_SET_RES, var_htv_end_set_req, s_var_htv_end_set_req, s_var_htv_end_set_req_index, buf, outbuf, xml, srand_id, ret);
    varxxx2xxx_htv_end(&var_htv_end_set_req.var_htv_end);
    vs_config_write();
    rountin_common_flag(CMD_ID_HTV_END_SET_RES, MSG_RES_FLAG_SUC, 0, *(int *)buf);

    htv_disable(var_htv_end_set_req.var_htv_end.channel, 2);

    return;
}

void rt_pic_start_get_req(char *buf)
{
    int ret;
    s_xml xml;
    char outbuf[10240];
    int srand_id;
    s_var_pic_start var_pic_start;
    s_var_pic_start_get_req   var_pic_start_get_req;

    ROUNTINE_COMM_1(CMD_ID_PIC_START_GET_RES, var_pic_start_get_req, s_var_pic_start_get_req, s_var_pic_start_get_req_index, buf, outbuf, xml, srand_id, ret);
    xxx2varxxx_pic_start(&var_pic_start);
    struct2xml((char *)(&var_pic_start), outbuf, s_var_pic_start_index, all_xml_find_desc);
    rountin_common_res_data(CMD_ID_PIC_START_GET_RES, outbuf, strlen(outbuf), MSG_RES_FLAG_SUC, 0, *(int *)buf);

    return;
}

void rt_pic_start_set_req(char *buf)
{
    int ret;
    s_xml xml;
    char outbuf[10240];
    int srand_id;
    s_var_pic_start_set_req   var_pic_start_set_req;

    ROUNTINE_COMM_1(CMD_ID_PIC_START_SET_RES, var_pic_start_set_req, s_var_pic_start_set_req, s_var_pic_start_set_req_index, buf, outbuf, xml, srand_id, ret);
//   varxxx2xxx_pic_start(&var_pic_start_set_req.var_pic_start);
// vs_config_write();
//   rountin_common_flag(CMD_ID_PIC_START_SET_RES, MSG_RES_FLAG_SUC, 0, *(int *)buf);

    if ((var_pic_start_set_req.var_pic_start.channel != 1) &&(var_pic_start_set_req.var_pic_start.channel != 0))
        rountin_common_flag(CMD_ID_PIC_START_SET_RES, MSG_RES_FLAG_ERR_CHN, 0, *(int *)buf);
    if (var_pic_start_set_req.var_pic_start.num <= 0)
        rountin_common_flag(CMD_ID_PIC_START_SET_RES, MSG_RES_FLAG_ERR_PIC_NUM, 0, *(int *)buf);
    rountin_common_flag(CMD_ID_PIC_START_SET_RES, MSG_RES_FLAG_SUC, 0, *(int *)buf);

    //抓拍
    cap_enable(var_pic_start_set_req.var_pic_start.channel, var_pic_start_set_req.var_pic_start.num);
    return;
}

void rt_ptz_control_get_req(char *buf)
{
    int ret;
    s_xml xml;
    char outbuf[10240];
    int srand_id;
    s_var_ptz_control var_ptz_control;
    s_var_ptz_control_get_req   var_ptz_control_get_req;

    ROUNTINE_COMM_1(CMD_ID_PTZ_CONTROL_GET_RES, var_ptz_control_get_req, s_var_ptz_control_get_req, s_var_ptz_control_get_req_index, buf, outbuf, xml, srand_id, ret);
    xxx2varxxx_ptz_control(&var_ptz_control);
    struct2xml((char *)(&var_ptz_control), outbuf, s_var_ptz_control_index, all_xml_find_desc);
    rountin_common_res_data(CMD_ID_PTZ_CONTROL_GET_RES, outbuf, strlen(outbuf), MSG_RES_FLAG_SUC, 0, *(int *)buf);

    return;
}

void rt_ptz_control_set_req(char *buf)
{
    int ret;
    s_xml xml;
    char outbuf[10240];
    int srand_id;
    s_var_ptz_control_set_req   var_ptz_control_set_req;

    ROUNTINE_COMM_1(CMD_ID_PTZ_CONTROL_SET_RES, var_ptz_control_set_req, s_var_ptz_control_set_req, s_var_ptz_control_set_req_index, buf, outbuf, xml, srand_id, ret);
//   varxxx2xxx_ptz_control(&var_ptz_control_set_req.var_ptz_control);
// vs_config_write();
    rountin_common_flag(CMD_ID_PTZ_CONTROL_SET_RES, MSG_RES_FLAG_SUC, 0, *(int *)buf);


    plz_start(var_ptz_control_set_req.var_ptz_control);
//    logger(TLOG_NOTICE, "ptz:%d,%d,%d,%d,%d\n", var_ptz_control_set_req.var_ptz_control.channel,
//           var_ptz_control_set_req.var_ptz_control.left, var_ptz_control_set_req.var_ptz_control.right,
//           var_ptz_control_set_req.var_ptz_control.up, var_ptz_control_set_req.var_ptz_control.down);
    return;
}

void rt_sys_quit_get_req(char *buf)
{
    int ret;
    s_xml xml;
    char outbuf[10240];
    int srand_id;
    s_var_sys_quit var_sys_quit;
    s_var_sys_quit_get_req   var_sys_quit_get_req;

    ROUNTINE_COMM_1(CMD_ID_SYS_QUIT_GET_RES, var_sys_quit_get_req, s_var_sys_quit_get_req, s_var_sys_quit_get_req_index, buf, outbuf, xml, srand_id, ret);
    xxx2varxxx_sys_quit(&var_sys_quit);
    struct2xml((char *)(&var_sys_quit), outbuf, s_var_sys_quit_index, all_xml_find_desc);
    rountin_common_res_data(CMD_ID_SYS_QUIT_GET_RES, outbuf, strlen(outbuf), MSG_RES_FLAG_SUC, 0, *(int *)buf);

    return;
}

void rt_sys_quit_set_req(char *buf)
{
    int ret;
    s_xml xml;
    char outbuf[10240];
    int srand_id;
    s_var_sys_quit_set_req   var_sys_quit_set_req;
    ROUNTINE_COMM_1(CMD_ID_SYS_QUIT_SET_RES, var_sys_quit_set_req, s_var_sys_quit_set_req, s_var_sys_quit_set_req_index, buf, outbuf, xml, srand_id, ret);
    if ((1 != ret) && (0 != ret))
    {
        rountin_common_flag(CMD_ID_SYS_QUIT_SET_RES, MSG_RES_FLAG_ERR_LOGIN_PWD, srand_id, *(int *)buf);
        return;
    }
    varxxx2xxx_sys_quit(&var_sys_quit_set_req.var_sys_quit);
//    vs_config_write();
    rountin_common_flag(CMD_ID_SYS_QUIT_SET_RES, MSG_RES_FLAG_SUC, 0, *(int *)buf);

    sys_quit();
    return;
}

void rt_log_get_req(char *buf)
{
    int ret;
    s_xml xml;
    char file_context[MAX_LOG_BUFFER];
    int srand_id;
    int counter, n_read;
//   s_var_log var_log;
    s_var_log_get_req   var_log_get_req;

    memset(file_context,	 0, MAX_LOG_BUFFER);
    ROUNTINE_COMM_1(CMD_ID_LOG_GET_RES, var_log_get_req, s_var_log_get_req, s_var_log_get_req_index, buf, file_context, xml, srand_id, ret);
    if (0 != ret)
    {
        rountin_common_flag(CMD_ID_USER_GET_RES, MSG_RES_FLAG_ERR_LOGIN_PWD, srand_id, *(int *)buf);
        return;
    }
//   xxx2varxxx_log(&var_log);
//   struct2xml((char *)(&var_log), outbuf, s_var_log_index, all_xml_find_desc);

    /******* 读取日志并发送***********************/
    // 填写<Gap>
    memcpy(file_context, "<IPC>", 5);
    counter += 5;


    if (0 == log_file_select)
    {
        rountin_common_flag(CMD_ID_LOG_GET_RES, MSG_RES_FLAG_ERR_FILE, 0, *(int *)buf);
        return ;
    }

    // 目前日志文件是LOGFILE_1，先读LOGFILE_2，读不到说明当前没有LOGFILE_2；再读1
    if (1 == log_file_select)
    {
        n_read = file_read(LOGFILE_2, file_context+counter, MAX_LOG_BUFFER/2, "rb");
        if (-1 == n_read)
        {
            n_read = 0;
        }
        counter += n_read;

        n_read = file_read(LOGFILE_1, file_context + counter, MAX_LOG_BUFFER/2, "rb");
        if (0 > n_read)
        {
            logger(TLOG_ERROR, "rt_log_get_req, file oper failed");
            rountin_common_flag(CMD_ID_LOG_GET_RES, MSG_RES_FLAG_ERR_FILE, 0, *(int *)buf);
            return ;
        }
        counter += n_read;

        // 填写</Gap>
        memcpy(file_context+counter, "</IPC>", 6);
        counter += 6;
        // 组包发送
        rountin_common_res_data(CMD_ID_LOG_GET_RES, file_context, counter, MSG_RES_FLAG_SUC, 0, *(int *)buf);
        return ;
    }

    // 目前日志文件是LOGFILE_2, 应该先读LOGFILE_1，再读LOGFILE_2，任何一个文件读出错，就全错
    n_read = file_read(LOGFILE_1, file_context + counter, MAX_LOG_BUFFER/2, "rb");
    if (-1 == n_read)
    {
        logger(TLOG_ERROR, "rt_log_get_req, file oper failed");
        rountin_common_flag(CMD_ID_LOG_GET_RES, MSG_RES_FLAG_ERR_FILE, 0, *(int *)buf);
        return ;
    }
    counter += n_read;

    n_read = file_read(LOGFILE_2, file_context + counter, MAX_LOG_BUFFER/2, "rb");
    if (0 > n_read)
    {
        logger(TLOG_ERROR, "rt_log_get_req, file oper failed");
        rountin_common_flag(CMD_ID_LOG_GET_RES, MSG_RES_FLAG_ERR_FILE, 0, *(int *)buf);
        return ;
    }
    counter += n_read;

    // 填写</Gap>
    memcpy(file_context+counter, "</IPC>", 6);
    counter += 6;
    // 组包发送
//    logger(TLOG_NOTICE, "rt_log_get_req success");
    rountin_common_res_data(CMD_ID_LOG_GET_RES, file_context, counter, MSG_RES_FLAG_SUC, 0, *(int *)buf);
    return ;

}

void rt_log_set_req(char *buf)
{
    int ret;
    s_xml xml;
    char outbuf[10240];
    int srand_id;
    s_var_log_set_req   var_log_set_req;

    ROUNTINE_COMM_1(CMD_ID_LOG_SET_RES, var_log_set_req, s_var_log_set_req, s_var_log_set_req_index, buf, outbuf, xml, srand_id, ret);
    varxxx2xxx_log(&var_log_set_req.var_log);
    vs_config_write();
    rountin_common_flag(CMD_ID_LOG_SET_RES, MSG_RES_FLAG_SUC, 0, *(int *)buf);

    return;
}

void rt_usb_remove_get_req(char *buf)
{
    int ret;
    s_xml xml;
    char outbuf[10240];
    int srand_id;
    s_var_usb_remove var_usb_remove;
    s_var_usb_remove_get_req   var_usb_remove_get_req;

    ROUNTINE_COMM_1(CMD_ID_USB_REMOVE_GET_RES, var_usb_remove_get_req, s_var_usb_remove_get_req, s_var_usb_remove_get_req_index, buf, outbuf, xml, srand_id, ret);
    xxx2varxxx_usb_remove(&var_usb_remove);
    struct2xml((char *)(&var_usb_remove), outbuf, s_var_usb_remove_index, all_xml_find_desc);
    rountin_common_res_data(CMD_ID_USB_REMOVE_GET_RES, outbuf, strlen(outbuf), MSG_RES_FLAG_SUC, 0, *(int *)buf);

    return;
}

void rt_usb_remove_set_req(char *buf)
{
    int ret;
    s_xml xml;
    char outbuf[10240];
    int srand_id;
    s_var_usb_remove_set_req   var_usb_remove_set_req;

    ROUNTINE_COMM_1(CMD_ID_USB_REMOVE_SET_RES, var_usb_remove_set_req, s_var_usb_remove_set_req, s_var_usb_remove_set_req_index, buf, outbuf, xml, srand_id, ret);
    varxxx2xxx_usb_remove(&var_usb_remove_set_req.var_usb_remove);
    rtv_usb_remove(var_usb_remove_set_req.var_usb_remove.channel);
    rountin_common_flag(CMD_ID_USB_REMOVE_SET_RES, MSG_RES_FLAG_SUC, 0, *(int *)buf);

    return;
}

void rt_hb_get_req(char *buf)
{
    int ret;
    s_xml xml;
    char outbuf[10240];
    int srand_id;
//   s_var_hb var_hb;
    s_var_hb_get_req   var_hb_get_req;

    ROUNTINE_COMM_1(CMD_ID_HB_GET_RES, var_hb_get_req, s_var_hb_get_req, s_var_hb_get_req_index, buf, outbuf, xml, srand_id, ret);
    if ((1 != ret)&&(0 != ret))
    {
        rountin_common_flag(CMD_ID_HB_GET_RES, MSG_RES_FLAG_ERR_LOGIN_PWD, srand_id, *(int *)buf);
        return;
    }
//   xxx2varxxx_hb(&var_hb);
//   struct2xml((char *)(&var_hb), outbuf, s_var_hb_index, all_xml_find_desc);
//   rountin_common_res_data(CMD_ID_HB_GET_RES, outbuf, strlen(outbuf), MSG_RES_FLAG_SUC, 0, *(int *)buf);

    rountin_common_flag(CMD_ID_HB_GET_RES, MSG_RES_FLAG_SUC, 0, *(int *)buf);
    return;
}

void rt_hb_set_req(char *buf)
{
    int ret;
    s_xml xml;
    char outbuf[10240];
    int srand_id;
    s_var_hb_set_req   var_hb_set_req;

    ROUNTINE_COMM_1(CMD_ID_HB_SET_RES, var_hb_set_req, s_var_hb_set_req, s_var_hb_set_req_index, buf, outbuf, xml, srand_id, ret);
    varxxx2xxx_hb(&var_hb_set_req.var_hb);
    vs_config_write();
    rountin_common_flag(CMD_ID_HB_SET_RES, MSG_RES_FLAG_SUC, 0, *(int *)buf);

    return;
}

void rt_def_config_get_req(char *buf)
{
    int ret;
    s_xml xml;
    char outbuf[10240];
    int srand_id;
    s_var_def_config var_def_config;
    s_var_def_config_get_req   var_def_config_get_req;

    ROUNTINE_COMM_1(CMD_ID_DEF_CONFIG_GET_RES, var_def_config_get_req, s_var_def_config_get_req, s_var_def_config_get_req_index, buf, outbuf, xml, srand_id, ret);
    if (0 != ret)
    {
        rountin_common_flag(CMD_ID_USER_GET_RES, MSG_RES_FLAG_ERR_LOGIN_PWD, srand_id, *(int *)buf);
        return;
    }
    xxx2varxxx_def_config(&var_def_config);
    struct2xml((char *)(&var_def_config), outbuf, s_var_def_config_index, all_xml_find_desc);
    rountin_common_res_data(CMD_ID_DEF_CONFIG_GET_RES, outbuf, strlen(outbuf), MSG_RES_FLAG_SUC, 0, *(int *)buf);

    return;
}

void rt_def_config_set_req(char *buf)
{
    int ret;
    s_xml xml;
    char outbuf[10240];
    int srand_id;
    s_var_def_config_set_req   var_def_config_set_req;

    ROUNTINE_COMM_1(CMD_ID_DEF_CONFIG_SET_RES, var_def_config_set_req, s_var_def_config_set_req, s_var_def_config_set_req_index, buf, outbuf, xml, srand_id, ret);
    if (0 != ret)
    {
        rountin_common_flag(CMD_ID_DEF_CONFIG_SET_RES, MSG_RES_FLAG_ERR_LOGIN_PWD, srand_id, *(int *)buf);
        return;
    }
//   varxxx2xxx_def_config(&var_def_config_set_req.var_def_config);
//   vs_config_write();
    rountin_common_flag(CMD_ID_DEF_CONFIG_SET_RES, MSG_RES_FLAG_SUC, 0, *(int *)buf);

    // 恢复出厂设置
//   system("cp -f ./thirdparty/vsftpd.conf /etc/");
//   system("cp -f cp -f ./thirdparty/thttpd.conf /etc/");
    system("cp -f /ipc/thirdparty/ipc.conf /etc/");

    // 停止ipc应用程序，主进程会自动重启子进程
	sys_quit();

    return;
}

// 预留
void rt_md_report_get_req(char *buf)
{
    int ret;
    s_xml xml;
    char outbuf[10240];
    int srand_id;
    s_var_md_report var_md_report;
    s_var_md_report_get_req   var_md_report_get_req;

    ROUNTINE_COMM_1(CMD_ID_MD_REPORT_GET_RES, var_md_report_get_req, s_var_md_report_get_req, s_var_md_report_get_req_index, buf, outbuf, xml, srand_id, ret);
    if (0 != ret)
    {
        rountin_common_flag(CMD_ID_USER_GET_RES, MSG_RES_FLAG_ERR_LOGIN_PWD, srand_id, *(int *)buf);
        return;
    }
    xxx2varxxx_md_report(&var_md_report);
    struct2xml((char *)(&var_md_report), outbuf, s_var_md_report_index, all_xml_find_desc);
    rountin_common_res_data(CMD_ID_MD_REPORT_GET_RES, outbuf, strlen(outbuf), MSG_RES_FLAG_SUC, 0, *(int *)buf);

    return;
}



void rt_md_report_set_req(char *buf)
{
    int ret;
	int len;
//    s_xml xml;
    char outbuf[10240];
//    int srand_id;
	int socket_id = 0;
    s_var_md_report_set_req   var_md_report_set_req;

/*
    ROUNTINE_COMM_1(CMD_ID_MD_REPORT_SET_RES, var_md_report_set_req, s_var_md_report_set_req, s_var_md_report_set_req_index, buf, outbuf, xml, srand_id, ret);
    varxxx2xxx_md_report(&var_md_report_set_req.var_md_report);
    vs_config_write();
    rountin_common_flag(CMD_ID_MD_REPORT_SET_RES, MSG_RES_FLAG_SUC, 0, *(int *)buf);
*/
	strcpy(var_md_report_set_req.user_info.username, IPC_USERNAME);
    strcpy(var_md_report_set_req.user_info.password, IPC_PASSWORD);
    xxx2varxxx_md_report(&var_md_report_set_req.var_md_report);
    md_reset();

    len = struct2xml((char *)(&var_md_report_set_req), outbuf, s_var_md_report_set_req_index, all_xml_find_desc);
    if (0 >= len )
        return;       // 注，这种情况应该不会发生

    ret = vs_connect_initiative(g_config.network.alarm_remote_addr.var, g_config.network.alarm_remote_port.var, &socket_id);
    if ((0 != ret)|| (socket_id <= 0))
        return;

    rountin_common_req_data(CMD_ID_MD_REPORT_SET_REQ, outbuf, strlen(outbuf), 0, socket_id);
    close(socket_id);	
    return;
}

// 预留
void rt_alarm_disk_get_req(char *buf)
{
    int ret;
    s_xml xml;
    char outbuf[10240];
    int srand_id;
    s_var_alarm_disk var_alarm_disk;
    s_var_alarm_disk_get_req   var_alarm_disk_get_req;

    ROUNTINE_COMM_1(CMD_ID_ALARM_DISK_GET_RES, var_alarm_disk_get_req, s_var_alarm_disk_get_req, s_var_alarm_disk_get_req_index, buf, outbuf, xml, srand_id, ret);
    xxx2varxxx_alarm_disk(&var_alarm_disk);
    struct2xml((char *)(&var_alarm_disk), outbuf, s_var_alarm_disk_index, all_xml_find_desc);
    rountin_common_res_data(CMD_ID_ALARM_DISK_GET_RES, outbuf, strlen(outbuf), MSG_RES_FLAG_SUC, 0, *(int *)buf);

    return;
}

// 注意，该RT为IPC主动发起，用来IPC主动发送disk告警给server
void rt_alarm_disk_set_req(char *buf)
{
    int ret;
//    int len1=0;
	int len2=0;
    char outbuf[10240];
//    char outbuf1[1024];
    int socket_id = 0;
    s_var_store_set_req   var_store_set_req;

//   ROUNTINE_COMM_1(CMD_ID_ALARM_DISK_SET_RES, var_alarm_disk_set_req, s_var_alarm_disk_set_req, s_var_alarm_disk_set_req_index, buf, outbuf, xml, srand_id, ret);
//   varxxx2xxx_alarm_disk(&var_alarm_disk_set_req.var_alarm_disk);
//   vs_config_write();
//   rountin_common_flag(CMD_ID_ALARM_DISK_SET_RES, MSG_RES_FLAG_SUC, 0, *(int *)buf);

    memset(outbuf, 0 , 10240);
//    memset(outbuf1, 0, 1024);
    strcpy(var_store_set_req.user_info.username, IPC_USERNAME);
    strcpy(var_store_set_req.user_info.password, IPC_PASSWORD);
    
    xxx2varxxx_store(&var_store_set_req.var_store);
 
//    len1 = struct2xml(&var_alarm_disk_set_req.user_info, outbuf1, s_user_info_index, all_xml_find_desc);
    len2 = struct2xml((char *)&var_store_set_req, outbuf, s_var_store_set_req_index, all_xml_find_desc);
/*
    sprintf(outbuf, "%s%s%d%s%d%s%d%s%d%s%d%s%d%s%d%s\n",
            outbuf1, 
            "<s_var_store sd_status = \"", var_alarm_disk_set_req.var_alarm_disk.sd_status,
            "\" sd_total_size = \"", var_alarm_disk_set_req.var_alarm_disk.sd_total_size,
            "\" sd_used_size = \"", var_alarm_disk_set_req.var_alarm_disk.sd_used_size,
            "\" sd_store_enable = \"", var_alarm_disk_set_req.var_alarm_disk.sd_store_enable,
            "\" auto_cover_older = \"", var_alarm_disk_set_req.var_alarm_disk.auto_cover_older,
            "\" percent_alarm = \"", var_alarm_disk_set_req.var_alarm_disk.percent_alarm,
            "\" percent_del = \"", var_alarm_disk_set_req.var_alarm_disk.percent_del,
            "\" />");
            */
//    printf("alarm disk:outbuf=%s\n", outbuf);

//    len = struct2xml((char *)(&var_alarm_disk_set_req), outbuf, s_var_alarm_disk_set_req_index, all_xml_find_desc);
//    if (0 >= len1 )
//        return;       // 注，这种情况应该不会发生

    ret = vs_connect_initiative(g_config.network.alarm_remote_addr.var, g_config.network.alarm_remote_port.var, &socket_id);
    if ((0 != ret)|| (socket_id <= 0))
        return;
        
    rountin_common_req_data(CMD_ID_ALARM_DISK_SET_REQ, outbuf, strlen(outbuf), 0, socket_id);
    close(socket_id);

    return;
}

void rt_time_syn_get_req(char *buf)
{
    int ret;
    s_xml xml;
    char outbuf[10240];
    int srand_id;
    s_var_time_syn var_time_syn;
    s_var_time_syn_get_req   var_time_syn_get_req;

    ROUNTINE_COMM_1(CMD_ID_TIME_SYN_GET_RES, var_time_syn_get_req, s_var_time_syn_get_req, s_var_time_syn_get_req_index, buf, outbuf, xml, srand_id, ret);
    xxx2varxxx_time_syn(&var_time_syn);
    struct2xml((char *)(&var_time_syn), outbuf, s_var_time_syn_index, all_xml_find_desc);
    rountin_common_res_data(CMD_ID_TIME_SYN_GET_RES, outbuf, strlen(outbuf), MSG_RES_FLAG_SUC, 0, *(int *)buf);

    return;
}

/* 更新系统的日期，格式如下: 2008-10-12 13:14:34*/
void rt_time_syn_set_req(char *buf)
{
    int ret;
    s_xml xml;
    char outbuf[10240];
    int srand_id;
    s_var_time_syn_set_req   var_time_syn_set_req;

    ROUNTINE_COMM_1(CMD_ID_TIME_SYN_SET_RES, var_time_syn_set_req, s_var_time_syn_set_req, s_var_time_syn_set_req_index, buf, outbuf, xml, srand_id, ret);
    if (0 != ret)
    {
        rountin_common_flag(CMD_ID_TIME_SYN_SET_RES, MSG_RES_FLAG_ERR_LOGIN_PWD, srand_id, *(int *)buf);
        return;
    }
//   varxxx2xxx_time_syn(&var_time_syn_set_req.var_time_syn);
//   vs_config_write();
    
    ret = sys_datetime_set(var_time_syn_set_req.var_time_syn.time);
	if(0 != ret)
		rountin_common_flag(CMD_ID_TIME_SYN_SET_RES, MSG_RES_FLAG_ERR_DATETIME_FORMAT, srand_id, *(int *)buf);

	rountin_common_flag(CMD_ID_TIME_SYN_SET_RES, MSG_RES_FLAG_SUC, 0, *(int *)buf);
    return;
}

void rt_alarm_error_get_req(char *buf)
{
   int ret;
   s_xml xml;
   char outbuf[10240];
   int srand_id;
   s_var_alarm_error var_alarm_error;
   s_var_alarm_error_get_req   var_alarm_error_get_req;

   ROUNTINE_COMM_1(CMD_ID_ALARM_ERROR_GET_RES, var_alarm_error_get_req, s_var_alarm_error_get_req, s_var_alarm_error_get_req_index, buf, outbuf, xml, srand_id, ret);
   xxx2varxxx_alarm_error(&var_alarm_error);
   struct2xml((char *)(&var_alarm_error), outbuf, s_var_alarm_error_index, all_xml_find_desc);
   rountin_common_res_data(CMD_ID_ALARM_ERROR_GET_RES, outbuf, strlen(outbuf), MSG_RES_FLAG_SUC, 0, *(int *)buf);

   return;
}

void rt_alarm_error_set_req(char *buf)
{
   int ret;
   s_xml xml;
   char outbuf[1024];
   int srand_id;
   s_var_alarm_error_set_req   var_alarm_error_set_req;
   int len;
   int socket_id = 0;

   strcpy(var_alarm_error_set_req.user_info.username, IPC_USERNAME);
   strcpy(var_alarm_error_set_req.user_info.password, IPC_PASSWORD);
   xxx2varxxx_alarm_error(&var_alarm_error_set_req.var_alarm_error);

   memset(outbuf, 0, 1024);
   len = struct2xml((char *)(&var_alarm_error_set_req), outbuf, s_var_alarm_error_set_req_index, all_xml_find_desc);
   if (0 >= len )
       return;       // 注，这种情况应该不会发生
   
   ret = vs_connect_initiative(g_config.network.alarm_remote_addr.var, g_config.network.alarm_remote_port.var, &socket_id);
   if ((0 != ret)|| (socket_id <= 0))
       return;
   
   rountin_common_req_data(CMD_ID_ALARM_ERROR_SET_REQ, outbuf, strlen(outbuf), 0, socket_id);
   close(socket_id);	 

   return;
}

void rt_process_info_get_req(char *buf)
{
   int ret;
   s_xml xml;
   char outbuf[10240];
   int srand_id;
   s_var_process_info var_process_info;
   s_var_process_info_get_req   var_process_info_get_req;

   char process_info[1024];
   int process_info_len;
   int counter = 0;

   ROUNTINE_COMM_1(CMD_ID_PROCESS_INFO_GET_RES, var_process_info_get_req, s_var_process_info_get_req, s_var_process_info_get_req_index, buf, outbuf, xml, srand_id, ret);

   // 获取进程信息
   memset(process_info,	 0, 1024);
   memset(outbuf,	 0, 10240);
   process_info_len = process_info_get(process_info);
   if(-1 == process_info_len)
   {
        rountin_common_flag(CMD_ID_PROCESS_INFO_GET_RES, MSG_RES_FLAG_ERR_FILE, srand_id, *(int *)buf);  
        return ; 
   }
   
   // 构造进程信息返回消息
   memcpy(outbuf, "<process_info>", 14);
   counter += 14;
   memcpy(outbuf + counter, process_info, process_info_len);
   counter += process_info_len;
   memcpy(outbuf + counter, "</process_info>", 15);
   
   rountin_common_res_data(CMD_ID_PROCESS_INFO_GET_RES, outbuf, strlen(outbuf), MSG_RES_FLAG_SUC, 0, *(int *)buf);

   return;
}

void rt_process_info_set_req(char *buf)
{
   
   return;
}

/*****************************************************************/

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
