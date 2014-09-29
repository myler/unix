int xxx2varxxx_login(s_var_login *var_login)
{
   var_login->pgh = g_config.login.pgh.var;

   return 0;
}

int xxx2varxxx_user(s_var_user *var_user)
{
   var_user->user_num = g_config.user.user_num.var;
   strcpy(var_user->username_0, g_config.user.username_0.var);
   strcpy(var_user->password_0, g_config.user.password_0.var);
   strcpy(var_user->username_1, g_config.user.username_1.var);
   strcpy(var_user->password_1, g_config.user.password_1.var);
   strcpy(var_user->username_2, g_config.user.username_2.var);
   strcpy(var_user->password_2, g_config.user.password_2.var);
   strcpy(var_user->username_3, g_config.user.username_3.var);
   strcpy(var_user->password_3, g_config.user.password_3.var);

   return 0;
}

int xxx2varxxx_video(s_var_video *var_video)
{
   var_video->rtv_num = g_config.video.rtv_num.var;
   var_video->solution_x_1 = g_config.video.solution_x_1.var;
   var_video->solution_y_1 = g_config.video.solution_y_1.var;
   var_video->bright_1 = g_config.video.bright_1.var;
   var_video->contrast_1 = g_config.video.contrast_1.var;
   var_video->frame_interval_1 = g_config.video.frame_interval_1.var;
   var_video->speed_1 = g_config.video.speed_1.var;
   var_video->cache_time_1 = g_config.video.cache_time_1.var;
   var_video->solution_x_2 = g_config.video.solution_x_2.var;
   var_video->solution_y_2 = g_config.video.solution_y_2.var;
   var_video->bright_2 = g_config.video.bright_2.var;
   var_video->contrast_2 = g_config.video.contrast_2.var;
   var_video->frame_interval_2 = g_config.video.frame_interval_2.var;
   var_video->speed_2 = g_config.video.speed_2.var;
   var_video->cache_time_2 = g_config.video.cache_time_2.var;

   return 0;
}

int xxx2varxxx_network(s_var_network *var_network)
{
   strcpy(var_network->ip_addr, g_config.network.ip_addr.var);
   strcpy(var_network->ip_mask, g_config.network.ip_mask.var);
   strcpy(var_network->ip_gateway, g_config.network.ip_gateway.var);
   strcpy(var_network->dns, g_config.network.dns.var);
   strcpy(var_network->mac_addr, g_config.network.mac_addr.var);
   var_network->web_port = g_config.network.web_port.var;
   var_network->socket_port = g_config.network.socket_port.var;
   var_network->rtv_port = g_config.network.rtv_port.var;
   strcpy(var_network->alarm_remote_addr, g_config.network.alarm_remote_addr.var);
   var_network->alarm_remote_port = g_config.network.alarm_remote_port.var;

   return 0;
}

