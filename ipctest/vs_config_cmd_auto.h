int vs_get_headtype(int head)
{
   switch(head) {
      case CMD_ID_LOGIN_GET_REQ:
      case CMD_ID_USER_GET_REQ:
      case CMD_ID_VIDEO_GET_REQ:
      case CMD_ID_NETWORK_GET_REQ:
      case CMD_ID_ALERT_GET_REQ:
      case CMD_ID_STORE_GET_REQ:
      case CMD_ID_SYS_GET_REQ:
      case CMD_ID_RTV_START_GET_REQ:
      case CMD_ID_HTV_START_GET_REQ:
      case CMD_ID_HTV_END_GET_REQ:
      case CMD_ID_PIC_START_GET_REQ:
      case CMD_ID_PTZ_CONTROL_GET_REQ:
      case CMD_ID_SYS_QUIT_GET_REQ:
      case CMD_ID_LOG_GET_REQ:
      case CMD_ID_USB_REMOVE_GET_REQ:
      case CMD_ID_HB_GET_REQ:
      case CMD_ID_DEF_CONFIG_GET_REQ:
      case CMD_ID_MD_REPORT_GET_REQ:
      case CMD_ID_ALARM_DISK_GET_REQ:
      case CMD_ID_TIME_SYN_GET_REQ:
      case CMD_ID_ALARM_ERROR_GET_REQ:
      case CMD_ID_PROCESS_INFO_GET_REQ:
           return HEAD_REQ_4;

      case CMD_ID_LOGIN_GET_RES:
      case CMD_ID_USER_GET_RES:
      case CMD_ID_VIDEO_GET_RES:
      case CMD_ID_NETWORK_GET_RES:
      case CMD_ID_ALERT_GET_RES:
      case CMD_ID_STORE_GET_RES:
      case CMD_ID_SYS_GET_RES:
      case CMD_ID_RTV_START_GET_RES:
      case CMD_ID_HTV_START_GET_RES:
      case CMD_ID_HTV_END_GET_RES:
      case CMD_ID_PIC_START_GET_RES:
      case CMD_ID_PTZ_CONTROL_GET_RES:
      case CMD_ID_SYS_QUIT_GET_RES:
      case CMD_ID_LOG_GET_RES:
      case CMD_ID_USB_REMOVE_GET_RES:
      case CMD_ID_HB_GET_RES:
      case CMD_ID_DEF_CONFIG_GET_RES:
      case CMD_ID_MD_REPORT_GET_RES:
      case CMD_ID_ALARM_DISK_GET_RES:
      case CMD_ID_TIME_SYN_GET_RES:
      case CMD_ID_ALARM_ERROR_GET_RES:
      case CMD_ID_PROCESS_INFO_GET_RES:
           return HEAD_RES_5;
   }
   return 0;
}



s_cmd2Handler  cmd2Handler[]=
{
   {   CMD_ID_LOGIN_GET_REQ      ,      rt_login_get_req      },
   {   CMD_ID_LOGIN_SET_REQ      ,      rt_login_set_req      },
   {   CMD_ID_USER_GET_REQ      ,      rt_user_get_req      },
   {   CMD_ID_USER_SET_REQ      ,      rt_user_set_req      },
   {   CMD_ID_VIDEO_GET_REQ      ,      rt_video_get_req      },
   {   CMD_ID_VIDEO_SET_REQ      ,      rt_video_set_req      },
   {   CMD_ID_NETWORK_GET_REQ      ,      rt_network_get_req      },
   {   CMD_ID_NETWORK_SET_REQ      ,      rt_network_set_req      },
   {   CMD_ID_ALERT_GET_REQ      ,      rt_alert_get_req      },
   {   CMD_ID_ALERT_SET_REQ      ,      rt_alert_set_req      },
   {   CMD_ID_STORE_GET_REQ      ,      rt_store_get_req      },
   {   CMD_ID_STORE_SET_REQ      ,      rt_store_set_req      },
   {   CMD_ID_SYS_GET_REQ      ,      rt_sys_get_req      },
   {   CMD_ID_SYS_SET_REQ      ,      rt_sys_set_req      },
   {   CMD_ID_RTV_START_GET_REQ      ,      rt_rtv_start_get_req      },
   {   CMD_ID_RTV_START_SET_REQ      ,      rt_rtv_start_set_req      },
   {   CMD_ID_HTV_START_GET_REQ      ,      rt_htv_start_get_req      },
   {   CMD_ID_HTV_START_SET_REQ      ,      rt_htv_start_set_req      },
   {   CMD_ID_HTV_END_GET_REQ      ,      rt_htv_end_get_req      },
   {   CMD_ID_HTV_END_SET_REQ      ,      rt_htv_end_set_req      },
   {   CMD_ID_PIC_START_GET_REQ      ,      rt_pic_start_get_req      },
   {   CMD_ID_PIC_START_SET_REQ      ,      rt_pic_start_set_req      },
   {   CMD_ID_PTZ_CONTROL_GET_REQ      ,      rt_ptz_control_get_req      },
   {   CMD_ID_PTZ_CONTROL_SET_REQ      ,      rt_ptz_control_set_req      },
   {   CMD_ID_SYS_QUIT_GET_REQ      ,      rt_sys_quit_get_req      },
   {   CMD_ID_SYS_QUIT_SET_REQ      ,      rt_sys_quit_set_req      },
   {   CMD_ID_LOG_GET_REQ      ,      rt_log_get_req      },
   {   CMD_ID_LOG_SET_REQ      ,      rt_log_set_req      },
   {   CMD_ID_USB_REMOVE_GET_REQ      ,      rt_usb_remove_get_req      },
   {   CMD_ID_USB_REMOVE_SET_REQ      ,      rt_usb_remove_set_req      },
   {   CMD_ID_HB_GET_REQ      ,      rt_hb_get_req      },
   {   CMD_ID_HB_SET_REQ      ,      rt_hb_set_req      },
   {   CMD_ID_DEF_CONFIG_GET_REQ      ,      rt_def_config_get_req      },
   {   CMD_ID_DEF_CONFIG_SET_REQ      ,      rt_def_config_set_req      },
   {   CMD_ID_MD_REPORT_GET_REQ      ,      rt_md_report_get_req      },
   {   CMD_ID_MD_REPORT_SET_REQ      ,      rt_md_report_set_req      },
   {   CMD_ID_ALARM_DISK_GET_REQ      ,      rt_alarm_disk_get_req      },
   {   CMD_ID_ALARM_DISK_SET_REQ      ,      rt_alarm_disk_set_req      },
   {   CMD_ID_TIME_SYN_GET_REQ      ,      rt_time_syn_get_req      },
   {   CMD_ID_TIME_SYN_SET_REQ      ,      rt_time_syn_set_req      },
   {   CMD_ID_ALARM_ERROR_GET_REQ      ,      rt_alarm_error_get_req      },
   {   CMD_ID_ALARM_ERROR_SET_REQ      ,      rt_alarm_error_set_req      },
   {   CMD_ID_PROCESS_INFO_GET_REQ      ,      rt_process_info_get_req      },
   {   CMD_ID_PROCESS_INFO_SET_REQ      ,      rt_process_info_set_req      },
   {	-1                      , 			NULL	 	            }
};
