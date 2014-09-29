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
   varxxx2xxx_video(&var_video_set_req.var_video);
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
   varxxx2xxx_network(&var_network_set_req.var_network);
vs_config_write();
   rountin_common_flag(CMD_ID_NETWORK_SET_RES, MSG_RES_FLAG_SUC, 0, *(int *)buf);

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
   varxxx2xxx_store(&var_store_set_req.var_store);
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
   varxxx2xxx_pic_start(&var_pic_start_set_req.var_pic_start);
vs_config_write();
   rountin_common_flag(CMD_ID_PIC_START_SET_RES, MSG_RES_FLAG_SUC, 0, *(int *)buf);

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
   varxxx2xxx_ptz_control(&var_ptz_control_set_req.var_ptz_control);
vs_config_write();
   rountin_common_flag(CMD_ID_PTZ_CONTROL_SET_RES, MSG_RES_FLAG_SUC, 0, *(int *)buf);

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
   varxxx2xxx_sys_quit(&var_sys_quit_set_req.var_sys_quit);
vs_config_write();
   rountin_common_flag(CMD_ID_SYS_QUIT_SET_RES, MSG_RES_FLAG_SUC, 0, *(int *)buf);

   return;
}

void rt_log_get_req(char *buf)
{
   int ret;
   s_xml xml;
   char outbuf[10240];
   int srand_id;
   s_var_log var_log;
   s_var_log_get_req   var_log_get_req;

   ROUNTINE_COMM_1(CMD_ID_LOG_GET_RES, var_log_get_req, s_var_log_get_req, s_var_log_get_req_index, buf, outbuf, xml, srand_id, ret);
   xxx2varxxx_log(&var_log);
   struct2xml((char *)(&var_log), outbuf, s_var_log_index, all_xml_find_desc);
   rountin_common_res_data(CMD_ID_LOG_GET_RES, outbuf, strlen(outbuf), MSG_RES_FLAG_SUC, 0, *(int *)buf);

   return;
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
vs_config_write();
   rountin_common_flag(CMD_ID_USB_REMOVE_SET_RES, MSG_RES_FLAG_SUC, 0, *(int *)buf);

   return;
}

void rt_hb_get_req(char *buf)
{
   int ret;
   s_xml xml;
   char outbuf[10240];
   int srand_id;
   s_var_hb var_hb;
   s_var_hb_get_req   var_hb_get_req;

   ROUNTINE_COMM_1(CMD_ID_HB_GET_RES, var_hb_get_req, s_var_hb_get_req, s_var_hb_get_req_index, buf, outbuf, xml, srand_id, ret);
   xxx2varxxx_hb(&var_hb);
   struct2xml((char *)(&var_hb), outbuf, s_var_hb_index, all_xml_find_desc);
   rountin_common_res_data(CMD_ID_HB_GET_RES, outbuf, strlen(outbuf), MSG_RES_FLAG_SUC, 0, *(int *)buf);

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
   varxxx2xxx_def_config(&var_def_config_set_req.var_def_config);
vs_config_write();
   rountin_common_flag(CMD_ID_DEF_CONFIG_SET_RES, MSG_RES_FLAG_SUC, 0, *(int *)buf);

   return;
}

void rt_md_report_get_req(char *buf)
{
   int ret;
   s_xml xml;
   char outbuf[10240];
   int srand_id;
   s_var_md_report var_md_report;
   s_var_md_report_get_req   var_md_report_get_req;

   ROUNTINE_COMM_1(CMD_ID_MD_REPORT_GET_RES, var_md_report_get_req, s_var_md_report_get_req, s_var_md_report_get_req_index, buf, outbuf, xml, srand_id, ret);
   xxx2varxxx_md_report(&var_md_report);
   struct2xml((char *)(&var_md_report), outbuf, s_var_md_report_index, all_xml_find_desc);
   rountin_common_res_data(CMD_ID_MD_REPORT_GET_RES, outbuf, strlen(outbuf), MSG_RES_FLAG_SUC, 0, *(int *)buf);

   return;
}

