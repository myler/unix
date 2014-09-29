/***********************************************************************************
*              Copyright 2007 - 2010, Megaeyes. Co., Ltd.
*                           ALL RIGHTS RESERVED
* FileName: vs_sd.c
* Description: SD卡的相关操作:获取总容量、剩余容量、SD卡状态，并对全局变量g_config.para_store中的相关项进行赋值
*
* History:
* Version   Date              Author  WXW      DefectNum    Description
* 1.1       2008-01-12   q60002125     NULL            Create this file.
***********************************************************************************/
#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

#include "listsOperator.h"
#include "sem.h"
#include "debug.h"
#include "logger.h"

extern s_syn_ctrl syn_ctrl_parse;

// 将数据形成节点,加入到链表,并唤醒解析线程
int receiver_core(char *buf, int buf_len)
{
    int ret; 
    ret = list_node_add(buf, buf_len);
    thread_syn_flag_set(&syn_ctrl_parse.mutex_r, &syn_ctrl_parse.cond_r, &syn_ctrl_parse.flag_r);
    return 0;
}


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
