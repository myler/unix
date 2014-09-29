/******************************************************************************

  Copyright (C), 2001-2011, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name 	: vs_sd.h
  Version		: Initial Draft
  Author		: 
  Created		: 
  Last Modified :
  Description	: vs_sd.c header file
  Function List :
  History		:
  1.Date		: 
	Author		: WXW
	Modification: Created file

******************************************************************************/


#ifndef __VS_SD_H__
#define __VS_SD_H__


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

/*
void get_sd_capacity();
void get_sd_capacity_for_V3();
void get_sd_capacity_for_web();
int  sd_format();
void vs_sd_init();
int sd_test();
int get_sd_status();
void thread_detectsd_main();
*/

int sd_action_insert();
int sd_action_remove();
int sd_status_set();
int sd_status_clr();

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __VS_SD_H__ */