int xxx2varxxx_alert(s_var_alert *var_alert)
{
   var_alert->alert_num = g_config.alert.alert_num.var;
   var_alert->capture_pic_enable_1 = g_config.alert.capture_pic_enable_1.var;
   var_alert->capture_pic_num_1 = g_config.alert.capture_pic_num_1.var;
   var_alert->capture_pic_interval_1 = g_config.alert.capture_pic_interval_1.var;
   var_alert->capture_video_enable_1 = g_config.alert.capture_video_enable_1.var;
   var_alert->capture_video_last_time_1 = g_config.alert.capture_video_last_time_1.var;
   var_alert->alarm_enable_1 = g_config.alert.alarm_enable_1.var;
   var_alert->alarm_delay_1 = g_config.alert.alarm_delay_1.var;
   var_alert->alarm_last_time_1 = g_config.alert.alarm_last_time_1.var;
   var_alert->md_enable_1 = g_config.alert.md_enable_1.var;
   var_alert->md_sensitivity_1 = g_config.alert.md_sensitivity_1.var;
   strcpy(var_alert->md_area_0_1, g_config.alert.md_area_0_1.var);
   strcpy(var_alert->md_area_1_1, g_config.alert.md_area_1_1.var);
   strcpy(var_alert->md_area_2_1, g_config.alert.md_area_2_1.var);
   strcpy(var_alert->md_area_3_1, g_config.alert.md_area_3_1.var);
   strcpy(var_alert->week_alert_plan_1, g_config.alert.week_alert_plan_1.var);
   var_alert->plan_cap_enalbe_1 = g_config.alert.plan_cap_enalbe_1.var;
   var_alert->plan_cap_last_sec_1 = g_config.alert.plan_cap_last_sec_1.var;
   var_alert->capture_pic_enable_2 = g_config.alert.capture_pic_enable_2.var;
   var_alert->capture_pic_num_2 = g_config.alert.capture_pic_num_2.var;
   var_alert->capture_pic_interval_2 = g_config.alert.capture_pic_interval_2.var;
   var_alert->capture_video_enable_2 = g_config.alert.capture_video_enable_2.var;
   var_alert->capture_video_last_time_2 = g_config.alert.capture_video_last_time_2.var;
   var_alert->alarm_enable_2 = g_config.alert.alarm_enable_2.var;
   var_alert->alarm_delay_2 = g_config.alert.alarm_delay_2.var;
   var_alert->alarm_last_time_2 = g_config.alert.alarm_last_time_2.var;
   var_alert->md_enable_2 = g_config.alert.md_enable_2.var;
   var_alert->md_sensitivity_2 = g_config.alert.md_sensitivity_2.var;
   strcpy(var_alert->md_area_0_2, g_config.alert.md_area_0_2.var);
   strcpy(var_alert->md_area_1_2, g_config.alert.md_area_1_2.var);
   strcpy(var_alert->md_area_2_2, g_config.alert.md_area_2_2.var);
   strcpy(var_alert->md_area_3_2, g_config.alert.md_area_3_2.var);
   strcpy(var_alert->week_alert_plan_2, g_config.alert.week_alert_plan_2.var);
   var_alert->plan_cap_enalbe_2 = g_config.alert.plan_cap_enalbe_2.var;
   var_alert->plan_cap_last_sec_2 = g_config.alert.plan_cap_last_sec_2.var;

   return 0;
}

int xxx2varxxx_store(s_var_store *var_store)
{
   var_store->sd_status = g_config.store.sd_status.var;
   var_store->sd_total_size = g_config.store.sd_total_size.var;
   var_store->sd_used_size = g_config.store.sd_used_size.var;
   var_store->sd_store_enable = g_config.store.sd_store_enable.var;
   var_store->auto_cover_older = g_config.store.auto_cover_older.var;
   var_store->percent_alarm = g_config.store.percent_alarm.var;
   var_store->percent_del = g_config.store.percent_del.var;

   return 0;
}

int xxx2varxxx_sys(s_var_sys *var_sys)
{
   strcpy(var_sys->app_version, g_config.sys.app_version.var);
   strcpy(var_sys->app_time, g_config.sys.app_time.var);

   return 0;
}

int xxx2varxxx_rtv_start(s_var_rtv_start *var_rtv_start)
{
   var_rtv_start->channel = g_config.rtv_start.channel.var;

   return 0;
}

int xxx2varxxx_htv_start(s_var_htv_start *var_htv_start)
{
   var_htv_start->channel = g_config.htv_start.channel.var;

   return 0;
}

int xxx2varxxx_htv_end(s_var_htv_end *var_htv_end)
{
   var_htv_end->channel = g_config.htv_end.channel.var;

   return 0;
}

int xxx2varxxx_pic_start(s_var_pic_start *var_pic_start)
{
   var_pic_start->channel = g_config.pic_start.channel.var;
   var_pic_start->num = g_config.pic_start.num.var;

   return 0;
}

int xxx2varxxx_ptz_control(s_var_ptz_control *var_ptz_control)
{
   var_ptz_control->channel = g_config.ptz_control.channel.var;
   var_ptz_control->left = g_config.ptz_control.left.var;
   var_ptz_control->right = g_config.ptz_control.right.var;
   var_ptz_control->up = g_config.ptz_control.up.var;
   var_ptz_control->down = g_config.ptz_control.down.var;

   return 0;
}

int xxx2varxxx_sys_quit(s_var_sys_quit *var_sys_quit)
{
   var_sys_quit->flag = g_config.sys_quit.flag.var;

   return 0;
}

int xxx2varxxx_log(s_var_log *var_log)
{
   var_log->flag = g_config.log.flag.var;

   return 0;
}

