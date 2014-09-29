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


#ifndef __VS_XML_H__
#define __VS_XML_H__


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

#include "vs_xml_parser_new.h"

/****************************************************************************************
* 在xml里所定义的各种struct的索引
****************************************************************************************/
/* xml类型序号，每一种不同的xml定义一个序号, 目前程序中仅有一种xml */
#define XML_TYPE_ID_0   0

enum xml_struct_index
{
//    D_var_int_index ,
//    D_var_string_index,
//    D_var_week_string_index,
    s_user_info_index = 0,
    s_var_login_index,
    s_var_login_get_req_index,
    s_var_login_set_req_index,
    s_var_user_index,
    s_var_user_get_req_index,
    s_var_user_set_req_index,
    s_var_video_index,
    s_var_video_get_req_index,
    s_var_video_set_req_index,
    s_var_network_index,
    s_var_network_get_req_index,
    s_var_network_set_req_index,
    s_var_alert_index,
    s_var_alert_get_req_index,
    s_var_alert_set_req_index,
    s_var_store_index,
    s_var_store_get_req_index,
    s_var_store_set_req_index,
    s_var_sys_index,
    s_var_sys_get_req_index,
    s_var_sys_set_req_index,
    s_var_rtv_start_index,
    s_var_rtv_start_get_req_index,
    s_var_rtv_start_set_req_index,
    s_var_htv_start_index,
    s_var_htv_start_get_req_index,
    s_var_htv_start_set_req_index,
    s_var_htv_end_index,
    s_var_htv_end_get_req_index,
    s_var_htv_end_set_req_index,
    s_var_pic_start_index,
    s_var_pic_start_get_req_index,
    s_var_pic_start_set_req_index,   
    s_var_ptz_control_index,
    s_var_ptz_control_get_req_index,
    s_var_ptz_control_set_req_index,
    s_var_sys_quit_index,
    s_var_sys_quit_get_req_index,
    s_var_sys_quit_set_req_index,
    s_var_log_index,
    s_var_log_get_req_index,
    s_var_log_set_req_index,
    s_var_md_report_index,
    s_var_md_report_get_req_index,
    s_var_md_report_set_req_index,
    s_var_usb_remove_index,
    s_var_usb_remove_get_req_index,
	s_var_usb_remove_set_req_index,
	s_var_hb_index,
	s_var_hb_get_req_index,
	s_var_hb_set_req_index,
	s_var_def_config_index,
	s_var_def_config_get_req_index,
	s_var_def_config_set_req_index,
	s_var_alarm_disk_index,
	s_var_alarm_disk_get_req_index,
	s_var_alarm_disk_set_req_index,
    s_var_time_syn_index,
    s_var_time_syn_get_req_index,
    s_var_time_syn_set_req_index,
    s_var_alarm_error_index,
    s_var_alarm_error_get_req_index,
    s_var_alarm_error_set_req_index,
    s_var_process_info_get_req_index,
    
    
    s_xml_test_index
    
};

#define XML_MAXLEN_NAME      32
#define XML_MAXLEN_ADDR      32
#define XML_MAXLEN_MAC       32
#define XML_MAXLEN_PORT      8
#define XML_MAXLEN_PROTO     8


typedef struct tag_xml_rule
{
    int  ID;
    char Name[XML_MAXLEN_NAME];    
    char SrcAddr[XML_MAXLEN_ADDR];
    char SrcMac[XML_MAXLEN_MAC];
    int  SrcPort;
    char Proto[XML_MAXLEN_PROTO];
    char DestAddr[XML_MAXLEN_ADDR];
    char DestMac[XML_MAXLEN_MAC];
    int  DestPort;
} s_xml_rule;


typedef struct tag_xml_test
{  
    char DestAddr[XML_MAXLEN_ADDR];
    char DestMac[XML_MAXLEN_MAC];
    int  DestPort;
} s_xml_test;


int buf_construct_xml(int cmd_head_ID, char *p_struct_data, int *length_xml, char *out_xml_buf);

// 所有xml2struct,,,struct2xml等功能的最后一个参数 all_xml_find_desc
char * all_xml_find_desc(int index, INPUT_MESSAGE *out_inputmsg);
    
#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __VS_PACKAGE_H__ */

