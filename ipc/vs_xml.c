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


#include "stdlib.h"
#include "vs_xml.h"
//#include "sm_parser.h"
#include "config.h"
#include "vs_config_cmd_id_auto.h"
//#include "vs_config_var_auto.h"



/* 根据命令头编号，构造相应xml  格式字符串 */
/************************************************************************
 * 函数名: buf_construct_xml
 * 作  者: pgh, sx
 * 描  述: 根据命令头编号, 根据命令头编号，构造相应xml  格式字符串
 * 输入参数: int cmd_head_ID, 命令头编号,比如 注册 TermRegister_Req的编号 2002, 回馈2003等 
 *           char *p_struct_data, 是本命令头对应的struct的数据, 根据里面的数据才能正确生成xml
 * 输出参数: int *length_xml, 返回的xml的长度.
 *           char *out_xml_buf, 返回的xml字符串, 如果==NULL,表示仅想得知xml的长度以便分配内存
 * 返回值: 0: 找到并返回, -1: 没有找到这个结构
************************************************************************/
int buf_construct_xml(int cmd_head_ID, char *p_struct_data, int *length_xml, char *out_xml_buf)
{
    int struct_index;

    if ( length_xml == NULL )
        return -1;

    *length_xml = 0;
    struct_index = -1;              // 命令头编号与struct的对应关系
    
    switch (cmd_head_ID) 
    {
//        case XML_TYPE_ID_0:
//            struct_index = s_user_info_index;
//            break;
		case CMD_ID_USER_GET_REQ:
	        struct_index = s_var_user_get_req_index;
	        break;
		case CMD_ID_USER_SET_REQ:
	        struct_index = s_var_user_set_req_index;
	        break;
		case CMD_ID_USER_GET_RES:
	        struct_index = s_var_user_index;
	        break;	
		case CMD_ID_USER_SET_RES:
	        struct_index = s_var_user_index;
	        break;
		default:
            break;
    }

    if (struct_index >= 0)
    {
        *length_xml = struct2xml(p_struct_data, out_xml_buf, struct_index, all_xml_find_desc );
        return 0;
    }
    return -1;
}