int xxx2varxxx_usb_remove(s_var_usb_remove *var_usb_remove)
{
   var_usb_remove->channel = g_config.usb_remove.channel.var;

   return 0;
}

int xxx2varxxx_hb(s_var_hb *var_hb)
{
   var_hb->flag = g_config.hb.flag.var;

   return 0;
}

int xxx2varxxx_def_config(s_var_def_config *var_def_config)
{
   var_def_config->flag = g_config.def_config.flag.var;

   return 0;
}

int xxx2varxxx_md_report(s_var_md_report *var_md_report)
{
   var_md_report->md_area_0_0 = g_config.md_report.md_area_0_0.var;
   var_md_report->md_area_0_1 = g_config.md_report.md_area_0_1.var;
   var_md_report->md_area_0_2 = g_config.md_report.md_area_0_2.var;
   var_md_report->md_area_0_3 = g_config.md_report.md_area_0_3.var;
   var_md_report->md_area_1_0 = g_config.md_report.md_area_1_0.var;
   var_md_report->md_area_1_1 = g_config.md_report.md_area_1_1.var;
   var_md_report->md_area_1_2 = g_config.md_report.md_area_1_2.var;
   var_md_report->md_area_1_3 = g_config.md_report.md_area_1_3.var;

   return 0;
}

int xxx2varxxx_alarm_disk(s_var_alarm_disk *var_alarm_disk)
{
   var_alarm_disk->flag = g_config.alarm_disk.flag.var;

   return 0;
}

int xxx2varxxx_time_syn(s_var_time_syn *var_time_syn)
{
   strcpy(var_time_syn->time, g_config.time_syn.time.var);

   return 0;
}

int xxx2varxxx_alarm_error(s_var_alarm_error *var_alarm_error)
{
   var_alarm_error->alarm_error_id = g_config.alarm_error.alarm_error_id.var;
   strcpy(var_alarm_error->alarm_error_name, g_config.alarm_error.alarm_error_name.var);

   return 0;
}

int xxx2varxxx_process_info(s_var_process_info *var_process_info)
{
   var_process_info->flag = g_config.process_info.flag.var;

   return 0;
}

int xxx2varxxx_end(s_var_end *var_end)
{
   var_end->flag = g_config.end.flag.var;

   return 0;
}

int varxxx2xxx_login(s_var_login *var_login)
{
   g_config.login.pgh.var = var_login->pgh;

   return 0;
}

int varxxx2xxx_user(s_var_user *var_user)
{
   g_config.user.user_num.var = var_user->user_num;
   strcpy(g_config.user.username_0.var, var_user->username_0);
   strcpy(g_config.user.password_0.var, var_user->password_0);
   strcpy(g_config.user.username_1.var, var_user->username_1);
   strcpy(g_config.user.password_1.var, var_user->password_1);
   strcpy(g_config.user.username_2.var, var_user->username_2);
   strcpy(g_config.user.password_2.var, var_user->password_2);
   strcpy(g_config.user.username_3.var, var_user->username_3);
   strcpy(g_config.user.password_3.var, var_user->password_3);

   return 0;
}

int varxxx2xxx_video(s_var_video *var_video)
{
   g_config.video.rtv_num.var = var_video->rtv_num;
   g_config.video.solution_x_1.var = var_video->solution_x_1;
   g_config.video.solution_y_1.var = var_video->solution_y_1;
   g_config.video.bright_1.var = var_video->bright_1;
   g_config.video.contrast_1.var = var_video->contrast_1;
   g_config.video.frame_interval_1.var = var_video->frame_interval_1;
   g_config.video.speed_1.var = var_video->speed_1;
   g_config.video.cache_time_1.var = var_video->cache_time_1;
   g_config.video.solution_x_2.var = var_video->solution_x_2;
   g_config.video.solution_y_2.var = var_video->solution_y_2;
   g_config.video.bright_2.var = var_video->bright_2;
   g_config.video.contrast_2.var = var_video->contrast_2;
   g_config.video.frame_interval_2.var = var_video->frame_interval_2;
   g_config.video.speed_2.var = var_video->speed_2;
   g_config.video.cache_time_2.var = var_video->cache_time_2;

   return 0;
}

