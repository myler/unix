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


#ifndef __PROTOCOL_H__
#define __PROTOCOL_H__


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */



#define LENGTH_BYTE_32                          32


#define MAX_LEN_USRENAME                        8
#define MAX_LEN_PASSWORD                        8
#define MAX_LEN_RULE_NAME                       16
#define MAX_LEN_RULE_IP                         16
#define LEN_RULE_MAC                            18

// 消息头版本，100:普通消息，101:加密消息
#define CMD_VERSION_NORMAL                      100
#define CMD_VERSION_ENCRYPT                     101

// 命令字
#include "vs_config_cmd_id_auto.h"
#define CMD_ID_ERR_FORMAT_RES        1020


// 命令长度定义
#define HEAD_REQ_4                              4
#define HEAD_RES_5                              5

#define MAX_LEN_SERIAL_PARSER                   1024 * 64

typedef int(*fun_handler)(void *data);
typedef struct tag_cmd2Handler          /*  命令序号，handler对应表   */
{
	int cmd_id;
	void *handler;
} s_cmd2Handler;


/*  请求 命令头 定义  */
typedef struct tag_cmd_req_head
{
    int version;                            /* 版本号       */
    int length;                             /* 指令长度     */
    int ID;                                 /* 指令编号     */
    int srandID;                            /* 指令序号     */
} s_cmd_req_head;

/*  返回命令头 定义  */
typedef struct tag_cmd_res_head
{
    int version;                            /* 版本号       */
    int length;                             /* 指令长度     */
    int ID;                                 /* 指令编号     */
    int srandID;                            /* 指令序号     */
    int flag;                               /* 成功标志     */
} s_cmd_res_head;

#include "vs_config_rt_h_auto.h"
int sm_parser_init();
int vs_get_headtype(int head);
//int thread_parser_main();
int sm_scp_parser(char *buf, int len);
int sm_header_sequence_convert(char *cmd_header, int num);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __VS_THREAD_H__ */