/************************************************************************
 * 函数名: all_xml_find_desc
 * 作  者: sx
 * 描  述: 根据xml对应的struct索引, 返回struct描述信息. 这些信息使用工具生成+人工调整.
 *         这里只需要这个函数的名字 all_xml_find_desc, 其参数根本不需要使用者调用
 * 输入参数: int index, 在使用方法上,通常为 该struct的name + "_index", 这是放在enum里枚举过了变量
 * 输出参数: INPUT_MESSAGE *out_inputmsg, 返回的描述信息(总信息)
 * 返回值: 返回的描述信息(分层信息)
************************************************************************/
char * all_xml_find_desc(int index, INPUT_MESSAGE *out_inputmsg)
{
/*
    if (index == D_var_int_index)
    {
        INPUT_MESSAGE msg = { "D_var_int", 1, TEST_MODE };
        FIELD_TYPE fdarray[] =
        {
            {"var",             sizeof(int),             TYPE_INT,     0,            0 }
        };
        return malloc_struct(&msg, (char *)out_inputmsg, fdarray);
    }	

    if (index == D_var_string_index)
    {
        INPUT_MESSAGE msg = { "D_var_string", 1, TEST_MODE };
        FIELD_TYPE fdarray[] =
        {
            {"var",             _LEN_NORMAL,             TYPE_STRING,  0,            0 }
        };
        return malloc_struct(&msg, (char *)out_inputmsg, fdarray);
    }

    if (index == D_var_week_string_index)
    {
        INPUT_MESSAGE msg = { "D_var_week_string", 1, TEST_MODE };
        FIELD_TYPE fdarray[] =
        {
            {"var",             _LEN_WEEK,               TYPE_STRING,  0,            0 }
        };
        return malloc_struct(&msg, (char *)out_inputmsg, fdarray);
    }
*/
    if (index == s_user_info_index)
    {
        INPUT_MESSAGE msg = { "user_info", 2, TEST_MODE };
        FIELD_TYPE fdarray[] =
        {
            {"username",        _LEN_NORMAL,             TYPE_STRING,  0,            0 },
            {"password",        _LEN_NORMAL,             TYPE_STRING,  0,            0 }
        };
        return malloc_struct(&msg, (char *)out_inputmsg, fdarray);
    }

    if (index == s_var_login_index)
    {
        INPUT_MESSAGE msg = { "var_login", 1, TEST_MODE };
        FIELD_TYPE fdarray[] =
        {
            {"pgh",             sizeof(int),             TYPE_INT,     0,            0 }
        };
        return malloc_struct(&msg, (char *)out_inputmsg, fdarray);
    }

    if (index == s_var_login_get_req_index)
    {
        INPUT_MESSAGE msg = { "var_login_get_req", 1, TEST_MODE };
        FIELD_TYPE fdarray[] =
        {
            {"user_info",       sizeof(s_user_info),     TYPE_STRUCT,  0,            s_user_info_index }
        };
        return malloc_struct(&msg, (char *)out_inputmsg, fdarray);
    }

    if (index == s_var_login_set_req_index)
    {
        INPUT_MESSAGE msg = { "var_login_set_req", 2, TEST_MODE };
        FIELD_TYPE fdarray[] =
        {
            {"user_info",       sizeof(s_user_info),     TYPE_STRUCT,  0,            s_user_info_index },
            {"var_login",       sizeof(s_var_login),     TYPE_STRUCT,  0,            s_var_login_index }
        };
        return malloc_struct(&msg, (char *)out_inputmsg, fdarray);
    }

	if (index == s_var_user_index)
	{
	    INPUT_MESSAGE msg = { "var_user", 9, TEST_MODE };
	    FIELD_TYPE fdarray[] =
	    {
	        {"user_num",        sizeof(int),             TYPE_INT,     0,            0 },
	        {"username_0",      _LEN_NORMAL,             TYPE_STRING,  0,            0 },
	        {"password_0",      _LEN_NORMAL,             TYPE_STRING,  0,            0 },
	        {"username_1",      _LEN_NORMAL,             TYPE_STRING,  0,            0 },
	        {"password_1",      _LEN_NORMAL,             TYPE_STRING,  0,            0 },
	        {"username_2",      _LEN_NORMAL,             TYPE_STRING,  0,            0 },
	        {"password_2",      _LEN_NORMAL,             TYPE_STRING,  0,            0 },
	        {"username_3",      _LEN_NORMAL,             TYPE_STRING,  0,            0 },
	        {"password_3",      _LEN_NORMAL,             TYPE_STRING,  0,            0 }
	    };
	    return malloc_struct(&msg, (char *)out_inputmsg, fdarray);
	}

    if (index == s_var_user_get_req_index)
    {
        INPUT_MESSAGE msg = { "var_user_get_req", 1, TEST_MODE };
        FIELD_TYPE fdarray[] =
        {
            {"user_info",       sizeof(s_user_info),     TYPE_STRUCT,  0,            s_user_info_index }
        };
        return malloc_struct(&msg, (char *)out_inputmsg, fdarray);
    }

    if (index == s_var_user_set_req_index)
    {
        INPUT_MESSAGE msg = { "var_user_set_req", 2, TEST_MODE };
        FIELD_TYPE fdarray[] =
        {
            {"user_info",       sizeof(s_user_info),     TYPE_STRUCT,  0,            s_user_info_index },
            {"var_user",        sizeof(s_var_user),      TYPE_STRUCT,  0,            s_var_user_index }
        };
        return malloc_struct(&msg, (char *)out_inputmsg, fdarray);
    }

    if (index == s_var_video_index)
    {
        INPUT_MESSAGE msg = { "var_video", 15, TEST_MODE };
        FIELD_TYPE fdarray[] =
        {
            {"rtv_num",         sizeof(int),             TYPE_INT,     0,            0 },
            {"solution_x_1",    sizeof(int),             TYPE_INT,     0,            0 },
            {"solution_y_1",    sizeof(int),             TYPE_INT,     0,            0 },
            {"bright_1",        sizeof(int),             TYPE_INT,     0,            0 },
            {"contrast_1",      sizeof(int),             TYPE_INT,     0,            0 },
            {"frame_interval_1",sizeof(int),             TYPE_INT,     0,            0 },
            {"speed_1",         sizeof(int),             TYPE_INT,     0,            0 },
            {"cache_time_1",    sizeof(int),             TYPE_INT,     0,            0 },
            {"solution_x_2",    sizeof(int),             TYPE_INT,     0,            0 },
            {"solution_y_2",    sizeof(int),             TYPE_INT,     0,            0 },
            {"bright_2",        sizeof(int),             TYPE_INT,     0,            0 },
            {"contrast_2",      sizeof(int),             TYPE_INT,     0,            0 },
            {"frame_interval_2",sizeof(int),             TYPE_INT,     0,            0 },
            {"speed_2",         sizeof(int),             TYPE_INT,     0,            0 },
            {"cache_time_2",    sizeof(int),             TYPE_INT,     0,            0 }
        };
        return malloc_struct(&msg, (char *)out_inputmsg, fdarray);
    }

    if (index == s_var_video_get_req_index)
    {
        INPUT_MESSAGE msg = { "var_video_get_req", 1, TEST_MODE };
        FIELD_TYPE fdarray[] =
        {
            {"user_info",       sizeof(s_user_info),     TYPE_STRUCT,  0,            s_user_info_index }
        };
        return malloc_struct(&msg, (char *)out_inputmsg, fdarray);
    }

    if (index == s_var_video_set_req_index)
    {
        INPUT_MESSAGE msg = { "var_video_set_req", 2, TEST_MODE };
        FIELD_TYPE fdarray[] =
        {
            {"user_info",       sizeof(s_user_info),     TYPE_STRUCT,  0,            s_user_info_index },
            {"var_video",       sizeof(s_var_video),     TYPE_STRUCT,  0,            s_var_video_index }
        };
        return malloc_struct(&msg, (char *)out_inputmsg, fdarray);
    }

    if (index == s_var_network_index)
	{
	    INPUT_MESSAGE msg = { "var_network", 10, TEST_MODE };
	    FIELD_TYPE fdarray[] =
	    {
	        {"ip_addr",         _LEN_NORMAL,             TYPE_STRING,  0,            0 },
	        {"ip_mask",         _LEN_NORMAL,             TYPE_STRING,  0,            0 },
	        {"ip_gateway",      _LEN_NORMAL,             TYPE_STRING,  0,            0 },
	        {"dns",             _LEN_NORMAL,             TYPE_STRING,  0,            0 },
	        {"mac_addr",        _LEN_NORMAL,             TYPE_STRING,  0,            0 },
	        {"web_port",        sizeof(int),             TYPE_INT,     0,            0 },
	        {"socket_port",     sizeof(int),             TYPE_INT,     0,            0 },
	        {"rtv_port",        sizeof(int),             TYPE_INT,     0,            0 },
	        {"alarm_remote_addr",_LEN_NORMAL,             TYPE_STRING,  0,            0 },
	        {"alarm_remote_port",sizeof(int),             TYPE_INT,     0,            0 }
	    };
	    return malloc_struct(&msg, (char *)out_inputmsg, fdarray);
	}

    if (index == s_var_network_get_req_index)
    {
        INPUT_MESSAGE msg = { "var_network_get_req", 1, TEST_MODE };
        FIELD_TYPE fdarray[] =
        {
            {"user_info",       sizeof(s_user_info),     TYPE_STRUCT,  0,            s_user_info_index }
        };
        return malloc_struct(&msg, (char *)out_inputmsg, fdarray);
    }

    if (index == s_var_network_set_req_index)
    {
        INPUT_MESSAGE msg = { "var_network_set_req", 2, TEST_MODE };
        FIELD_TYPE fdarray[] =
        {
            {"user_info",       sizeof(s_user_info),     TYPE_STRUCT,  0,            s_user_info_index },
            {"var_network",     sizeof(s_var_network),   TYPE_STRUCT,  0,            s_var_network_index }
        };
        return malloc_struct(&msg, (char *)out_inputmsg, fdarray);
    }

	if (index == s_var_alert_index)
	{
	    INPUT_MESSAGE msg = { "var_alert", 35, TEST_MODE };
	    FIELD_TYPE fdarray[] =
	    {
	        {"alert_num",       sizeof(int),             TYPE_INT,     0,            0 },
	        {"capture_pic_enable_1",sizeof(int),             TYPE_INT,     0,            0 },
	        {"capture_pic_num_1",sizeof(int),             TYPE_INT,     0,            0 },
	        {"capture_pic_interval_1",sizeof(int),             TYPE_INT,     0,            0 },
	        {"capture_video_enable_1",sizeof(int),             TYPE_INT,     0,            0 },
	        {"capture_video_last_time_1",sizeof(int),             TYPE_INT,     0,            0 },
	        {"alarm_enable_1",  sizeof(int),             TYPE_INT,     0,            0 },
	        {"alarm_delay_1",   sizeof(int),             TYPE_INT,     0,            0 },
	        {"alarm_last_time_1",sizeof(int),             TYPE_INT,     0,            0 },
	        {"md_enable_1",     sizeof(int),             TYPE_INT,     0,            0 },
	        {"md_sensitivity_1",sizeof(int),             TYPE_INT,     0,            0 },
	        {"md_area_0_1",     _LEN_NORMAL,             TYPE_STRING,  0,            0 },
	        {"md_area_1_1",     _LEN_NORMAL,             TYPE_STRING,  0,            0 },
	        {"md_area_2_1",     _LEN_NORMAL,             TYPE_STRING,  0,            0 },
	        {"md_area_3_1",     _LEN_NORMAL,             TYPE_STRING,  0,            0 },
	        {"week_alert_plan_1",_LEN_WEEK,               TYPE_STRING,  0,            0 },
	        {"plan_cap_enalbe_1",sizeof(int),             TYPE_INT,     0,            0 },
	        {"plan_cap_last_sec_1",sizeof(int),             TYPE_INT,     0,            0 },
	        {"capture_pic_enable_2",sizeof(int),             TYPE_INT,     0,            0 },
	        {"capture_pic_num_2",sizeof(int),             TYPE_INT,     0,            0 },
	        {"capture_pic_interval_2",sizeof(int),             TYPE_INT,     0,            0 },
	        {"capture_video_enable_2",sizeof(int),             TYPE_INT,     0,            0 },
	        {"capture_video_last_time_2",sizeof(int),             TYPE_INT,     0,            0 },
	        {"alarm_enable_2",  sizeof(int),             TYPE_INT,     0,            0 },
	        {"alarm_delay_2",   sizeof(int),             TYPE_INT,     0,            0 },
	        {"alarm_last_time_2",sizeof(int),             TYPE_INT,     0,            0 },
	        {"md_enable_2",     sizeof(int),             TYPE_INT,     0,            0 },
	        {"md_sensitivity_2",sizeof(int),             TYPE_INT,     0,            0 },
	        {"md_area_0_2",     _LEN_NORMAL,             TYPE_STRING,  0,            0 },
	        {"md_area_1_2",     _LEN_NORMAL,             TYPE_STRING,  0,            0 },
	        {"md_area_2_2",     _LEN_NORMAL,             TYPE_STRING,  0,            0 },
	        {"md_area_3_2",     _LEN_NORMAL,             TYPE_STRING,  0,            0 },
	        {"week_alert_plan_2",_LEN_WEEK,               TYPE_STRING,  0,            0 },
	        {"plan_cap_enalbe_2",sizeof(int),             TYPE_INT,     0,            0 },
	        {"plan_cap_last_sec_2",sizeof(int),             TYPE_INT,     0,            0 }
	    };
	    return malloc_struct(&msg, (char *)out_inputmsg, fdarray);
	}    

    if (index == s_var_alert_get_req_index)
    {
        INPUT_MESSAGE msg = { "var_alert_get_req", 1, TEST_MODE };
        FIELD_TYPE fdarray[] =
        {
            {"user_info",       sizeof(s_user_info),     TYPE_STRUCT,  0,            s_user_info_index }
        };
        return malloc_struct(&msg, (char *)out_inputmsg, fdarray);
    }

    if (index == s_var_alert_set_req_index)
    {
        INPUT_MESSAGE msg = { "var_alert_set_req", 2, TEST_MODE };
        FIELD_TYPE fdarray[] =
        {
            {"user_info",       sizeof(s_user_info),     TYPE_STRUCT,  0,            s_user_info_index },
            {"var_alert",       sizeof(s_var_alert),     TYPE_STRUCT,  0,            s_var_alert_index }
        };
        return malloc_struct(&msg, (char *)out_inputmsg, fdarray);
    }

	if (index == s_var_store_index)
	{
	    INPUT_MESSAGE msg = { "var_store", 7, TEST_MODE };
	    FIELD_TYPE fdarray[] =
	    {
	        {"sd_status",       sizeof(int),             TYPE_INT,     0,            0 },
	        {"sd_total_size",   sizeof(int),             TYPE_INT,     0,            0 },
	        {"sd_used_size",    sizeof(int),             TYPE_INT,     0,            0 },
	        {"sd_store_enable", sizeof(int),             TYPE_INT,     0,            0 },
	        {"auto_cover_older",sizeof(int),             TYPE_INT,     0,            0 },
	        {"percent_alarm",   sizeof(int),             TYPE_INT,     0,            0 },
	        {"percent_del",     sizeof(int),             TYPE_INT,     0,            0 }
	    };
	    return malloc_struct(&msg, (char *)out_inputmsg, fdarray);
	}

    if (index == s_var_store_get_req_index)
    {
        INPUT_MESSAGE msg = { "var_store_get_req", 1, TEST_MODE };
        FIELD_TYPE fdarray[] =
        {
            {"user_info",       sizeof(s_user_info),     TYPE_STRUCT,  0,            s_user_info_index }
        };
        return malloc_struct(&msg, (char *)out_inputmsg, fdarray);
    }

    if (index == s_var_store_set_req_index)
    {
        INPUT_MESSAGE msg = { "var_store_set_req", 2, TEST_MODE };
        FIELD_TYPE fdarray[] =
        {
            {"user_info",       sizeof(s_user_info),     TYPE_STRUCT,  0,            s_user_info_index },
            {"var_store",       sizeof(s_var_store),     TYPE_STRUCT,  0,            s_var_store_index }
        };
        return malloc_struct(&msg, (char *)out_inputmsg, fdarray);
    }

    if (index == s_var_sys_index)
    {
        INPUT_MESSAGE msg = { "var_sys", 2, TEST_MODE };
        FIELD_TYPE fdarray[] =
        {
            {"app_version",     _LEN_NORMAL,             TYPE_STRING,  0,            0 },
            {"app_time",        _LEN_NORMAL,             TYPE_STRING,  0,            0 }
        };
        return malloc_struct(&msg, (char *)out_inputmsg, fdarray);
    }

    if (index == s_var_sys_get_req_index)
    {
        INPUT_MESSAGE msg = { "var_sys_get_req", 1, TEST_MODE };
        FIELD_TYPE fdarray[] =
        {
            {"user_info",       sizeof(s_user_info),     TYPE_STRUCT,  0,            s_user_info_index }
        };
        return malloc_struct(&msg, (char *)out_inputmsg, fdarray);
    }

    if (index == s_var_sys_set_req_index)
    {
        INPUT_MESSAGE msg = { "var_sys_set_req", 2, TEST_MODE };
        FIELD_TYPE fdarray[] =
        {
            {"user_info",       sizeof(s_user_info),     TYPE_STRUCT,  0,            s_user_info_index },
            {"var_sys",         sizeof(s_var_sys),       TYPE_STRUCT,  0,            s_var_sys_index }
        };
        return malloc_struct(&msg, (char *)out_inputmsg, fdarray);
    }

	if (index == s_var_rtv_start_index)
	{
	    INPUT_MESSAGE msg = { "var_rtv_start", 1, TEST_MODE };
	    FIELD_TYPE fdarray[] =
	    {
	        {"channel",         sizeof(int),             TYPE_INT,     0,            0 }
	    };
	    return malloc_struct(&msg, (char *)out_inputmsg, fdarray);
	}

    if (index == s_var_rtv_start_get_req_index)
    {
        INPUT_MESSAGE msg = { "var_rtv_start_get_req", 1, TEST_MODE };
        FIELD_TYPE fdarray[] =
        {
            {"user_info",       sizeof(s_user_info),     TYPE_STRUCT,  0,            s_user_info_index }
        };
        return malloc_struct(&msg, (char *)out_inputmsg, fdarray);
    }

    if (index == s_var_rtv_start_set_req_index)
    {
        INPUT_MESSAGE msg = { "var_rtv_start_set_req", 2, TEST_MODE };
        FIELD_TYPE fdarray[] =
        {
            {"user_info",       sizeof(s_user_info),     TYPE_STRUCT,  0,            s_user_info_index },
            {"var_rtv_start",   sizeof(s_var_rtv_start), TYPE_STRUCT,  0,            s_var_rtv_start_index }
        };
        return malloc_struct(&msg, (char *)out_inputmsg, fdarray);
    }

    if (index == s_var_htv_start_index)
    {
        INPUT_MESSAGE msg = { "var_htv_start", 1, TEST_MODE };
        FIELD_TYPE fdarray[] =
        {
            {"channel",         sizeof(int),             TYPE_INT,     0,            0 }
        };
        return malloc_struct(&msg, (char *)out_inputmsg, fdarray);
    }

    if (index == s_var_htv_start_get_req_index)
    {
        INPUT_MESSAGE msg = { "var_htv_start_get_req", 1, TEST_MODE };
        FIELD_TYPE fdarray[] =
        {
            {"user_info",       sizeof(s_user_info),     TYPE_STRUCT,  0,            s_user_info_index }
        };
        return malloc_struct(&msg, (char *)out_inputmsg, fdarray);
    }

    if (index == s_var_htv_start_set_req_index)
    {
        INPUT_MESSAGE msg = { "var_htv_start_set_req", 2, TEST_MODE };
        FIELD_TYPE fdarray[] =
        {
            {"user_info",       sizeof(s_user_info),     TYPE_STRUCT,  0,            s_user_info_index },
            {"var_htv_start",   sizeof(s_var_htv_start), TYPE_STRUCT,  0,            s_var_htv_start_index }
        };
        return malloc_struct(&msg, (char *)out_inputmsg, fdarray);
    }

    if (index == s_var_htv_end_index)
    {
        INPUT_MESSAGE msg = { "var_htv_end", 1, TEST_MODE };
        FIELD_TYPE fdarray[] =
        {
            {"channel",         sizeof(int),             TYPE_INT,     0,            0 }
        };
        return malloc_struct(&msg, (char *)out_inputmsg, fdarray);
    }

    if (index == s_var_htv_end_get_req_index)
    {
        INPUT_MESSAGE msg = { "var_htv_end_get_req", 1, TEST_MODE };
        FIELD_TYPE fdarray[] =
        {
            {"user_info",       sizeof(s_user_info),     TYPE_STRUCT,  0,            s_user_info_index }
        };
        return malloc_struct(&msg, (char *)out_inputmsg, fdarray);
    }


    if (index == s_var_htv_end_set_req_index)
    {
        INPUT_MESSAGE msg = { "var_htv_end_set_req", 2, TEST_MODE };
        FIELD_TYPE fdarray[] =
        {
            {"user_info",       sizeof(s_user_info),     TYPE_STRUCT,  0,            s_user_info_index },
            {"var_htv_end",     sizeof(s_var_htv_end),   TYPE_STRUCT,  0,            s_var_htv_end_index }
        };
        return malloc_struct(&msg, (char *)out_inputmsg, fdarray);
    }

    if (index == s_var_pic_start_index)
    {
        INPUT_MESSAGE msg = { "var_pic_start", 2, TEST_MODE };
        FIELD_TYPE fdarray[] =
        {
            {"channel",         sizeof(int),             TYPE_INT,     0,            0 },
            {"num",             sizeof(int),             TYPE_INT,     0,            0 }
        };
        return malloc_struct(&msg, (char *)out_inputmsg, fdarray);
    }

    if (index == s_var_pic_start_get_req_index)
    {
        INPUT_MESSAGE msg = { "var_pic_start_get_req", 1, TEST_MODE };
        FIELD_TYPE fdarray[] =
        {
            {"user_info",       sizeof(s_user_info),     TYPE_STRUCT,  0,            s_user_info_index }
        };
        return malloc_struct(&msg, (char *)out_inputmsg, fdarray);
    }


    if (index == s_var_pic_start_set_req_index)
    {
        INPUT_MESSAGE msg = { "var_pic_start_set_req", 2, TEST_MODE };
        FIELD_TYPE fdarray[] =
        {
            {"user_info",       sizeof(s_user_info),     TYPE_STRUCT,  0,            s_user_info_index },
            {"var_pic_start",   sizeof(s_var_pic_start), TYPE_STRUCT,  0,            s_var_pic_start_index }
        };
        return malloc_struct(&msg, (char *)out_inputmsg, fdarray);
    }

    if (index == s_var_ptz_control_index)
    {
        INPUT_MESSAGE msg = { "var_ptz_control", 5, TEST_MODE };
        FIELD_TYPE fdarray[] =
        {
            {"channel",         sizeof(int),             TYPE_INT,     0,            0 },
            {"left",            sizeof(int),             TYPE_INT,     0,            0 },
            {"right",           sizeof(int),             TYPE_INT,     0,            0 },
            {"up",              sizeof(int),             TYPE_INT,     0,            0 },
            {"down",            sizeof(int),             TYPE_INT,     0,            0 }
        };
        return malloc_struct(&msg, (char *)out_inputmsg, fdarray);
    }

    if (index == s_var_ptz_control_get_req_index)
    {
        INPUT_MESSAGE msg = { "var_ptz_control_get_req", 1, TEST_MODE };
        FIELD_TYPE fdarray[] =
        {
            {"user_info",       sizeof(s_user_info),     TYPE_STRUCT,  0,            s_user_info_index }
        };
        return malloc_struct(&msg, (char *)out_inputmsg, fdarray);
    }

    if (index == s_var_ptz_control_set_req_index)
    {
        INPUT_MESSAGE msg = { "var_ptz_control_set_req", 2, TEST_MODE };
        FIELD_TYPE fdarray[] =
        {
            {"user_info",       sizeof(s_user_info),     TYPE_STRUCT,  0,            s_user_info_index },
            {"var_ptz_control", sizeof(s_var_ptz_control),TYPE_STRUCT,  0,            s_var_ptz_control_index }
        };
        return malloc_struct(&msg, (char *)out_inputmsg, fdarray);
    }

    if (index == s_var_sys_quit_index)
    {
        INPUT_MESSAGE msg = { "var_sys_quit", 1, TEST_MODE };
        FIELD_TYPE fdarray[] =
        {
            {"flag",            sizeof(int),             TYPE_INT,     0,            0 }
        };
        return malloc_struct(&msg, (char *)out_inputmsg, fdarray);
    }

    if (index == s_var_sys_quit_get_req_index)
    {
        INPUT_MESSAGE msg = { "var_sys_quit_get_req", 1, TEST_MODE };
        FIELD_TYPE fdarray[] =
        {
            {"user_info",       sizeof(s_user_info),     TYPE_STRUCT,  0,            s_user_info_index }
        };
        return malloc_struct(&msg, (char *)out_inputmsg, fdarray);
    }



    if (index == s_var_sys_quit_set_req_index)
    {
        INPUT_MESSAGE msg = { "var_sys_quit_set_req", 2, TEST_MODE };
        FIELD_TYPE fdarray[] =
        {
            {"user_info",       sizeof(s_user_info),     TYPE_STRUCT,  0,            s_user_info_index },
            {"var_sys_quit",    sizeof(s_var_sys_quit),  TYPE_STRUCT,  0,            s_var_sys_quit_index }
        };
        return malloc_struct(&msg, (char *)out_inputmsg, fdarray);
    }

    if (index == s_var_log_index)
    {
        INPUT_MESSAGE msg = { "var_log", 1, TEST_MODE };
        FIELD_TYPE fdarray[] =
        {
            {"flag",            sizeof(int),             TYPE_INT,     0,            0 }
        };
        return malloc_struct(&msg, (char *)out_inputmsg, fdarray);
    }

    if (index == s_var_log_get_req_index)
    {
        INPUT_MESSAGE msg = { "var_log_get_req", 1, TEST_MODE };
        FIELD_TYPE fdarray[] =
        {
            {"user_info",       sizeof(s_user_info),     TYPE_STRUCT,  0,            s_user_info_index }
        };
        return malloc_struct(&msg, (char *)out_inputmsg, fdarray);
    }

    if (index == s_var_log_set_req_index)
    {
        INPUT_MESSAGE msg = { "var_log_set_req", 2, TEST_MODE };
        FIELD_TYPE fdarray[] =
        {
            {"user_info",       sizeof(s_user_info),     TYPE_STRUCT,  0,            s_user_info_index },
            {"var_log",         sizeof(s_var_log),       TYPE_STRUCT,  0,            s_var_log_index }
        };
        return malloc_struct(&msg, (char *)out_inputmsg, fdarray);
    }

    if (index == s_var_md_report_index)
    {
        INPUT_MESSAGE msg = { "var_md_report", 8, TEST_MODE };
        FIELD_TYPE fdarray[] =
        {
            {"md_area_0_0",     sizeof(int),             TYPE_INT,     0,            0 },
            {"md_area_0_1",     sizeof(int),             TYPE_INT,     0,            0 },
            {"md_area_0_2",     sizeof(int),             TYPE_INT,     0,            0 },
            {"md_area_0_3",     sizeof(int),             TYPE_INT,     0,            0 },
            {"md_area_1_0",     sizeof(int),             TYPE_INT,     0,            0 },
            {"md_area_1_1",     sizeof(int),             TYPE_INT,     0,            0 },
            {"md_area_1_2",     sizeof(int),             TYPE_INT,     0,            0 },
            {"md_area_1_3",     sizeof(int),             TYPE_INT,     0,            0 }
        };
        return malloc_struct(&msg, (char *)out_inputmsg, fdarray);
    }

    if (index == s_var_md_report_get_req_index)
    {
        INPUT_MESSAGE msg = { "var_md_report_get_req", 1, TEST_MODE };
        FIELD_TYPE fdarray[] =
        {
            {"user_info",       sizeof(s_user_info),     TYPE_STRUCT,  0,            s_user_info_index }
        };
        return malloc_struct(&msg, (char *)out_inputmsg, fdarray);
    }

    if (index == s_var_md_report_set_req_index)
    {
        INPUT_MESSAGE msg = { "var_md_report_set_req", 2, TEST_MODE };
        FIELD_TYPE fdarray[] =
        {
            {"user_info",       sizeof(s_user_info),     TYPE_STRUCT,  0,            s_user_info_index },
            {"var_md_report",   sizeof(s_var_md_report), TYPE_STRUCT,  0,            s_var_md_report_index }
        };
        return malloc_struct(&msg, (char *)out_inputmsg, fdarray);
    }

	if (index == s_var_usb_remove_index)
	{
	    INPUT_MESSAGE msg = { "var_usb_remove", 1, TEST_MODE };
	    FIELD_TYPE fdarray[] =
	    {
	        {"channel",         sizeof(int),             TYPE_INT,     0,            0 }
	    };
	    return malloc_struct(&msg, (char *)out_inputmsg, fdarray);
	}

	if (index == s_var_usb_remove_get_req_index)
	{
	    INPUT_MESSAGE msg = { "var_usb_remove_get_req", 1, TEST_MODE };
	    FIELD_TYPE fdarray[] =
	    {
	        {"user_info",       sizeof(s_user_info),     TYPE_STRUCT,  0,            s_user_info_index }
	    };
	    return malloc_struct(&msg, (char *)out_inputmsg, fdarray);
	}

	if (index == s_var_usb_remove_set_req_index)
	{
	    INPUT_MESSAGE msg = { "var_usb_remove_set_req", 2, TEST_MODE };
	    FIELD_TYPE fdarray[] =
	    {
	        {"user_info",       sizeof(s_user_info),     TYPE_STRUCT,  0,            s_user_info_index },
	        {"var_usb_remove",  sizeof(s_var_usb_remove),TYPE_STRUCT,  0,            s_var_usb_remove_index }
	    };
	    return malloc_struct(&msg, (char *)out_inputmsg, fdarray);
	}
    
    if (index == s_var_hb_index)
    {
        INPUT_MESSAGE msg = { "var_hb", 1, TEST_MODE };
        FIELD_TYPE fdarray[] =
        {
            {"flag",            sizeof(int),             TYPE_INT,     0,            0 }
        };
        return malloc_struct(&msg, (char *)out_inputmsg, fdarray);
    }

	if (index == s_var_hb_get_req_index)
    {
        INPUT_MESSAGE msg = { "var_hb_get_req", 1, TEST_MODE };
        FIELD_TYPE fdarray[] =
        {
            {"user_info",       sizeof(s_user_info),     TYPE_STRUCT,  0,            s_user_info_index }
        };
        return malloc_struct(&msg, (char *)out_inputmsg, fdarray);
    }

    if (index == s_var_hb_set_req_index)
    {
        INPUT_MESSAGE msg = { "var_hb_set_req", 2, TEST_MODE };
        FIELD_TYPE fdarray[] =
        {
            {"user_info",       sizeof(s_user_info),     TYPE_STRUCT,  0,            s_user_info_index },
            {"var_hb",          sizeof(s_var_hb),        TYPE_STRUCT,  0,            s_var_hb_index }
        };
        return malloc_struct(&msg, (char *)out_inputmsg, fdarray);
    }

	if (index == s_var_def_config_index)
	{
	    INPUT_MESSAGE msg = { "var_def_config", 1, TEST_MODE };
	    FIELD_TYPE fdarray[] =
	    {
	        {"flag",            sizeof(int),             TYPE_INT,     0,            0 }
	    };
	    return malloc_struct(&msg, (char *)out_inputmsg, fdarray);
	}

	if (index == s_var_def_config_get_req_index)
	{
	    INPUT_MESSAGE msg = { "var_def_config_get_req", 1, TEST_MODE };
	    FIELD_TYPE fdarray[] =
	    {
	        {"user_info",       sizeof(s_user_info),     TYPE_STRUCT,  0,            s_user_info_index }
	    };
	    return malloc_struct(&msg, (char *)out_inputmsg, fdarray);
	}
	if (index == s_var_def_config_set_req_index)
	{
	    INPUT_MESSAGE msg = { "var_def_config_set_req", 2, TEST_MODE };
	    FIELD_TYPE fdarray[] =
	    {
	        {"user_info",       sizeof(s_user_info),     TYPE_STRUCT,  0,            s_user_info_index },
	        {"var_def_config",  sizeof(s_var_def_config),TYPE_STRUCT,  0,            s_var_def_config_index }
	    };
	    return malloc_struct(&msg, (char *)out_inputmsg, fdarray);
	}

    if (index == s_var_alarm_disk_index)
    {
        INPUT_MESSAGE msg = { "var_alarm_disk", 7, TEST_MODE };
        FIELD_TYPE fdarray[] =
        {
            {"sd_status",       sizeof(int),             TYPE_INT,     0,            0 },
            {"sd_total_size",   sizeof(int),             TYPE_INT,     0,            0 },
            {"sd_used_size",    sizeof(int),             TYPE_INT,     0,            0 },
            {"sd_store_enable", sizeof(int),             TYPE_INT,     0,            0 },
            {"auto_cover_older",sizeof(int),             TYPE_INT,     0,            0 },
            {"percent_alarm",   sizeof(int),             TYPE_INT,     0,            0 },
            {"percent_del",     sizeof(int),             TYPE_INT,     0,            0 }
        };
        return malloc_struct(&msg, (char *)out_inputmsg, fdarray);
    }

    if (index == s_var_alarm_disk_get_req_index)
    {
        INPUT_MESSAGE msg = { "var_alarm_disk_get_req", 1, TEST_MODE };
        FIELD_TYPE fdarray[] =
        {
            {"user_info",       sizeof(s_user_info),     TYPE_STRUCT,  0,            s_user_info_index }
        };
        return malloc_struct(&msg, (char *)out_inputmsg, fdarray);
    }

    if (index == s_var_alarm_disk_set_req_index)
    {
        INPUT_MESSAGE msg = { "var_alarm_disk_set_req", 2, TEST_MODE };
        FIELD_TYPE fdarray[] =
        {
            {"user_info",       sizeof(s_user_info),     TYPE_STRUCT,  0,            s_user_info_index },
            {"var_alarm_disk",  sizeof(s_var_alarm_disk),TYPE_STRUCT,  0,            s_var_alarm_disk_index }
        };
        return malloc_struct(&msg, (char *)out_inputmsg, fdarray);
    }

    if (index == s_var_time_syn_index)
    {
        INPUT_MESSAGE msg = { "var_time_syn", 1, TEST_MODE };
        FIELD_TYPE fdarray[] =
        {
            {"time",            _LEN_NORMAL,             TYPE_STRING,  0,            0 }
        };
        return malloc_struct(&msg, (char *)out_inputmsg, fdarray);
    }

    if (index == s_var_time_syn_get_req_index)
    {
        INPUT_MESSAGE msg = { "var_time_syn_get_req", 1, TEST_MODE };
        FIELD_TYPE fdarray[] =
        {
            {"user_info",       sizeof(s_user_info),     TYPE_STRUCT,  0,            s_user_info_index }
        };
        return malloc_struct(&msg, (char *)out_inputmsg, fdarray);
    }

    if (index == s_var_time_syn_set_req_index)
    {
        INPUT_MESSAGE msg = { "var_time_syn_set_req", 2, TEST_MODE };
        FIELD_TYPE fdarray[] =
        {
            {"user_info",       sizeof(s_user_info),     TYPE_STRUCT,  0,            s_user_info_index },
            {"var_time_syn",    sizeof(s_var_time_syn),  TYPE_STRUCT,  0,            s_var_time_syn_index }
        };
        return malloc_struct(&msg, (char *)out_inputmsg, fdarray);
    }

    if (index == s_var_alarm_error_index)
    {
        INPUT_MESSAGE msg = { "var_alarm_error", 2, TEST_MODE };
        FIELD_TYPE fdarray[] =
        {
            {"alarm_error_id",  sizeof(int),             TYPE_INT,     0,            0 },
            {"alarm_error_name",_LEN_NORMAL,             TYPE_STRING,  0,            0 }
        };
        return malloc_struct(&msg, (char *)out_inputmsg, fdarray);
    }

    if (index == s_var_alarm_error_get_req_index)
    {
        INPUT_MESSAGE msg = { "var_alarm_error_get_req", 1, TEST_MODE };
        FIELD_TYPE fdarray[] =
        {
            {"user_info",       sizeof(s_user_info),     TYPE_STRUCT,  0,            s_user_info_index }
        };
        return malloc_struct(&msg, (char *)out_inputmsg, fdarray);
    }

    if (index == s_var_alarm_error_set_req_index)
    {
        INPUT_MESSAGE msg = { "var_alarm_error_set_req", 2, TEST_MODE };
        FIELD_TYPE fdarray[] =
        {
            {"user_info",       sizeof(s_user_info),     TYPE_STRUCT,  0,            s_user_info_index },
            {"var_alarm_error", sizeof(s_var_alarm_error),TYPE_STRUCT,  0,            s_var_alarm_error_index }
        };
        return malloc_struct(&msg, (char *)out_inputmsg, fdarray);
    }

    if (index == s_var_process_info_get_req_index)
    {
        INPUT_MESSAGE msg = { "var_process_info_get_req", 1, TEST_MODE };
        FIELD_TYPE fdarray[] =
        {
            {"user_info",       sizeof(s_user_info),     TYPE_STRUCT,  0,            s_user_info_index }
        };
        return malloc_struct(&msg, (char *)out_inputmsg, fdarray);
    }
    
    return NULL;
}

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