int varxxx2xxx_network(s_var_network *var_network)
{
   strcpy(g_config.network.ip_addr.var, var_network->ip_addr);
   strcpy(g_config.network.ip_mask.var, var_network->ip_mask);
   strcpy(g_config.network.ip_gateway.var, var_network->ip_gateway);
   strcpy(g_config.network.dns.var, var_network->dns);
   strcpy(g_config.network.mac_addr.var, var_network->mac_addr);
   g_config.network.web_port.var = var_network->web_port;
   g_config.network.socket_port.var = var_network->socket_port;
   g_config.network.rtv_port.var = var_network->rtv_port;
   strcpy(g_config.network.alarm_remote_addr.var, var_network->alarm_remote_addr);
   g_config.network.alarm_remote_port.var = var_network->alarm_remote_port;

   return 0;
}

int varxxx2xxx_alert(s_var_alert *var_alert)
{
   g_config.alert.alert_num.var = var_alert->alert_num;
   g_config.alert.capture_pic_enable_1.var = var_alert->capture_pic_enable_1;
   g_config.alert.capture_pic_num_1.var = var_alert->capture_pic_num_1;
   g_config.alert.capture_pic_interval_1.var = var_alert->capture_pic_interval_1;
   g_config.alert.capture_video_enable_1.var = var_alert->capture_video_enable_1;
   g_config.alert.capture_video_last_time_1.var = var_alert->capture_video_last_time_1;
   g_config.alert.alarm_enable_1.var = var_alert->alarm_enable_1;
   g_config.alert.alarm_delay_1.var = var_alert->alarm_delay_1;
   g_config.alert.alarm_last_time_1.var = var_alert->alarm_last_time_1;
   g_config.alert.md_enable_1.var = var_alert->md_enable_1;
   g_config.alert.md_sensitivity_1.var = var_alert->md_sensitivity_1;
   strcpy(g_config.alert.md_area_0_1.var, var_alert->md_area_0_1);
   strcpy(g_config.alert.md_area_1_1.var, var_alert->md_area_1_1);
   strcpy(g_config.alert.md_area_2_1.var, var_alert->md_area_2_1);
   strcpy(g_config.alert.md_area_3_1.var, var_alert->md_area_3_1);
   strcpy(g_config.alert.week_alert_plan_1.var, var_alert->week_alert_plan_1);
   g_config.alert.plan_cap_enalbe_1.var = var_alert->plan_cap_enalbe_1;
   g_config.alert.plan_cap_last_sec_1.var = var_alert->plan_cap_last_sec_1;
   g_config.alert.capture_pic_enable_2.var = var_alert->capture_pic_enable_2;
   g_config.alert.capture_pic_num_2.var = var_alert->capture_pic_num_2;
   g_config.alert.capture_pic_interval_2.var = var_alert->capture_pic_interval_2;
   g_config.alert.capture_video_enable_2.var = var_alert->capture_video_enable_2;
   g_config.alert.capture_video_last_time_2.var = var_alert->capture_video_last_time_2;
   g_config.alert.alarm_enable_2.var = var_alert->alarm_enable_2;
   g_config.alert.alarm_delay_2.var = var_alert->alarm_delay_2;
   g_config.alert.alarm_last_time_2.var = var_alert->alarm_last_time_2;
   g_config.alert.md_enable_2.var = var_alert->md_enable_2;
   g_config.alert.md_sensitivity_2.var = var_alert->md_sensitivity_2;
   strcpy(g_config.alert.md_area_0_2.var, var_alert->md_area_0_2);
   strcpy(g_config.alert.md_area_1_2.var, var_alert->md_area_1_2);
   strcpy(g_config.alert.md_area_2_2.var, var_alert->md_area_2_2);
   strcpy(g_config.alert.md_area_3_2.var, var_alert->md_area_3_2);
   strcpy(g_config.alert.week_alert_plan_2.var, var_alert->week_alert_plan_2);
   g_config.alert.plan_cap_enalbe_2.var = var_alert->plan_cap_enalbe_2;
   g_config.alert.plan_cap_last_sec_2.var = var_alert->plan_cap_last_sec_2;

   return 0;
}

int varxxx2xxx_store(s_var_store *var_store)
{
   g_config.store.sd_status.var = var_store->sd_status;
   g_config.store.sd_total_size.var = var_store->sd_total_size;
   g_config.store.sd_used_size.var = var_store->sd_used_size;
   g_config.store.sd_store_enable.var = var_store->sd_store_enable;
   g_config.store.auto_cover_older.var = var_store->auto_cover_older;
   g_config.store.percent_alarm.var = var_store->percent_alarm;
   g_config.store.percent_del.var = var_store->percent_del;

   return 0;
}

