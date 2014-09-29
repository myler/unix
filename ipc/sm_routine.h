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


#ifndef __SM_ROUTINE_H__
#define __SM_ROUTINE_H__


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

// IPC主动发出消息的用户名和密码
#define IPC_USERNAME                        "IPC"
#define IPC_PASSWORD                        "123456"

#define MSG_RES_FLAG_SUC                    0                // 响应消息，成功
#define MSG_RES_FLAG_ERR_MALLOC             1                // 响应消息，失败，内存分配失败
#define MSG_RES_FLAG_ERR_FILE               2                // 响应消息，失败，文件操作失败
#define MSG_RES_FLAG_ERR_XML                3                // 响应消息，失败，xml错误
#define MSG_RES_FLAG_ERR_LOGIN_USR          4                // 响应消息，失败，登录用户名错误
#define MSG_RES_FLAG_ERR_LOGIN_PWD          5                // 响应消息，失败，登录密码错误
#define MSG_RES_FLAG_ERR_LOGIN_NO           6                // 响应消息，失败，没有登录
#define MSG_RES_FLAG_ERR_LOGIN_TIMEOUT      7                // 响应消息，失败，登录超时
#define MSG_RES_FLAG_ERR_PASSWORD           8                // 响应消息，失败，操作密码验证失败
#define MSG_RES_FLAG_ERR_FORMAT_STA         9                // 响应消息，失败，接收到的消息起始字节不正确
#define MSG_RES_FLAG_ERR_FORMAT_END         10               // 响应消息，失败，接收到的消息结束字节不正确
#define MSG_RES_FLAG_ERR_FORMAT_VER         11               // 响应消息，失败，接收到的消息版本不正确
#define MSG_RES_FLAG_ERR_FORMAT_CMD         12               // 响应消息，失败，接收到的消息版本指令编码不正确
#define MSG_RES_FLAG_ERR_IP                 13               // 响应消息，失败，接收到的IP地址为空

#define MSG_RES_FLAG_ERR_PASSWD_FULL        14               // 响应消息，失败，用户已满，增加新用户失败
#define MSG_RES_FLAG_ERR_PASSWD_EMPTY       15               // 响应消息，失败，用户未找到，删除用户失败
#define MSG_RES_FLAG_ERR_PASSWD_FRAIL       16               // 响应消息，失败，新密码强度不够

#define MSG_RES_FLAG_ERR_CHN                17               // 响应消息，失败，channel号错误
#define MSG_RES_FLAG_ERR_PIC_NUM            18               // 响应消息，失败，抓拍请求的抓拍张数<=0
#define MSG_RES_FLAG_ERR_DATETIME_FORMAT    19               // 响应消息，失败，时间格式不正确
#define MSG_RES_FLAG_ERR_ADMIN_NULL         20               // 响应消息，失败，系统管理员用户名或密码为空

// IPC主动发出的严重错误告警定义
#define MSG_ALARM_ERR_FILE_OPT_ID           1             // 文件操作严重错误，目前针对录像文件保存时的打开失败

typedef struct tag_xml
{
    char *context;
    int len;
} s_xml;

/********************************** IPC begin *******************************************/
#define ROUNTINE_COMM_1(cmd_head_id, var_st, s_var_st, var_st_index, buf, outbuf, xml, srand_id, ret) do{ \
	memset((char *)&var_st, 0, sizeof(s_var_st));			\
    memset(outbuf, 0, 10240);                                                                             \
    srand_id_get(buf, &srand_id);                                                                        \
    xml_get(buf, &xml);                                                                                  \
	ret = xml2struct(xml.context, xml.len, (char *)&var_st, var_st_index, all_xml_find_desc);             \
	if(0 != ret){                                                                                         \
        rountin_common_flag(cmd_head_id, MSG_RES_FLAG_ERR_XML, srand_id, *(int *)buf);                                      \
        return ;                                                                                          \
    }	\
    ret = user_info_check(var_st.user_info.username, var_st.user_info.password);                                \
    if(-1 == ret){                                                                                         \
        rountin_common_flag(cmd_head_id, MSG_RES_FLAG_ERR_LOGIN_PWD, srand_id, *(int *)buf);                                \
        return ;                                                                                          \
    }                                                                                                     \
}while(0)

#define ROUNTINE_COMM_2(cmd_head_id, st, s_st, s_st_index, buf, outbuf, xml, srand_id, ret) do{ \
	memset((char *)&st, 0, sizeof(s_st));			\
    memset(outbuf,	 0, 10240);                                                                             \
    srand_id_get(buf, &srand_id);                                                                        \
    xml_get(buf, &xml);                                                                                  \
	ret = xml2struct(xml.context, xml.len, (char *)&st, s_st_index, all_xml_find_desc);             \
	if(0 != ret){                                                                                         \
        rountin_common_flag(cmd_head_id, MSG_RES_FLAG_ERR_XML, srand_id, *(int *)buf);                                      \
        return ;                                                                                          \
    }	\
    ret = user_info_check(st.username, st.password);                                \
    if(-1 == ret){                                                                                         \
        rountin_common_flag(cmd_head_id, MSG_RES_FLAG_ERR_LOGIN_PWD, srand_id, *(int *)buf);                                \
        return ;                                                                                          \
    }                                                                                                     \
}while(0)


// 发送成功响应
#define ROUNTINE_COMM_RES_SUCCESS(cmd_id, srand_id, socket_id) do{								\
    rountin_common_flag(cmd_id, MSG_RES_FLAG_SUC, srand_id, socket_id);                                            \
}while(0)

// 发送失败响应
#define ROUNTINE_COMM_RES_FAIL(cmd_id, flag, srand_id, socket_id) do{								\
    rountin_common_flag(cmd_id, flag, srand_id, socket_id);                                            \
}while(0)


// rt函数申明
#include "vs_config_rt_h_auto.h"

int rountin_common_flag(int cmd_head_ID, int success_flag, int link_type, int ret_socketid);
int rountin_common_res_data(int cmd_head_ID, char *data, int data_len, int flag, int link_type, int ret_socketid);
int rountin_common_req_data(int cmd_head_ID, char *data, int data_len, int link_type, int ret_socketid);
int limit_video_para();


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __VS_THREAD_H__ */

