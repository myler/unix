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
extern "C"{
#endif
#endif /* __cplusplus */

#include "vs_thread.h"
#include "protocol.h"
#include "parser.h"
#include "logger.h"
#include "sm_routine.h"
#include "sem.h"
#include "listsOperator.h"

extern s_syn_ctrl syn_ctrl_parse;

int parser_core(char *buf)
{
    int ret;
    int cmd_head_ID;
    s_cmd_req_head *cmd_req_head = NULL;
    cmd_req_head = (s_cmd_req_head *)(buf+4);

#ifdef parse_debug
	logger(TLOG_NOTICE, "%s:cmd_id=%d,,%d,%d,%d,%d,\n  %d,,%x,%x,%x,%x context=%s", __FUNCTION__, 
			*(int *)(buf+4),*(int *)(buf+4+4),*(int *)(buf+4+4+4),*(int *)(buf+4+4+4+4),*(int *)(buf+20),
			*(buf+12),*(buf+4+4+4),*(buf+4+4+5),*(buf+4+4+6),*(buf+4+4+7),buf+16+4);
#endif

    // 检查版本号，错误则直接返回
    if(100 != cmd_req_head->version)
    {
        logger(TLOG_ERROR, "sm_scp_parser version error, version=%d", cmd_req_head->version);
        rountin_common_flag(CMD_ID_ERR_FORMAT_RES, MSG_RES_FLAG_ERR_FORMAT_VER, 0, *(int *)buf);
        return -1;
    }
    
    cmd_head_ID = cmd_req_head->ID;
    ret = sm_handler(cmd_head_ID, buf);
    return ret;
}

/* 消息解析主线程*/
int thread_parser_main()
{
    struct member *list_node;

    while( !mapThreadID2Handler[THREAD_PARSER].thread_quit_flag )
	{
	    // 取节点，如果链空，阻塞，等待消息接收线程唤醒
	    list_node_get(&list_node);
//		logger(TLOG_NOTICE, "FFFFFFFFFFFFFFFJJ\n");
	    if(NULL == list_node)
	    {
	        thread_syn_flag_clr(&syn_ctrl_parse.mutex_r, &syn_ctrl_parse.cond_r, &syn_ctrl_parse.flag_r);
//logger(TLOG_NOTICE, "SSSSSSSSSSSSSSSSSSS\n");
            thread_syn_wait(&syn_ctrl_parse.mutex_r, &syn_ctrl_parse.cond_r, &syn_ctrl_parse.flag_r);
//logger(TLOG_NOTICE, "DDDDDDDDDDDDDDDDDDDD\n");
            list_node_get(&list_node);          // 唤醒后重新取节点
//logger(TLOG_NOTICE, "WWWWWWWWWWWWWWWWWWW\n");
            if(NULL == list_node)               // 唤醒后取节点仍然空，这种情况应该不会发生
                continue;
	    }
//logger(TLOG_NOTICE, "AAAAAAAAAAAAAAAAAAAAAAA\n");
        parser_core(list_node->data);
//		logger(TLOG_NOTICE, "GGGGGGGGGGGGG\n");
        free(list_node->data);
//		logger(TLOG_NOTICE, "HHHHHHHHHHHH\n");
        free(list_node);
//		logger(TLOG_NOTICE, "JJJJJJJJJJJJJJ\n");
	}

	logger(TLOG_NOTICE, "%s quit", __FUNCTION__);
    return 0;
}



#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