int varxxx2xxx_sys(s_var_sys *var_sys)
{
   strcpy(g_config.sys.app_version.var, var_sys->app_version);
   strcpy(g_config.sys.app_time.var, var_sys->app_time);

   return 0;
}

int varxxx2xxx_rtv_start(s_var_rtv_start *var_rtv_start)
{
   g_config.rtv_start.channel.var = var_rtv_start->channel;

   return 0;
}

int varxxx2xxx_htv_start(s_var_htv_start *var_htv_start)
{
   g_config.htv_start.channel.var = var_htv_start->channel;

   return 0;
}

int varxxx2xxx_htv_end(s_var_htv_end *var_htv_end)
{
   g_config.htv_end.channel.var = var_htv_end->channel;

   return 0;
}

int varxxx2xxx_pic_start(s_var_pic_start *var_pic_start)
{
   g_config.pic_start.channel.var = var_pic_start->channel;
   g_config.pic_start.num.var = var_pic_start->num;

   return 0;
}

int varxxx2xxx_ptz_control(s_var_ptz_control *var_ptz_control)
{
   g_config.ptz_control.channel.var = var_ptz_control->channel;
   g_config.ptz_control.left.var = var_ptz_control->left;
   g_config.ptz_control.right.var = var_ptz_control->right;
   g_config.ptz_control.up.var = var_ptz_control->up;
   g_config.ptz_control.down.var = var_ptz_control->down;

   return 0;
}

int varxxx2xxx_sys_quit(s_var_sys_quit *var_sys_quit)
{
   g_config.sys_quit.flag.var = var_sys_quit->flag;

   return 0;
}

int varxxx2xxx_log(s_var_log *var_log)
{
   g_config.log.flag.var = var_log->flag;

   return 0;
}

int varxxx2xxx_usb_remove(s_var_usb_remove *var_usb_remove)
{
   g_config.usb_remove.channel.var = var_usb_remove->channel;

   return 0;
}

int varxxx2xxx_hb(s_var_hb *var_hb)
{
   g_config.hb.flag.var = var_hb->flag;

   return 0;
}

int varxxx2xxx_def_config(s_var_def_config *var_def_config)
{
   g_config.def_config.flag.var = var_def_config->flag;

   return 0;
}

int varxxx2xxx_md_report(s_var_md_report *var_md_report)
{
   g_config.md_report.md_area_0_0.var = var_md_report->md_area_0_0;
   g_config.md_report.md_area_0_1.var = var_md_report->md_area_0_1;
   g_config.md_report.md_area_0_2.var = var_md_report->md_area_0_2;
   g_config.md_report.md_area_0_3.var = var_md_report->md_area_0_3;
   g_config.md_report.md_area_1_0.var = var_md_report->md_area_1_0;
   g_config.md_report.md_area_1_1.var = var_md_report->md_area_1_1;
   g_config.md_report.md_area_1_2.var = var_md_report->md_area_1_2;
   g_config.md_report.md_area_1_3.var = var_md_report->md_area_1_3;

   return 0;
}

int varxxx2xxx_alarm_disk(s_var_alarm_disk *var_alarm_disk)
{
   g_config.alarm_disk.flag.var = var_alarm_disk->flag;

   return 0;
}

int varxxx2xxx_time_syn(s_var_time_syn *var_time_syn)
{
   strcpy(g_config.time_syn.time.var, var_time_syn->time);

   return 0;
}

int varxxx2xxx_alarm_error(s_var_alarm_error *var_alarm_error)
{
   g_config.alarm_error.alarm_error_id.var = var_alarm_error->alarm_error_id;
   strcpy(g_config.alarm_error.alarm_error_name.var, var_alarm_error->alarm_error_name);

   return 0;
}

int varxxx2xxx_process_info(s_var_process_info *var_process_info)
{
   g_config.process_info.flag.var = var_process_info->flag;

   return 0;
}

int varxxx2xxx_end(s_var_end *var_end)
{
   g_config.end.flag.var = var_end->flag;

   return 0;
}

