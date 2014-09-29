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


#ifndef __VS_PACKAGE_H__
#define __VS_PACKAGE_H__


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

#include "protocol.h"

typedef  char  	int8;
typedef  int    	int32;

int32 package_cmd_req_construct(s_cmd_req_head *cmd_req_head, int cmd_req_head_ID, int length_xml, int srand_id);
int32 package_cmd_res_construct(s_cmd_res_head *cmd_res_head,int cmd_res_head_ID, int length_xml, int srand_id);
int32 package_cmd_res_construct_1(s_cmd_res_head *cmd_res_head,int cmd_res_head_ID, int length_xml, int suc_flag);
    
#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __VS_PACKAGE_H__ */