void rt_md_report_set_req(char *buf)
{
   int ret;
   s_xml xml;
   char outbuf[10240];
   int srand_id;
   s_var_md_report_set_req   var_md_report_set_req;

   ROUNTINE_COMM_1(CMD_ID_MD_REPORT_SET_RES, var_md_report_set_req, s_var_md_report_set_req, s_var_md_report_set_req_index, buf, outbuf, xml, srand_id, ret);
   varxxx2xxx_md_report(&var_md_report_set_req.var_md_report);
vs_config_write();
   rountin_common_flag(CMD_ID_MD_REPORT_SET_RES, MSG_RES_FLAG_SUC, 0, *(int *)buf);

   return;
}

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

void rt_alarm_disk_set_req(char *buf)
{
   int ret;
   s_xml xml;
   char outbuf[10240];
   int srand_id;
   s_var_alarm_disk_set_req   var_alarm_disk_set_req;

   ROUNTINE_COMM_1(CMD_ID_ALARM_DISK_SET_RES, var_alarm_disk_set_req, s_var_alarm_disk_set_req, s_var_alarm_disk_set_req_index, buf, outbuf, xml, srand_id, ret);
   varxxx2xxx_alarm_disk(&var_alarm_disk_set_req.var_alarm_disk);
vs_config_write();
   rountin_common_flag(CMD_ID_ALARM_DISK_SET_RES, MSG_RES_FLAG_SUC, 0, *(int *)buf);

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

void rt_time_syn_set_req(char *buf)
{
   int ret;
   s_xml xml;
   char outbuf[10240];
   int srand_id;
   s_var_time_syn_set_req   var_time_syn_set_req;

   ROUNTINE_COMM_1(CMD_ID_TIME_SYN_SET_RES, var_time_syn_set_req, s_var_time_syn_set_req, s_var_time_syn_set_req_index, buf, outbuf, xml, srand_id, ret);
   varxxx2xxx_time_syn(&var_time_syn_set_req.var_time_syn);
vs_config_write();
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
   char outbuf[10240];
   int srand_id;
   s_var_alarm_error_set_req   var_alarm_error_set_req;

   ROUNTINE_COMM_1(CMD_ID_ALARM_ERROR_SET_RES, var_alarm_error_set_req, s_var_alarm_error_set_req, s_var_alarm_error_set_req_index, buf, outbuf, xml, srand_id, ret);
   varxxx2xxx_alarm_error(&var_alarm_error_set_req.var_alarm_error);
vs_config_write();
   rountin_common_flag(CMD_ID_ALARM_ERROR_SET_RES, MSG_RES_FLAG_SUC, 0, *(int *)buf);

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

   ROUNTINE_COMM_1(CMD_ID_PROCESS_INFO_GET_RES, var_process_info_get_req, s_var_process_info_get_req, s_var_process_info_get_req_index, buf, outbuf, xml, srand_id, ret);
   xxx2varxxx_process_info(&var_process_info);
   struct2xml((char *)(&var_process_info), outbuf, s_var_process_info_index, all_xml_find_desc);
   rountin_common_res_data(CMD_ID_PROCESS_INFO_GET_RES, outbuf, strlen(outbuf), MSG_RES_FLAG_SUC, 0, *(int *)buf);

   return;
}

void rt_process_info_set_req(char *buf)
{
   int ret;
   s_xml xml;
   char outbuf[10240];
   int srand_id;
   s_var_process_info_set_req   var_process_info_set_req;

   ROUNTINE_COMM_1(CMD_ID_PROCESS_INFO_SET_RES, var_process_info_set_req, s_var_process_info_set_req, s_var_process_info_set_req_index, buf, outbuf, xml, srand_id, ret);
   varxxx2xxx_process_info(&var_process_info_set_req.var_process_info);
vs_config_write();
   rountin_common_flag(CMD_ID_PROCESS_INFO_SET_RES, MSG_RES_FLAG_SUC, 0, *(int *)buf);

   return;
}

