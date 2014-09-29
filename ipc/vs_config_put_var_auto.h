int vs_config_put_var(char *name, char *var, char *note)
{
    if ( name[0] == '\0' && var[0] != '\0' )
    {
        if ( strcmp(var, "login") == 0 )// web登录
        {
            g_config.config_index = CFG_login;
            strcpy(g_config.login.name, var);
            strcpy(g_config.login.note, note);
        }
        else if ( strcmp(var, "user") == 0 )//用户信息  
        {
            g_config.config_index = CFG_user;
            strcpy(g_config.user.name, var);
            strcpy(g_config.user.note, note);
        }
        else if ( strcmp(var, "video") == 0 )//视频参数
        {
            g_config.config_index = CFG_video;
            strcpy(g_config.video.name, var);
            strcpy(g_config.video.note, note);
        }
        else if ( strcmp(var, "network") == 0 )//网络参数
        {
            g_config.config_index = CFG_network;
            strcpy(g_config.network.name, var);
            strcpy(g_config.network.note, note);
        }
        else if ( strcmp(var, "alert") == 0 )//报警参数	
        {
            g_config.config_index = CFG_alert;
            strcpy(g_config.alert.name, var);
            strcpy(g_config.alert.note, note);
        }
        else if ( strcmp(var, "store") == 0 )//存储参数	
        {
            g_config.config_index = CFG_store;
            strcpy(g_config.store.name, var);
            strcpy(g_config.store.note, note);
        }
        else if ( strcmp(var, "sys") == 0 )//系统设置	                        	
        {
            g_config.config_index = CFG_sys;
            strcpy(g_config.sys.name, var);
            strcpy(g_config.sys.note, note);
        }
        else if ( strcmp(var, "rtv_start") == 0 )// 实时视频传输请求
        {
            g_config.config_index = CFG_rtv_start;
            strcpy(g_config.rtv_start.name, var);
            strcpy(g_config.rtv_start.note, note);
        }
        else if ( strcmp(var, "htv_start") == 0 )// 录像启动请求
        {
            g_config.config_index = CFG_htv_start;
            strcpy(g_config.htv_start.name, var);
            strcpy(g_config.htv_start.note, note);
        }
        else if ( strcmp(var, "htv_end") == 0 )// 录像停止请求
        {
            g_config.config_index = CFG_htv_end;
            strcpy(g_config.htv_end.name, var);
            strcpy(g_config.htv_end.note, note);
        }
        else if ( strcmp(var, "pic_start") == 0 )// 图片抓拍启动请求
        {
            g_config.config_index = CFG_pic_start;
            strcpy(g_config.pic_start.name, var);
            strcpy(g_config.pic_start.note, note);
        }
        else if ( strcmp(var, "ptz_control") == 0 )// 云台控制请求
        {
            g_config.config_index = CFG_ptz_control;
            strcpy(g_config.ptz_control.name, var);
            strcpy(g_config.ptz_control.note, note);
        }
        else if ( strcmp(var, "sys_quit") == 0 )// IPC退出请求
        {
            g_config.config_index = CFG_sys_quit;
            strcpy(g_config.sys_quit.name, var);
            strcpy(g_config.sys_quit.note, note);
        }
        else if ( strcmp(var, "log") == 0 )// 日志获取
        {
            g_config.config_index = CFG_log;
            strcpy(g_config.log.name, var);
            strcpy(g_config.log.note, note);
        }
        else if ( strcmp(var, "usb_remove") == 0 )
        {
            g_config.config_index = CFG_usb_remove;
            strcpy(g_config.usb_remove.name, var);
            strcpy(g_config.usb_remove.note, note);
        }
        else if ( strcmp(var, "hb") == 0 )// 心跳
        {
            g_config.config_index = CFG_hb;
            strcpy(g_config.hb.name, var);
            strcpy(g_config.hb.note, note);
        }
        else if ( strcmp(var, "def_config") == 0 )// 恢复出厂配置
        {
            g_config.config_index = CFG_def_config;
            strcpy(g_config.def_config.name, var);
            strcpy(g_config.def_config.note, note);
        }
        else if ( strcmp(var, "md_report") == 0 )
        {
            g_config.config_index = CFG_md_report;
            strcpy(g_config.md_report.name, var);
            strcpy(g_config.md_report.note, note);
        }
        else if ( strcmp(var, "alarm_disk") == 0 )// 参数都由存储参数全局变量提供
        {
            g_config.config_index = CFG_alarm_disk;
            strcpy(g_config.alarm_disk.name, var);
            strcpy(g_config.alarm_disk.note, note);
        }
        else if ( strcmp(var, "time_syn") == 0 )// 时间同步
        {
            g_config.config_index = CFG_time_syn;
            strcpy(g_config.time_syn.name, var);
            strcpy(g_config.time_syn.note, note);
        }
        else if ( strcmp(var, "alarm_error") == 0 )// IPC向RTU上报严重错误消息，如录像保存时的open失败
        {
            g_config.config_index = CFG_alarm_error;
            strcpy(g_config.alarm_error.name, var);
            strcpy(g_config.alarm_error.note, note);
        }
        else if ( strcmp(var, "process_info") == 0 )// 获取ipc进程信息
        {
            g_config.config_index = CFG_process_info;
            strcpy(g_config.process_info.name, var);
            strcpy(g_config.process_info.note, note);
        }
        else if ( strcmp(var, "end") == 0 )
        {
            g_config.config_index = CFG_end;
            strcpy(g_config.end.name, var);
            strcpy(g_config.end.note, note);
        }
        return 0;
    }

    // 所有具体的数值
    if ( g_config.config_index == CFG_login)// web登录
    {
        if ( strcmp( name, "pgh" ) == 0 )
        {
            strcpy( g_config.login.pgh.name, name );
            strcpy( g_config.login.pgh.note, note );
            g_config.login.pgh.var = atoi( var );
        }
    }
    else if ( g_config.config_index == CFG_user)//用户信息  
    {
        if ( strcmp( name, "user_num" ) == 0 )
        {
            strcpy( g_config.user.user_num.name, name );
            strcpy( g_config.user.user_num.note, note );
            g_config.user.user_num.var = atoi( var );
        }
        if ( strcmp( name, "username_0" ) == 0 )// username_0系统管理员
        {
            strcpy( g_config.user.username_0.name, name );
            strcpy( g_config.user.username_0.note, note );
            strcpy( g_config.user.username_0.var, var );
        }
        if ( strcmp( name, "password_0" ) == 0 )
        {
            strcpy( g_config.user.password_0.name, name );
            strcpy( g_config.user.password_0.note, note );
            strcpy( g_config.user.password_0.var, var );
        }
        if ( strcmp( name, "username_1" ) == 0 )// username_1 RTU用户					
        {
            strcpy( g_config.user.username_1.name, name );
            strcpy( g_config.user.username_1.note, note );
            strcpy( g_config.user.username_1.var, var );
        }
        if ( strcmp( name, "password_1" ) == 0 )
        {
            strcpy( g_config.user.password_1.name, name );
            strcpy( g_config.user.password_1.note, note );
            strcpy( g_config.user.password_1.var, var );
        }
        if ( strcmp( name, "username_2" ) == 0 )// username_2 普通用户
        {
            strcpy( g_config.user.username_2.name, name );
            strcpy( g_config.user.username_2.note, note );
            strcpy( g_config.user.username_2.var, var );
        }
        if ( strcmp( name, "password_2" ) == 0 )
        {
            strcpy( g_config.user.password_2.name, name );
            strcpy( g_config.user.password_2.note, note );
            strcpy( g_config.user.password_2.var, var );
        }
        if ( strcmp( name, "username_3" ) == 0 )// username_3 普通用户
        {
            strcpy( g_config.user.username_3.name, name );
            strcpy( g_config.user.username_3.note, note );
            strcpy( g_config.user.username_3.var, var );
        }
        if ( strcmp( name, "password_3" ) == 0 )
        {
            strcpy( g_config.user.password_3.name, name );
            strcpy( g_config.user.password_3.note, note );
            strcpy( g_config.user.password_3.var, var );
        }
    }
    else if ( g_config.config_index == CFG_video)//视频参数
    {
        if ( strcmp( name, "rtv_num" ) == 0 )//暂定只有2路视频
        {
            strcpy( g_config.video.rtv_num.name, name );
            strcpy( g_config.video.rtv_num.note, note );
            g_config.video.rtv_num.var = atoi( var );
        }
        if ( strcmp( name, "solution_x_1" ) == 0 )
        {
            strcpy( g_config.video.solution_x_1.name, name );
            strcpy( g_config.video.solution_x_1.note, note );
            g_config.video.solution_x_1.var = atoi( var );
        }
        if ( strcmp( name, "solution_y_1" ) == 0 )
        {
            strcpy( g_config.video.solution_y_1.name, name );
            strcpy( g_config.video.solution_y_1.note, note );
            g_config.video.solution_y_1.var = atoi( var );
        }
        if ( strcmp( name, "bright_1" ) == 0 )//亮度 : 0~255
        {
            strcpy( g_config.video.bright_1.name, name );
            strcpy( g_config.video.bright_1.note, note );
            g_config.video.bright_1.var = atoi( var );
        }
        if ( strcmp( name, "contrast_1" ) == 0 )//对比度: 0~255
        {
            strcpy( g_config.video.contrast_1.name, name );
            strcpy( g_config.video.contrast_1.note, note );
            g_config.video.contrast_1.var = atoi( var );
        }
        if ( strcmp( name, "frame_interval_1" ) == 0 )//传输帧间隔数,0为无间隔
        {
            strcpy( g_config.video.frame_interval_1.name, name );
            strcpy( g_config.video.frame_interval_1.note, note );
            g_config.video.frame_interval_1.var = atoi( var );
        }
        if ( strcmp( name, "speed_1" ) == 0 )//帧率
        {
            strcpy( g_config.video.speed_1.name, name );
            strcpy( g_config.video.speed_1.note, note );
            g_config.video.speed_1.var = atoi( var );
        }
        if ( strcmp( name, "cache_time_1" ) == 0 )//视频图片预缓存时间长度
        {
            strcpy( g_config.video.cache_time_1.name, name );
            strcpy( g_config.video.cache_time_1.note, note );
            g_config.video.cache_time_1.var = atoi( var );
        }
        if ( strcmp( name, "solution_x_2" ) == 0 )
        {
            strcpy( g_config.video.solution_x_2.name, name );
            strcpy( g_config.video.solution_x_2.note, note );
            g_config.video.solution_x_2.var = atoi( var );
        }
        if ( strcmp( name, "solution_y_2" ) == 0 )
        {
            strcpy( g_config.video.solution_y_2.name, name );
            strcpy( g_config.video.solution_y_2.note, note );
            g_config.video.solution_y_2.var = atoi( var );
        }
        if ( strcmp( name, "bright_2" ) == 0 )
        {
            strcpy( g_config.video.bright_2.name, name );
            strcpy( g_config.video.bright_2.note, note );
            g_config.video.bright_2.var = atoi( var );
        }
        if ( strcmp( name, "contrast_2" ) == 0 )
        {
            strcpy( g_config.video.contrast_2.name, name );
            strcpy( g_config.video.contrast_2.note, note );
            g_config.video.contrast_2.var = atoi( var );
        }
        if ( strcmp( name, "frame_interval_2" ) == 0 )
        {
            strcpy( g_config.video.frame_interval_2.name, name );
            strcpy( g_config.video.frame_interval_2.note, note );
            g_config.video.frame_interval_2.var = atoi( var );
        }
        if ( strcmp( name, "speed_2" ) == 0 )
        {
            strcpy( g_config.video.speed_2.name, name );
            strcpy( g_config.video.speed_2.note, note );
            g_config.video.speed_2.var = atoi( var );
        }
        if ( strcmp( name, "cache_time_2" ) == 0 )
        {
            strcpy( g_config.video.cache_time_2.name, name );
            strcpy( g_config.video.cache_time_2.note, note );
            g_config.video.cache_time_2.var = atoi( var );
        }
    }
    else if ( g_config.config_index == CFG_network)//网络参数
    {
        if ( strcmp( name, "ip_addr" ) == 0 )
        {
            strcpy( g_config.network.ip_addr.name, name );
            strcpy( g_config.network.ip_addr.note, note );
            strcpy( g_config.network.ip_addr.var, var );
        }
        if ( strcmp( name, "ip_mask" ) == 0 )
        {
            strcpy( g_config.network.ip_mask.name, name );
            strcpy( g_config.network.ip_mask.note, note );
            strcpy( g_config.network.ip_mask.var, var );
        }
        if ( strcmp( name, "ip_gateway" ) == 0 )
        {
            strcpy( g_config.network.ip_gateway.name, name );
            strcpy( g_config.network.ip_gateway.note, note );
            strcpy( g_config.network.ip_gateway.var, var );
        }
        if ( strcmp( name, "dns" ) == 0 )
        {
            strcpy( g_config.network.dns.name, name );
            strcpy( g_config.network.dns.note, note );
            strcpy( g_config.network.dns.var, var );
        }
        if ( strcmp( name, "mac_addr" ) == 0 )
        {
            strcpy( g_config.network.mac_addr.name, name );
            strcpy( g_config.network.mac_addr.note, note );
            strcpy( g_config.network.mac_addr.var, var );
        }
        if ( strcmp( name, "web_port" ) == 0 )//web服务器访问端口
        {
            strcpy( g_config.network.web_port.name, name );
            strcpy( g_config.network.web_port.note, note );
            g_config.network.web_port.var = atoi( var );
        }
        if ( strcmp( name, "socket_port" ) == 0 )//socket命令端口
        {
            strcpy( g_config.network.socket_port.name, name );
            strcpy( g_config.network.socket_port.note, note );
            g_config.network.socket_port.var = atoi( var );
        }
        if ( strcmp( name, "rtv_port" ) == 0 )//视频传送端口
        {
            strcpy( g_config.network.rtv_port.name, name );
            strcpy( g_config.network.rtv_port.note, note );
            g_config.network.rtv_port.var = atoi( var );
        }
        if ( strcmp( name, "alarm_remote_addr" ) == 0 )//远程地址，用于IPC主动发送告警
        {
            strcpy( g_config.network.alarm_remote_addr.name, name );
            strcpy( g_config.network.alarm_remote_addr.note, note );
            strcpy( g_config.network.alarm_remote_addr.var, var );
        }
        if ( strcmp( name, "alarm_remote_port" ) == 0 )//远程端口
        {
            strcpy( g_config.network.alarm_remote_port.name, name );
            strcpy( g_config.network.alarm_remote_port.note, note );
            g_config.network.alarm_remote_port.var = atoi( var );
        }
    }
    else if ( g_config.config_index == CFG_alert)//报警参数	
    {
        if ( strcmp( name, "alert_num" ) == 0 )//2路报警
        {
            strcpy( g_config.alert.alert_num.name, name );
            strcpy( g_config.alert.alert_num.note, note );
            g_config.alert.alert_num.var = atoi( var );
        }
        if ( strcmp( name, "capture_pic_enable_1" ) == 0 )//启用抓拍图片
        {
            strcpy( g_config.alert.capture_pic_enable_1.name, name );
            strcpy( g_config.alert.capture_pic_enable_1.note, note );
            g_config.alert.capture_pic_enable_1.var = atoi( var );
        }
        if ( strcmp( name, "capture_pic_num_1" ) == 0 )//图片抓拍数目
        {
            strcpy( g_config.alert.capture_pic_num_1.name, name );
            strcpy( g_config.alert.capture_pic_num_1.note, note );
            g_config.alert.capture_pic_num_1.var = atoi( var );
        }
        if ( strcmp( name, "capture_pic_interval_1" ) == 0 )//图片抓拍间隔, 后续删除
        {
            strcpy( g_config.alert.capture_pic_interval_1.name, name );
            strcpy( g_config.alert.capture_pic_interval_1.note, note );
            g_config.alert.capture_pic_interval_1.var = atoi( var );
        }
        if ( strcmp( name, "capture_video_enable_1" ) == 0 )//启用录像
        {
            strcpy( g_config.alert.capture_video_enable_1.name, name );
            strcpy( g_config.alert.capture_video_enable_1.note, note );
            g_config.alert.capture_video_enable_1.var = atoi( var );
        }
        if ( strcmp( name, "capture_video_last_time_1" ) == 0 )//录像持续时间
        {
            strcpy( g_config.alert.capture_video_last_time_1.name, name );
            strcpy( g_config.alert.capture_video_last_time_1.note, note );
            g_config.alert.capture_video_last_time_1.var = atoi( var );
        }
        if ( strcmp( name, "alarm_enable_1" ) == 0 )//启用警铃
        {
            strcpy( g_config.alert.alarm_enable_1.name, name );
            strcpy( g_config.alert.alarm_enable_1.note, note );
            g_config.alert.alarm_enable_1.var = atoi( var );
        }
        if ( strcmp( name, "alarm_delay_1" ) == 0 )//警铃延迟时间
        {
            strcpy( g_config.alert.alarm_delay_1.name, name );
            strcpy( g_config.alert.alarm_delay_1.note, note );
            g_config.alert.alarm_delay_1.var = atoi( var );
        }
        if ( strcmp( name, "alarm_last_time_1" ) == 0 )//警铃持续时间
        {
            strcpy( g_config.alert.alarm_last_time_1.name, name );
            strcpy( g_config.alert.alarm_last_time_1.note, note );
            g_config.alert.alarm_last_time_1.var = atoi( var );
        }
        if ( strcmp( name, "md_enable_1" ) == 0 )//启用移动侦测
        {
            strcpy( g_config.alert.md_enable_1.name, name );
            strcpy( g_config.alert.md_enable_1.note, note );
            g_config.alert.md_enable_1.var = atoi( var );
        }
        if ( strcmp( name, "md_sensitivity_1" ) == 0 )//侦测敏感度（30%）
        {
            strcpy( g_config.alert.md_sensitivity_1.name, name );
            strcpy( g_config.alert.md_sensitivity_1.note, note );
            g_config.alert.md_sensitivity_1.var = atoi( var );
        }
        if ( strcmp( name, "md_area_0_1" ) == 0 )//侦测区域（矩形）
        {
            strcpy( g_config.alert.md_area_0_1.name, name );
            strcpy( g_config.alert.md_area_0_1.note, note );
            strcpy( g_config.alert.md_area_0_1.var, var );
        }
        if ( strcmp( name, "md_area_1_1" ) == 0 )//侦测区域（矩形）
        {
            strcpy( g_config.alert.md_area_1_1.name, name );
            strcpy( g_config.alert.md_area_1_1.note, note );
            strcpy( g_config.alert.md_area_1_1.var, var );
        }
        if ( strcmp( name, "md_area_2_1" ) == 0 )//侦测区域（矩形）
        {
            strcpy( g_config.alert.md_area_2_1.name, name );
            strcpy( g_config.alert.md_area_2_1.note, note );
            strcpy( g_config.alert.md_area_2_1.var, var );
        }
        if ( strcmp( name, "md_area_3_1" ) == 0 )//侦测区域（矩形）
        {
            strcpy( g_config.alert.md_area_3_1.name, name );
            strcpy( g_config.alert.md_area_3_1.note, note );
            strcpy( g_config.alert.md_area_3_1.var, var );
        }
        if ( strcmp( name, "week_alert_plan_1" ) == 0 )
        {
            strcpy( g_config.alert.week_alert_plan_1.name, name );
            strcpy( g_config.alert.week_alert_plan_1.note, note );
            strcpy( g_config.alert.week_alert_plan_1.var, var );
        }
        if ( strcmp( name, "plan_cap_enalbe_1" ) == 0 )// 布防时间到时，是否启动录像
        {
            strcpy( g_config.alert.plan_cap_enalbe_1.name, name );
            strcpy( g_config.alert.plan_cap_enalbe_1.note, note );
            g_config.alert.plan_cap_enalbe_1.var = atoi( var );
        }
        if ( strcmp( name, "plan_cap_last_sec_1" ) == 0 )// 录像持续秒数，0代表录像时间持续到下一个整点
        {
            strcpy( g_config.alert.plan_cap_last_sec_1.name, name );
            strcpy( g_config.alert.plan_cap_last_sec_1.note, note );
            g_config.alert.plan_cap_last_sec_1.var = atoi( var );
        }
        if ( strcmp( name, "capture_pic_enable_2" ) == 0 )//启用抓拍图片
        {
            strcpy( g_config.alert.capture_pic_enable_2.name, name );
            strcpy( g_config.alert.capture_pic_enable_2.note, note );
            g_config.alert.capture_pic_enable_2.var = atoi( var );
        }
        if ( strcmp( name, "capture_pic_num_2" ) == 0 )//图片抓拍数目
        {
            strcpy( g_config.alert.capture_pic_num_2.name, name );
            strcpy( g_config.alert.capture_pic_num_2.note, note );
            g_config.alert.capture_pic_num_2.var = atoi( var );
        }
        if ( strcmp( name, "capture_pic_interval_2" ) == 0 )//图片抓拍间隔
        {
            strcpy( g_config.alert.capture_pic_interval_2.name, name );
            strcpy( g_config.alert.capture_pic_interval_2.note, note );
            g_config.alert.capture_pic_interval_2.var = atoi( var );
        }
        if ( strcmp( name, "capture_video_enable_2" ) == 0 )//启用录像
        {
            strcpy( g_config.alert.capture_video_enable_2.name, name );
            strcpy( g_config.alert.capture_video_enable_2.note, note );
            g_config.alert.capture_video_enable_2.var = atoi( var );
        }
        if ( strcmp( name, "capture_video_last_time_2" ) == 0 )//录像持续时间
        {
            strcpy( g_config.alert.capture_video_last_time_2.name, name );
            strcpy( g_config.alert.capture_video_last_time_2.note, note );
            g_config.alert.capture_video_last_time_2.var = atoi( var );
        }
        if ( strcmp( name, "alarm_enable_2" ) == 0 )//启用警铃
        {
            strcpy( g_config.alert.alarm_enable_2.name, name );
            strcpy( g_config.alert.alarm_enable_2.note, note );
            g_config.alert.alarm_enable_2.var = atoi( var );
        }
        if ( strcmp( name, "alarm_delay_2" ) == 0 )//警铃延迟时间
        {
            strcpy( g_config.alert.alarm_delay_2.name, name );
            strcpy( g_config.alert.alarm_delay_2.note, note );
            g_config.alert.alarm_delay_2.var = atoi( var );
        }
        if ( strcmp( name, "alarm_last_time_2" ) == 0 )//警铃持续时间
        {
            strcpy( g_config.alert.alarm_last_time_2.name, name );
            strcpy( g_config.alert.alarm_last_time_2.note, note );
            g_config.alert.alarm_last_time_2.var = atoi( var );
        }
        if ( strcmp( name, "md_enable_2" ) == 0 )//启用移动侦测
        {
            strcpy( g_config.alert.md_enable_2.name, name );
            strcpy( g_config.alert.md_enable_2.note, note );
            g_config.alert.md_enable_2.var = atoi( var );
        }
        if ( strcmp( name, "md_sensitivity_2" ) == 0 )//侦测敏感度（30%）
        {
            strcpy( g_config.alert.md_sensitivity_2.name, name );
            strcpy( g_config.alert.md_sensitivity_2.note, note );
            g_config.alert.md_sensitivity_2.var = atoi( var );
        }
        if ( strcmp( name, "md_area_0_2" ) == 0 )//侦测区域（矩形）
        {
            strcpy( g_config.alert.md_area_0_2.name, name );
            strcpy( g_config.alert.md_area_0_2.note, note );
            strcpy( g_config.alert.md_area_0_2.var, var );
        }
        if ( strcmp( name, "md_area_1_2" ) == 0 )//侦测区域（矩形）
        {
            strcpy( g_config.alert.md_area_1_2.name, name );
            strcpy( g_config.alert.md_area_1_2.note, note );
            strcpy( g_config.alert.md_area_1_2.var, var );
        }
        if ( strcmp( name, "md_area_2_2" ) == 0 )//侦测区域（矩形）
        {
            strcpy( g_config.alert.md_area_2_2.name, name );
            strcpy( g_config.alert.md_area_2_2.note, note );
            strcpy( g_config.alert.md_area_2_2.var, var );
        }
        if ( strcmp( name, "md_area_3_2" ) == 0 )//侦测区域（矩形）
        {
            strcpy( g_config.alert.md_area_3_2.name, name );
            strcpy( g_config.alert.md_area_3_2.note, note );
            strcpy( g_config.alert.md_area_3_2.var, var );
        }
        if ( strcmp( name, "week_alert_plan_2" ) == 0 )
        {
            strcpy( g_config.alert.week_alert_plan_2.name, name );
            strcpy( g_config.alert.week_alert_plan_2.note, note );
            strcpy( g_config.alert.week_alert_plan_2.var, var );
        }
        if ( strcmp( name, "plan_cap_enalbe_2" ) == 0 )// 布防时间到时，是否启动录像
        {
            strcpy( g_config.alert.plan_cap_enalbe_2.name, name );
            strcpy( g_config.alert.plan_cap_enalbe_2.note, note );
            g_config.alert.plan_cap_enalbe_2.var = atoi( var );
        }
        if ( strcmp( name, "plan_cap_last_sec_2" ) == 0 )// 录像持续秒数，0代表录像时间持续到下一个整点
        {
            strcpy( g_config.alert.plan_cap_last_sec_2.name, name );
            strcpy( g_config.alert.plan_cap_last_sec_2.note, note );
            g_config.alert.plan_cap_last_sec_2.var = atoi( var );
        }
    }
    else if ( g_config.config_index == CFG_store)//存储参数	
    {
        if ( strcmp( name, "sd_status" ) == 0 )//状态，0：未插入，1：已插入
        {
            strcpy( g_config.store.sd_status.name, name );
            strcpy( g_config.store.sd_status.note, note );
            g_config.store.sd_status.var = atoi( var );
        }
        if ( strcmp( name, "sd_total_size" ) == 0 )//SD卡总容量
        {
            strcpy( g_config.store.sd_total_size.name, name );
            strcpy( g_config.store.sd_total_size.note, note );
            g_config.store.sd_total_size.var = atoi( var );
        }
        if ( strcmp( name, "sd_used_size" ) == 0 )//SD卡已使用容量，两个参数在此无意义，主要是封装在一个结构体内，sd_store_enable
        {
            strcpy( g_config.store.sd_used_size.name, name );
            strcpy( g_config.store.sd_used_size.note, note );
            g_config.store.sd_used_size.var = atoi( var );
        }
        if ( strcmp( name, "sd_store_enable" ) == 0 )//启用SD卡存储
        {
            strcpy( g_config.store.sd_store_enable.name, name );
            strcpy( g_config.store.sd_store_enable.note, note );
            g_config.store.sd_store_enable.var = atoi( var );
        }
        if ( strcmp( name, "auto_cover_older" ) == 0 )//自动覆盖旧文件
        {
            strcpy( g_config.store.auto_cover_older.name, name );
            strcpy( g_config.store.auto_cover_older.note, note );
            g_config.store.auto_cover_older.var = atoi( var );
        }
        if ( strcmp( name, "percent_alarm" ) == 0 )// 执行告警百分比，磁盘剩余空间百分比<=percent_alarm,则进行告警瞤ercent_del
        {
            strcpy( g_config.store.percent_alarm.name, name );
            strcpy( g_config.store.percent_alarm.note, note );
            g_config.store.percent_alarm.var = atoi( var );
        }
        if ( strcmp( name, "percent_del" ) == 0 )// 执行删除百分比，磁盘剩余空间百分比<=percent_del,则进行删除操譻ys
        {
            strcpy( g_config.store.percent_del.name, name );
            strcpy( g_config.store.percent_del.note, note );
            g_config.store.percent_del.var = atoi( var );
        }
    }
    else if ( g_config.config_index == CFG_sys)//系统设置	                        	
    {
        if ( strcmp( name, "app_version" ) == 0 )
        {
            strcpy( g_config.sys.app_version.name, name );
            strcpy( g_config.sys.app_version.note, note );
            strcpy( g_config.sys.app_version.var, var );
        }
        if ( strcmp( name, "app_time" ) == 0 )
        {
            strcpy( g_config.sys.app_time.name, name );
            strcpy( g_config.sys.app_time.note, note );
            strcpy( g_config.sys.app_time.var, var );
        }
    }
    else if ( g_config.config_index == CFG_rtv_start)// 实时视频传输请求
    {
        if ( strcmp( name, "channel" ) == 0 )// 视频信道 0, 1
        {
            strcpy( g_config.rtv_start.channel.name, name );
            strcpy( g_config.rtv_start.channel.note, note );
            g_config.rtv_start.channel.var = atoi( var );
        }
    }
    else if ( g_config.config_index == CFG_htv_start)// 录像启动请求
    {
        if ( strcmp( name, "channel" ) == 0 )// 视频信道 0, 1	
        {
            strcpy( g_config.htv_start.channel.name, name );
            strcpy( g_config.htv_start.channel.note, note );
            g_config.htv_start.channel.var = atoi( var );
        }
    }
    else if ( g_config.config_index == CFG_htv_end)// 录像停止请求
    {
        if ( strcmp( name, "channel" ) == 0 )// 视频信道 0, 1
        {
            strcpy( g_config.htv_end.channel.name, name );
            strcpy( g_config.htv_end.channel.note, note );
            g_config.htv_end.channel.var = atoi( var );
        }
    }
    else if ( g_config.config_index == CFG_pic_start)// 图片抓拍启动请求
    {
        if ( strcmp( name, "channel" ) == 0 )// 视频信道 0, 1
        {
            strcpy( g_config.pic_start.channel.name, name );
            strcpy( g_config.pic_start.channel.note, note );
            g_config.pic_start.channel.var = atoi( var );
        }
        if ( strcmp( name, "num" ) == 0 )// 抓拍张数
        {
            strcpy( g_config.pic_start.num.name, name );
            strcpy( g_config.pic_start.num.note, note );
            g_config.pic_start.num.var = atoi( var );
        }
    }
    else if ( g_config.config_index == CFG_ptz_control)// 云台控制请求
    {
        if ( strcmp( name, "channel" ) == 0 )// 视频信道 0, 1
        {
            strcpy( g_config.ptz_control.channel.name, name );
            strcpy( g_config.ptz_control.channel.note, note );
            g_config.ptz_control.channel.var = atoi( var );
        }
        if ( strcmp( name, "left" ) == 0 )// 向左转动  0：无操作 1：操作
        {
            strcpy( g_config.ptz_control.left.name, name );
            strcpy( g_config.ptz_control.left.note, note );
            g_config.ptz_control.left.var = atoi( var );
        }
        if ( strcmp( name, "right" ) == 0 )// 向右转动  0：无操作 1：操作
        {
            strcpy( g_config.ptz_control.right.name, name );
            strcpy( g_config.ptz_control.right.note, note );
            g_config.ptz_control.right.var = atoi( var );
        }
        if ( strcmp( name, "up" ) == 0 )// 向上转动  0：无操作 1：操作
        {
            strcpy( g_config.ptz_control.up.name, name );
            strcpy( g_config.ptz_control.up.note, note );
            g_config.ptz_control.up.var = atoi( var );
        }
        if ( strcmp( name, "down" ) == 0 )// 向下转动  0：无操作 1：操作
        {
            strcpy( g_config.ptz_control.down.name, name );
            strcpy( g_config.ptz_control.down.note, note );
            g_config.ptz_control.down.var = atoi( var );
        }
    }
    else if ( g_config.config_index == CFG_sys_quit)// IPC退出请求
    {
        if ( strcmp( name, "flag" ) == 0 )// 0：IPC不退出，1：IPC退出
        {
            strcpy( g_config.sys_quit.flag.name, name );
            strcpy( g_config.sys_quit.flag.note, note );
            g_config.sys_quit.flag.var = atoi( var );
        }
    }
    else if ( g_config.config_index == CFG_log)// 日志获取
    {
        if ( strcmp( name, "flag" ) == 0 )// 0: 不获取日志, 1:获取日志
        {
            strcpy( g_config.log.flag.name, name );
            strcpy( g_config.log.flag.note, note );
            g_config.log.flag.var = atoi( var );
        }
    }
    else if ( g_config.config_index == CFG_usb_remove)
    {
        if ( strcmp( name, "channel" ) == 0 )
        {
            strcpy( g_config.usb_remove.channel.name, name );
            strcpy( g_config.usb_remove.channel.note, note );
            g_config.usb_remove.channel.var = atoi( var );
        }
    }
    else if ( g_config.config_index == CFG_hb)// 心跳
    {
        if ( strcmp( name, "flag" ) == 0 )
        {
            strcpy( g_config.hb.flag.name, name );
            strcpy( g_config.hb.flag.note, note );
            g_config.hb.flag.var = atoi( var );
        }
    }
    else if ( g_config.config_index == CFG_def_config)// 恢复出厂配置
    {
        if ( strcmp( name, "flag" ) == 0 )
        {
            strcpy( g_config.def_config.flag.name, name );
            strcpy( g_config.def_config.flag.note, note );
            g_config.def_config.flag.var = atoi( var );
        }
    }
    else if ( g_config.config_index == CFG_md_report)
    {
        if ( strcmp( name, "md_area_0_0" ) == 0 )// 0路视频第0号区域是否有移动 0：没有 1：有
        {
            strcpy( g_config.md_report.md_area_0_0.name, name );
            strcpy( g_config.md_report.md_area_0_0.note, note );
            g_config.md_report.md_area_0_0.var = atoi( var );
        }
        if ( strcmp( name, "md_area_0_1" ) == 0 )
        {
            strcpy( g_config.md_report.md_area_0_1.name, name );
            strcpy( g_config.md_report.md_area_0_1.note, note );
            g_config.md_report.md_area_0_1.var = atoi( var );
        }
        if ( strcmp( name, "md_area_0_2" ) == 0 )
        {
            strcpy( g_config.md_report.md_area_0_2.name, name );
            strcpy( g_config.md_report.md_area_0_2.note, note );
            g_config.md_report.md_area_0_2.var = atoi( var );
        }
        if ( strcmp( name, "md_area_0_3" ) == 0 )
        {
            strcpy( g_config.md_report.md_area_0_3.name, name );
            strcpy( g_config.md_report.md_area_0_3.note, note );
            g_config.md_report.md_area_0_3.var = atoi( var );
        }
        if ( strcmp( name, "md_area_1_0" ) == 0 )
        {
            strcpy( g_config.md_report.md_area_1_0.name, name );
            strcpy( g_config.md_report.md_area_1_0.note, note );
            g_config.md_report.md_area_1_0.var = atoi( var );
        }
        if ( strcmp( name, "md_area_1_1" ) == 0 )
        {
            strcpy( g_config.md_report.md_area_1_1.name, name );
            strcpy( g_config.md_report.md_area_1_1.note, note );
            g_config.md_report.md_area_1_1.var = atoi( var );
        }
        if ( strcmp( name, "md_area_1_2" ) == 0 )
        {
            strcpy( g_config.md_report.md_area_1_2.name, name );
            strcpy( g_config.md_report.md_area_1_2.note, note );
            g_config.md_report.md_area_1_2.var = atoi( var );
        }
        if ( strcmp( name, "md_area_1_3" ) == 0 )
        {
            strcpy( g_config.md_report.md_area_1_3.name, name );
            strcpy( g_config.md_report.md_area_1_3.note, note );
            g_config.md_report.md_area_1_3.var = atoi( var );
        }
    }
    else if ( g_config.config_index == CFG_alarm_disk)// 参数都由存储参数全局变量提供
    {
        if ( strcmp( name, "flag" ) == 0 )
        {
            strcpy( g_config.alarm_disk.flag.name, name );
            strcpy( g_config.alarm_disk.flag.note, note );
            g_config.alarm_disk.flag.var = atoi( var );
        }
    }
    else if ( g_config.config_index == CFG_time_syn)// 时间同步
    {
        if ( strcmp( name, "time" ) == 0 )// 更新系统的日期，格式如下: 2008-10-12 13:14:34
        {
            strcpy( g_config.time_syn.time.name, name );
            strcpy( g_config.time_syn.time.note, note );
            strcpy( g_config.time_syn.time.var, var );
        }
    }
    else if ( g_config.config_index == CFG_alarm_error)// IPC向RTU上报严重错误消息，如录像保存时的open失败
    {
        if ( strcmp( name, "alarm_error_id" ) == 0 )// 告警错误id
        {
            strcpy( g_config.alarm_error.alarm_error_id.name, name );
            strcpy( g_config.alarm_error.alarm_error_id.note, note );
            g_config.alarm_error.alarm_error_id.var = atoi( var );
        }
        if ( strcmp( name, "alarm_error_name" ) == 0 )
        {
            strcpy( g_config.alarm_error.alarm_error_name.name, name );
            strcpy( g_config.alarm_error.alarm_error_name.note, note );
            strcpy( g_config.alarm_error.alarm_error_name.var, var );
        }
    }
    else if ( g_config.config_index == CFG_process_info)// 获取ipc进程信息
    {
        if ( strcmp( name, "flag" ) == 0 )
        {
            strcpy( g_config.process_info.flag.name, name );
            strcpy( g_config.process_info.flag.note, note );
            g_config.process_info.flag.var = atoi( var );
        }
    }
    else if ( g_config.config_index == CFG_end)
    {
        if ( strcmp( name, "flag" ) == 0 )// 结束标记
        {
            strcpy( g_config.end.flag.name, name );
            strcpy( g_config.end.flag.note, note );
            g_config.end.flag.var = atoi( var );
        }
    }
}

