// 重写配置文件
int vs_config_write()
{
    FILE *fp = NULL;
    char line[512];
    fp = fopen("/etc/ipc.conf", "w"); 
    if (fp == NULL)
    {
        return 0;
    }
    if (g_config.login.name[0] != '\0')// web登录
    {
        vs_config_box_line(fp, line, g_config.login.name, g_config.login.note);
        vs_config_var_line2(fp, line, g_config.login.pgh.name, g_config.login.pgh.var, g_config.login.pgh.note);
    }
    if (g_config.user.name[0] != '\0')//用户信息  
    {
        vs_config_box_line(fp, line, g_config.user.name, g_config.user.note);
        vs_config_var_line2(fp, line, g_config.user.user_num.name, g_config.user.user_num.var, g_config.user.user_num.note);
        vs_config_var_line(fp, line, g_config.user.username_0.name, g_config.user.username_0.var, g_config.user.username_0.note);
        vs_config_var_line(fp, line, g_config.user.password_0.name, g_config.user.password_0.var, g_config.user.password_0.note);
        vs_config_var_line(fp, line, g_config.user.username_1.name, g_config.user.username_1.var, g_config.user.username_1.note);
        vs_config_var_line(fp, line, g_config.user.password_1.name, g_config.user.password_1.var, g_config.user.password_1.note);
        vs_config_var_line(fp, line, g_config.user.username_2.name, g_config.user.username_2.var, g_config.user.username_2.note);
        vs_config_var_line(fp, line, g_config.user.password_2.name, g_config.user.password_2.var, g_config.user.password_2.note);
        vs_config_var_line(fp, line, g_config.user.username_3.name, g_config.user.username_3.var, g_config.user.username_3.note);
        vs_config_var_line(fp, line, g_config.user.password_3.name, g_config.user.password_3.var, g_config.user.password_3.note);
    }
    if (g_config.video.name[0] != '\0')//视频参数
    {
        vs_config_box_line(fp, line, g_config.video.name, g_config.video.note);
        vs_config_var_line2(fp, line, g_config.video.rtv_num.name, g_config.video.rtv_num.var, g_config.video.rtv_num.note);
        vs_config_var_line2(fp, line, g_config.video.solution_x_1.name, g_config.video.solution_x_1.var, g_config.video.solution_x_1.note);
        vs_config_var_line2(fp, line, g_config.video.solution_y_1.name, g_config.video.solution_y_1.var, g_config.video.solution_y_1.note);
        vs_config_var_line2(fp, line, g_config.video.bright_1.name, g_config.video.bright_1.var, g_config.video.bright_1.note);
        vs_config_var_line2(fp, line, g_config.video.contrast_1.name, g_config.video.contrast_1.var, g_config.video.contrast_1.note);
        vs_config_var_line2(fp, line, g_config.video.frame_interval_1.name, g_config.video.frame_interval_1.var, g_config.video.frame_interval_1.note);
        vs_config_var_line2(fp, line, g_config.video.speed_1.name, g_config.video.speed_1.var, g_config.video.speed_1.note);
        vs_config_var_line2(fp, line, g_config.video.cache_time_1.name, g_config.video.cache_time_1.var, g_config.video.cache_time_1.note);
        vs_config_var_line2(fp, line, g_config.video.solution_x_2.name, g_config.video.solution_x_2.var, g_config.video.solution_x_2.note);
        vs_config_var_line2(fp, line, g_config.video.solution_y_2.name, g_config.video.solution_y_2.var, g_config.video.solution_y_2.note);
        vs_config_var_line2(fp, line, g_config.video.bright_2.name, g_config.video.bright_2.var, g_config.video.bright_2.note);
        vs_config_var_line2(fp, line, g_config.video.contrast_2.name, g_config.video.contrast_2.var, g_config.video.contrast_2.note);
        vs_config_var_line2(fp, line, g_config.video.frame_interval_2.name, g_config.video.frame_interval_2.var, g_config.video.frame_interval_2.note);
        vs_config_var_line2(fp, line, g_config.video.speed_2.name, g_config.video.speed_2.var, g_config.video.speed_2.note);
        vs_config_var_line2(fp, line, g_config.video.cache_time_2.name, g_config.video.cache_time_2.var, g_config.video.cache_time_2.note);
    }
    if (g_config.network.name[0] != '\0')//网络参数
    {
        vs_config_box_line(fp, line, g_config.network.name, g_config.network.note);
        vs_config_var_line(fp, line, g_config.network.ip_addr.name, g_config.network.ip_addr.var, g_config.network.ip_addr.note);
        vs_config_var_line(fp, line, g_config.network.ip_mask.name, g_config.network.ip_mask.var, g_config.network.ip_mask.note);
        vs_config_var_line(fp, line, g_config.network.ip_gateway.name, g_config.network.ip_gateway.var, g_config.network.ip_gateway.note);
        vs_config_var_line(fp, line, g_config.network.dns.name, g_config.network.dns.var, g_config.network.dns.note);
        vs_config_var_line(fp, line, g_config.network.mac_addr.name, g_config.network.mac_addr.var, g_config.network.mac_addr.note);
        vs_config_var_line2(fp, line, g_config.network.web_port.name, g_config.network.web_port.var, g_config.network.web_port.note);
        vs_config_var_line2(fp, line, g_config.network.socket_port.name, g_config.network.socket_port.var, g_config.network.socket_port.note);
        vs_config_var_line2(fp, line, g_config.network.rtv_port.name, g_config.network.rtv_port.var, g_config.network.rtv_port.note);
        vs_config_var_line(fp, line, g_config.network.alarm_remote_addr.name, g_config.network.alarm_remote_addr.var, g_config.network.alarm_remote_addr.note);
        vs_config_var_line2(fp, line, g_config.network.alarm_remote_port.name, g_config.network.alarm_remote_port.var, g_config.network.alarm_remote_port.note);
    }
    if (g_config.alert.name[0] != '\0')//报警参数	
    {
        vs_config_box_line(fp, line, g_config.alert.name, g_config.alert.note);
        vs_config_var_line2(fp, line, g_config.alert.alert_num.name, g_config.alert.alert_num.var, g_config.alert.alert_num.note);
        vs_config_var_line2(fp, line, g_config.alert.capture_pic_enable_1.name, g_config.alert.capture_pic_enable_1.var, g_config.alert.capture_pic_enable_1.note);
        vs_config_var_line2(fp, line, g_config.alert.capture_pic_num_1.name, g_config.alert.capture_pic_num_1.var, g_config.alert.capture_pic_num_1.note);
        vs_config_var_line2(fp, line, g_config.alert.capture_pic_interval_1.name, g_config.alert.capture_pic_interval_1.var, g_config.alert.capture_pic_interval_1.note);
        vs_config_var_line2(fp, line, g_config.alert.capture_video_enable_1.name, g_config.alert.capture_video_enable_1.var, g_config.alert.capture_video_enable_1.note);
        vs_config_var_line2(fp, line, g_config.alert.capture_video_last_time_1.name, g_config.alert.capture_video_last_time_1.var, g_config.alert.capture_video_last_time_1.note);
        vs_config_var_line2(fp, line, g_config.alert.alarm_enable_1.name, g_config.alert.alarm_enable_1.var, g_config.alert.alarm_enable_1.note);
        vs_config_var_line2(fp, line, g_config.alert.alarm_delay_1.name, g_config.alert.alarm_delay_1.var, g_config.alert.alarm_delay_1.note);
        vs_config_var_line2(fp, line, g_config.alert.alarm_last_time_1.name, g_config.alert.alarm_last_time_1.var, g_config.alert.alarm_last_time_1.note);
        vs_config_var_line2(fp, line, g_config.alert.md_enable_1.name, g_config.alert.md_enable_1.var, g_config.alert.md_enable_1.note);
        vs_config_var_line2(fp, line, g_config.alert.md_sensitivity_1.name, g_config.alert.md_sensitivity_1.var, g_config.alert.md_sensitivity_1.note);
        vs_config_var_line(fp, line, g_config.alert.md_area_0_1.name, g_config.alert.md_area_0_1.var, g_config.alert.md_area_0_1.note);
        vs_config_var_line(fp, line, g_config.alert.md_area_1_1.name, g_config.alert.md_area_1_1.var, g_config.alert.md_area_1_1.note);
        vs_config_var_line(fp, line, g_config.alert.md_area_2_1.name, g_config.alert.md_area_2_1.var, g_config.alert.md_area_2_1.note);
        vs_config_var_line(fp, line, g_config.alert.md_area_3_1.name, g_config.alert.md_area_3_1.var, g_config.alert.md_area_3_1.note);
        vs_config_var_line(fp, line, g_config.alert.week_alert_plan_1.name, g_config.alert.week_alert_plan_1.var, g_config.alert.week_alert_plan_1.note);
        vs_config_var_line2(fp, line, g_config.alert.plan_cap_enalbe_1.name, g_config.alert.plan_cap_enalbe_1.var, g_config.alert.plan_cap_enalbe_1.note);
        vs_config_var_line2(fp, line, g_config.alert.plan_cap_last_sec_1.name, g_config.alert.plan_cap_last_sec_1.var, g_config.alert.plan_cap_last_sec_1.note);
        vs_config_var_line2(fp, line, g_config.alert.capture_pic_enable_2.name, g_config.alert.capture_pic_enable_2.var, g_config.alert.capture_pic_enable_2.note);
        vs_config_var_line2(fp, line, g_config.alert.capture_pic_num_2.name, g_config.alert.capture_pic_num_2.var, g_config.alert.capture_pic_num_2.note);
        vs_config_var_line2(fp, line, g_config.alert.capture_pic_interval_2.name, g_config.alert.capture_pic_interval_2.var, g_config.alert.capture_pic_interval_2.note);
        vs_config_var_line2(fp, line, g_config.alert.capture_video_enable_2.name, g_config.alert.capture_video_enable_2.var, g_config.alert.capture_video_enable_2.note);
        vs_config_var_line2(fp, line, g_config.alert.capture_video_last_time_2.name, g_config.alert.capture_video_last_time_2.var, g_config.alert.capture_video_last_time_2.note);
        vs_config_var_line2(fp, line, g_config.alert.alarm_enable_2.name, g_config.alert.alarm_enable_2.var, g_config.alert.alarm_enable_2.note);
        vs_config_var_line2(fp, line, g_config.alert.alarm_delay_2.name, g_config.alert.alarm_delay_2.var, g_config.alert.alarm_delay_2.note);
        vs_config_var_line2(fp, line, g_config.alert.alarm_last_time_2.name, g_config.alert.alarm_last_time_2.var, g_config.alert.alarm_last_time_2.note);
        vs_config_var_line2(fp, line, g_config.alert.md_enable_2.name, g_config.alert.md_enable_2.var, g_config.alert.md_enable_2.note);
        vs_config_var_line2(fp, line, g_config.alert.md_sensitivity_2.name, g_config.alert.md_sensitivity_2.var, g_config.alert.md_sensitivity_2.note);
        vs_config_var_line(fp, line, g_config.alert.md_area_0_2.name, g_config.alert.md_area_0_2.var, g_config.alert.md_area_0_2.note);
        vs_config_var_line(fp, line, g_config.alert.md_area_1_2.name, g_config.alert.md_area_1_2.var, g_config.alert.md_area_1_2.note);
        vs_config_var_line(fp, line, g_config.alert.md_area_2_2.name, g_config.alert.md_area_2_2.var, g_config.alert.md_area_2_2.note);
        vs_config_var_line(fp, line, g_config.alert.md_area_3_2.name, g_config.alert.md_area_3_2.var, g_config.alert.md_area_3_2.note);
        vs_config_var_line(fp, line, g_config.alert.week_alert_plan_2.name, g_config.alert.week_alert_plan_2.var, g_config.alert.week_alert_plan_2.note);
        vs_config_var_line2(fp, line, g_config.alert.plan_cap_enalbe_2.name, g_config.alert.plan_cap_enalbe_2.var, g_config.alert.plan_cap_enalbe_2.note);
        vs_config_var_line2(fp, line, g_config.alert.plan_cap_last_sec_2.name, g_config.alert.plan_cap_last_sec_2.var, g_config.alert.plan_cap_last_sec_2.note);
    }
    if (g_config.store.name[0] != '\0')//存储参数	
    {
        vs_config_box_line(fp, line, g_config.store.name, g_config.store.note);
        vs_config_var_line2(fp, line, g_config.store.sd_status.name, g_config.store.sd_status.var, g_config.store.sd_status.note);
        vs_config_var_line2(fp, line, g_config.store.sd_total_size.name, g_config.store.sd_total_size.var, g_config.store.sd_total_size.note);
        vs_config_var_line2(fp, line, g_config.store.sd_used_size.name, g_config.store.sd_used_size.var, g_config.store.sd_used_size.note);
        vs_config_var_line2(fp, line, g_config.store.sd_store_enable.name, g_config.store.sd_store_enable.var, g_config.store.sd_store_enable.note);
        vs_config_var_line2(fp, line, g_config.store.auto_cover_older.name, g_config.store.auto_cover_older.var, g_config.store.auto_cover_older.note);
        vs_config_var_line2(fp, line, g_config.store.percent_alarm.name, g_config.store.percent_alarm.var, g_config.store.percent_alarm.note);
        vs_config_var_line2(fp, line, g_config.store.percent_del.name, g_config.store.percent_del.var, g_config.store.percent_del.note);
    }
    if (g_config.sys.name[0] != '\0')//系统设置	                        	
    {
        vs_config_box_line(fp, line, g_config.sys.name, g_config.sys.note);
        vs_config_var_line(fp, line, g_config.sys.app_version.name, g_config.sys.app_version.var, g_config.sys.app_version.note);
        vs_config_var_line(fp, line, g_config.sys.app_time.name, g_config.sys.app_time.var, g_config.sys.app_time.note);
    }
    if (g_config.rtv_start.name[0] != '\0')// 实时视频传输请求
    {
        vs_config_box_line(fp, line, g_config.rtv_start.name, g_config.rtv_start.note);
        vs_config_var_line2(fp, line, g_config.rtv_start.channel.name, g_config.rtv_start.channel.var, g_config.rtv_start.channel.note);
    }
    if (g_config.htv_start.name[0] != '\0')// 录像启动请求
    {
        vs_config_box_line(fp, line, g_config.htv_start.name, g_config.htv_start.note);
        vs_config_var_line2(fp, line, g_config.htv_start.channel.name, g_config.htv_start.channel.var, g_config.htv_start.channel.note);
    }
    if (g_config.htv_end.name[0] != '\0')// 录像停止请求
    {
        vs_config_box_line(fp, line, g_config.htv_end.name, g_config.htv_end.note);
        vs_config_var_line2(fp, line, g_config.htv_end.channel.name, g_config.htv_end.channel.var, g_config.htv_end.channel.note);
    }
    if (g_config.pic_start.name[0] != '\0')// 图片抓拍启动请求
    {
        vs_config_box_line(fp, line, g_config.pic_start.name, g_config.pic_start.note);
        vs_config_var_line2(fp, line, g_config.pic_start.channel.name, g_config.pic_start.channel.var, g_config.pic_start.channel.note);
        vs_config_var_line2(fp, line, g_config.pic_start.num.name, g_config.pic_start.num.var, g_config.pic_start.num.note);
    }
    if (g_config.ptz_control.name[0] != '\0')// 云台控制请求
    {
        vs_config_box_line(fp, line, g_config.ptz_control.name, g_config.ptz_control.note);
        vs_config_var_line2(fp, line, g_config.ptz_control.channel.name, g_config.ptz_control.channel.var, g_config.ptz_control.channel.note);
        vs_config_var_line2(fp, line, g_config.ptz_control.left.name, g_config.ptz_control.left.var, g_config.ptz_control.left.note);
        vs_config_var_line2(fp, line, g_config.ptz_control.right.name, g_config.ptz_control.right.var, g_config.ptz_control.right.note);
        vs_config_var_line2(fp, line, g_config.ptz_control.up.name, g_config.ptz_control.up.var, g_config.ptz_control.up.note);
        vs_config_var_line2(fp, line, g_config.ptz_control.down.name, g_config.ptz_control.down.var, g_config.ptz_control.down.note);
    }
    if (g_config.sys_quit.name[0] != '\0')// IPC退出请求
    {
        vs_config_box_line(fp, line, g_config.sys_quit.name, g_config.sys_quit.note);
        vs_config_var_line2(fp, line, g_config.sys_quit.flag.name, g_config.sys_quit.flag.var, g_config.sys_quit.flag.note);
    }
    if (g_config.log.name[0] != '\0')// 日志获取
    {
        vs_config_box_line(fp, line, g_config.log.name, g_config.log.note);
        vs_config_var_line2(fp, line, g_config.log.flag.name, g_config.log.flag.var, g_config.log.flag.note);
    }
    if (g_config.usb_remove.name[0] != '\0')
    {
        vs_config_box_line(fp, line, g_config.usb_remove.name, g_config.usb_remove.note);
        vs_config_var_line2(fp, line, g_config.usb_remove.channel.name, g_config.usb_remove.channel.var, g_config.usb_remove.channel.note);
    }
    if (g_config.hb.name[0] != '\0')// 心跳
    {
        vs_config_box_line(fp, line, g_config.hb.name, g_config.hb.note);
        vs_config_var_line2(fp, line, g_config.hb.flag.name, g_config.hb.flag.var, g_config.hb.flag.note);
    }
    if (g_config.def_config.name[0] != '\0')// 恢复出厂配置
    {
        vs_config_box_line(fp, line, g_config.def_config.name, g_config.def_config.note);
        vs_config_var_line2(fp, line, g_config.def_config.flag.name, g_config.def_config.flag.var, g_config.def_config.flag.note);
    }
    if (g_config.md_report.name[0] != '\0')
    {
        vs_config_box_line(fp, line, g_config.md_report.name, g_config.md_report.note);
        vs_config_var_line2(fp, line, g_config.md_report.md_area_0_0.name, g_config.md_report.md_area_0_0.var, g_config.md_report.md_area_0_0.note);
        vs_config_var_line2(fp, line, g_config.md_report.md_area_0_1.name, g_config.md_report.md_area_0_1.var, g_config.md_report.md_area_0_1.note);
        vs_config_var_line2(fp, line, g_config.md_report.md_area_0_2.name, g_config.md_report.md_area_0_2.var, g_config.md_report.md_area_0_2.note);
        vs_config_var_line2(fp, line, g_config.md_report.md_area_0_3.name, g_config.md_report.md_area_0_3.var, g_config.md_report.md_area_0_3.note);
        vs_config_var_line2(fp, line, g_config.md_report.md_area_1_0.name, g_config.md_report.md_area_1_0.var, g_config.md_report.md_area_1_0.note);
        vs_config_var_line2(fp, line, g_config.md_report.md_area_1_1.name, g_config.md_report.md_area_1_1.var, g_config.md_report.md_area_1_1.note);
        vs_config_var_line2(fp, line, g_config.md_report.md_area_1_2.name, g_config.md_report.md_area_1_2.var, g_config.md_report.md_area_1_2.note);
        vs_config_var_line2(fp, line, g_config.md_report.md_area_1_3.name, g_config.md_report.md_area_1_3.var, g_config.md_report.md_area_1_3.note);
    }
    if (g_config.alarm_disk.name[0] != '\0')// 参数都由存储参数全局变量提供
    {
        vs_config_box_line(fp, line, g_config.alarm_disk.name, g_config.alarm_disk.note);
        vs_config_var_line2(fp, line, g_config.alarm_disk.flag.name, g_config.alarm_disk.flag.var, g_config.alarm_disk.flag.note);
    }
    if (g_config.time_syn.name[0] != '\0')// 时间同步
    {
        vs_config_box_line(fp, line, g_config.time_syn.name, g_config.time_syn.note);
        vs_config_var_line(fp, line, g_config.time_syn.time.name, g_config.time_syn.time.var, g_config.time_syn.time.note);
    }
    if (g_config.alarm_error.name[0] != '\0')// IPC向RTU上报严重错误消息，如录像保存时的open失败
    {
        vs_config_box_line(fp, line, g_config.alarm_error.name, g_config.alarm_error.note);
        vs_config_var_line2(fp, line, g_config.alarm_error.alarm_error_id.name, g_config.alarm_error.alarm_error_id.var, g_config.alarm_error.alarm_error_id.note);
        vs_config_var_line(fp, line, g_config.alarm_error.alarm_error_name.name, g_config.alarm_error.alarm_error_name.var, g_config.alarm_error.alarm_error_name.note);
    }
    if (g_config.process_info.name[0] != '\0')// 获取ipc进程信息
    {
        vs_config_box_line(fp, line, g_config.process_info.name, g_config.process_info.note);
        vs_config_var_line2(fp, line, g_config.process_info.flag.name, g_config.process_info.flag.var, g_config.process_info.flag.note);
    }
    if (g_config.end.name[0] != '\0')
    {
        vs_config_box_line(fp, line, g_config.end.name, g_config.end.note);
        vs_config_var_line2(fp, line, g_config.end.flag.name, g_config.end.flag.var, g_config.end.flag.note);
    }
    fclose(fp);
    return 0;
}

