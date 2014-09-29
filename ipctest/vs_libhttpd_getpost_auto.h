    //[login] web登录
    if( 0 == strcmp( cmd, "login_pgh" ) )
    {
        char ctemp[16];
        GetTypeValue( hc->http_context, "login_pgh", ctemp );
        g_config.login.pgh.var  = atoi( ctemp ); // 取得表单控件的值
        //返回一个页面，对于同一页面的内容，应该只需有一个位置载入吧，先注释掉，想让哪个做为主要标志载入，再打开吧
        //sendReflashToConn( hc, "../web_page/setup/timer.html"); // 返回一个页面
    }
    //[user]用户信息  
    else if( 0 == strcmp( cmd, "user_user_num" ) )
    {
        char ctemp[16];
        GetTypeValue( hc->http_context, "user_user_num", ctemp );
        g_config.user.user_num.var  = atoi( ctemp );
    }
    else if( 0 == strcmp( cmd, "user_username_0" ) )// username_0系统管理员
    {
        GetTypeValue( hc->http_context, "user_username_0", g_config.user.username_0.var );
        strdecode( g_config.user.username_0.var, g_config.user.username_0.var );
    }
    else if( 0 == strcmp( cmd, "user_password_0" ) )
    {
        GetTypeValue( hc->http_context, "user_password_0", g_config.user.password_0.var );
        strdecode( g_config.user.password_0.var, g_config.user.password_0.var );
    }
    else if( 0 == strcmp( cmd, "user_username_1" ) )// username_1 RTU用户					
    {
        GetTypeValue( hc->http_context, "user_username_1", g_config.user.username_1.var );
        strdecode( g_config.user.username_1.var, g_config.user.username_1.var );
    }
    else if( 0 == strcmp( cmd, "user_password_1" ) )
    {
        GetTypeValue( hc->http_context, "user_password_1", g_config.user.password_1.var );
        strdecode( g_config.user.password_1.var, g_config.user.password_1.var );
    }
    else if( 0 == strcmp( cmd, "user_username_2" ) )// username_2 普通用户
    {
        GetTypeValue( hc->http_context, "user_username_2", g_config.user.username_2.var );
        strdecode( g_config.user.username_2.var, g_config.user.username_2.var );
    }
    else if( 0 == strcmp( cmd, "user_password_2" ) )
    {
        GetTypeValue( hc->http_context, "user_password_2", g_config.user.password_2.var );
        strdecode( g_config.user.password_2.var, g_config.user.password_2.var );
    }
    else if( 0 == strcmp( cmd, "user_username_3" ) )// username_3 普通用户
    {
        GetTypeValue( hc->http_context, "user_username_3", g_config.user.username_3.var );
        strdecode( g_config.user.username_3.var, g_config.user.username_3.var );
    }
    else if( 0 == strcmp( cmd, "user_password_3" ) )
    {
        GetTypeValue( hc->http_context, "user_password_3", g_config.user.password_3.var );
        strdecode( g_config.user.password_3.var, g_config.user.password_3.var );
    }
    //[video]视频参数
    else if( 0 == strcmp( cmd, "video_rtv_num" ) )//暂定只有2路视频
    {
        char ctemp[16];
        GetTypeValue( hc->http_context, "video_rtv_num", ctemp );
        g_config.video.rtv_num.var  = atoi( ctemp );
    }
    else if( 0 == strcmp( cmd, "video_solution_x_1" ) )
    {
        char ctemp[16];
        GetTypeValue( hc->http_context, "video_solution_x_1", ctemp );
        g_config.video.solution_x_1.var  = atoi( ctemp );
    }
    else if( 0 == strcmp( cmd, "video_solution_y_1" ) )
    {
        char ctemp[16];
        GetTypeValue( hc->http_context, "video_solution_y_1", ctemp );
        g_config.video.solution_y_1.var  = atoi( ctemp );
    }
    else if( 0 == strcmp( cmd, "video_bright_1" ) )//亮度 : 0~255
    {
        char ctemp[16];
        GetTypeValue( hc->http_context, "video_bright_1", ctemp );
        g_config.video.bright_1.var  = atoi( ctemp );
    }
    else if( 0 == strcmp( cmd, "video_contrast_1" ) )//对比度: 0~255
    {
        char ctemp[16];
        GetTypeValue( hc->http_context, "video_contrast_1", ctemp );
        g_config.video.contrast_1.var  = atoi( ctemp );
    }
    else if( 0 == strcmp( cmd, "video_frame_interval_1" ) )//传输帧间隔数,0为无间隔
    {
        char ctemp[16];
        GetTypeValue( hc->http_context, "video_frame_interval_1", ctemp );
        g_config.video.frame_interval_1.var  = atoi( ctemp );
    }
    else if( 0 == strcmp( cmd, "video_speed_1" ) )//帧率
    {
        char ctemp[16];
        GetTypeValue( hc->http_context, "video_speed_1", ctemp );
        g_config.video.speed_1.var  = atoi( ctemp );
    }
    else if( 0 == strcmp( cmd, "video_cache_time_1" ) )//视频图片预缓存时间长度
    {
        char ctemp[16];
        GetTypeValue( hc->http_context, "video_cache_time_1", ctemp );
        g_config.video.cache_time_1.var  = atoi( ctemp );
    }
    else if( 0 == strcmp( cmd, "video_solution_x_2" ) )
    {
        char ctemp[16];
        GetTypeValue( hc->http_context, "video_solution_x_2", ctemp );
        g_config.video.solution_x_2.var  = atoi( ctemp );
    }
    else if( 0 == strcmp( cmd, "video_solution_y_2" ) )
    {
        char ctemp[16];
        GetTypeValue( hc->http_context, "video_solution_y_2", ctemp );
        g_config.video.solution_y_2.var  = atoi( ctemp );
    }
    else if( 0 == strcmp( cmd, "video_bright_2" ) )
    {
        char ctemp[16];
        GetTypeValue( hc->http_context, "video_bright_2", ctemp );
        g_config.video.bright_2.var  = atoi( ctemp );
    }
    else if( 0 == strcmp( cmd, "video_contrast_2" ) )
    {
        char ctemp[16];
        GetTypeValue( hc->http_context, "video_contrast_2", ctemp );
        g_config.video.contrast_2.var  = atoi( ctemp );
    }
    else if( 0 == strcmp( cmd, "video_frame_interval_2" ) )
    {
        char ctemp[16];
        GetTypeValue( hc->http_context, "video_frame_interval_2", ctemp );
        g_config.video.frame_interval_2.var  = atoi( ctemp );
    }
    else if( 0 == strcmp( cmd, "video_speed_2" ) )
    {
        char ctemp[16];
        GetTypeValue( hc->http_context, "video_speed_2", ctemp );
        g_config.video.speed_2.var  = atoi( ctemp );
    }
    else if( 0 == strcmp( cmd, "video_cache_time_2" ) )
    {
        char ctemp[16];
        GetTypeValue( hc->http_context, "video_cache_time_2", ctemp );
        g_config.video.cache_time_2.var  = atoi( ctemp );
    }
    //[network]网络参数
    else if( 0 == strcmp( cmd, "network_ip_addr" ) )
    {
        GetTypeValue( hc->http_context, "network_ip_addr", g_config.network.ip_addr.var );
        strdecode( g_config.network.ip_addr.var, g_config.network.ip_addr.var );
    }
    else if( 0 == strcmp( cmd, "network_ip_mask" ) )
    {
        GetTypeValue( hc->http_context, "network_ip_mask", g_config.network.ip_mask.var );
        strdecode( g_config.network.ip_mask.var, g_config.network.ip_mask.var );
    }
    else if( 0 == strcmp( cmd, "network_ip_gateway" ) )
    {
        GetTypeValue( hc->http_context, "network_ip_gateway", g_config.network.ip_gateway.var );
        strdecode( g_config.network.ip_gateway.var, g_config.network.ip_gateway.var );
    }
    else if( 0 == strcmp( cmd, "network_dns" ) )
    {
        GetTypeValue( hc->http_context, "network_dns", g_config.network.dns.var );
        strdecode( g_config.network.dns.var, g_config.network.dns.var );
    }
    else if( 0 == strcmp( cmd, "network_mac_addr" ) )
    {
        GetTypeValue( hc->http_context, "network_mac_addr", g_config.network.mac_addr.var );
        strdecode( g_config.network.mac_addr.var, g_config.network.mac_addr.var );
    }
    else if( 0 == strcmp( cmd, "network_web_port" ) )//web服务器访问端口
    {
        char ctemp[16];
        GetTypeValue( hc->http_context, "network_web_port", ctemp );
        g_config.network.web_port.var  = atoi( ctemp );
    }
    else if( 0 == strcmp( cmd, "network_socket_port" ) )//socket命令端口
    {
        char ctemp[16];
        GetTypeValue( hc->http_context, "network_socket_port", ctemp );
        g_config.network.socket_port.var  = atoi( ctemp );
    }
    else if( 0 == strcmp( cmd, "network_rtv_port" ) )//视频传送端口
    {
        char ctemp[16];
        GetTypeValue( hc->http_context, "network_rtv_port", ctemp );
        g_config.network.rtv_port.var  = atoi( ctemp );
    }
    else if( 0 == strcmp( cmd, "network_alarm_remote_addr" ) )//远程地址，用于IPC主动发送告警
    {
        GetTypeValue( hc->http_context, "network_alarm_remote_addr", g_config.network.alarm_remote_addr.var );
        strdecode( g_config.network.alarm_remote_addr.var, g_config.network.alarm_remote_addr.var );
    }
    else if( 0 == strcmp( cmd, "network_alarm_remote_port" ) )//远程端口
    {
        char ctemp[16];
        GetTypeValue( hc->http_context, "network_alarm_remote_port", ctemp );
        g_config.network.alarm_remote_port.var  = atoi( ctemp );
    }
    //[alert]报警参数	
    else if( 0 == strcmp( cmd, "alert_alert_num" ) )//2路报警
    {
        char ctemp[16];
        GetTypeValue( hc->http_context, "alert_alert_num", ctemp );
        g_config.alert.alert_num.var  = atoi( ctemp );
    }
    else if( 0 == strcmp( cmd, "alert_capture_pic_enable_1" ) )//启用抓拍图片
    {
        char ctemp[16];
        GetTypeValue( hc->http_context, "alert_capture_pic_enable_1", ctemp );
        g_config.alert.capture_pic_enable_1.var  = atoi( ctemp );
    }
    else if( 0 == strcmp( cmd, "alert_capture_pic_num_1" ) )//图片抓拍数目
    {
        char ctemp[16];
        GetTypeValue( hc->http_context, "alert_capture_pic_num_1", ctemp );
        g_config.alert.capture_pic_num_1.var  = atoi( ctemp );
    }
    else if( 0 == strcmp( cmd, "alert_capture_pic_interval_1" ) )//图片抓拍间隔, 后续删除
    {
        char ctemp[16];
        GetTypeValue( hc->http_context, "alert_capture_pic_interval_1", ctemp );
        g_config.alert.capture_pic_interval_1.var  = atoi( ctemp );
    }
    else if( 0 == strcmp( cmd, "alert_capture_video_enable_1" ) )//启用录像
    {
        char ctemp[16];
        GetTypeValue( hc->http_context, "alert_capture_video_enable_1", ctemp );
        g_config.alert.capture_video_enable_1.var  = atoi( ctemp );
    }
    else if( 0 == strcmp( cmd, "alert_capture_video_last_time_1" ) )//录像持续时间
    {
        char ctemp[16];
        GetTypeValue( hc->http_context, "alert_capture_video_last_time_1", ctemp );
        g_config.alert.capture_video_last_time_1.var  = atoi( ctemp );
    }
    else if( 0 == strcmp( cmd, "alert_alarm_enable_1" ) )//启用警铃
    {
        char ctemp[16];
        GetTypeValue( hc->http_context, "alert_alarm_enable_1", ctemp );
        g_config.alert.alarm_enable_1.var  = atoi( ctemp );
    }
    else if( 0 == strcmp( cmd, "alert_alarm_delay_1" ) )//警铃延迟时间
    {
        char ctemp[16];
        GetTypeValue( hc->http_context, "alert_alarm_delay_1", ctemp );
        g_config.alert.alarm_delay_1.var  = atoi( ctemp );
    }
    else if( 0 == strcmp( cmd, "alert_alarm_last_time_1" ) )//警铃持续时间
    {
        char ctemp[16];
        GetTypeValue( hc->http_context, "alert_alarm_last_time_1", ctemp );
        g_config.alert.alarm_last_time_1.var  = atoi( ctemp );
    }
    else if( 0 == strcmp( cmd, "alert_md_enable_1" ) )//启用移动侦测
    {
        char ctemp[16];
        GetTypeValue( hc->http_context, "alert_md_enable_1", ctemp );
        g_config.alert.md_enable_1.var  = atoi( ctemp );
    }
    else if( 0 == strcmp( cmd, "alert_md_sensitivity_1" ) )//侦测敏感度（30%）
    {
        char ctemp[16];
        GetTypeValue( hc->http_context, "alert_md_sensitivity_1", ctemp );
        g_config.alert.md_sensitivity_1.var  = atoi( ctemp );
    }
    else if( 0 == strcmp( cmd, "alert_md_area_0_1" ) )//侦测区域（矩形）
    {
        GetTypeValue( hc->http_context, "alert_md_area_0_1", g_config.alert.md_area_0_1.var );
        strdecode( g_config.alert.md_area_0_1.var, g_config.alert.md_area_0_1.var );
    }
    else if( 0 == strcmp( cmd, "alert_md_area_1_1" ) )//侦测区域（矩形）
    {
        GetTypeValue( hc->http_context, "alert_md_area_1_1", g_config.alert.md_area_1_1.var );
        strdecode( g_config.alert.md_area_1_1.var, g_config.alert.md_area_1_1.var );
    }
    else if( 0 == strcmp( cmd, "alert_md_area_2_1" ) )//侦测区域（矩形）
    {
        GetTypeValue( hc->http_context, "alert_md_area_2_1", g_config.alert.md_area_2_1.var );
        strdecode( g_config.alert.md_area_2_1.var, g_config.alert.md_area_2_1.var );
    }
    else if( 0 == strcmp( cmd, "alert_md_area_3_1" ) )//侦测区域（矩形）
    {
        GetTypeValue( hc->http_context, "alert_md_area_3_1", g_config.alert.md_area_3_1.var );
        strdecode( g_config.alert.md_area_3_1.var, g_config.alert.md_area_3_1.var );
    }
    else if( 0 == strcmp( cmd, "alert_week_alert_plan_1" ) )
    {
        GetTypeValue( hc->http_context, "alert_week_alert_plan_1", g_config.alert.week_alert_plan_1.var );
        strdecode( g_config.alert.week_alert_plan_1.var, g_config.alert.week_alert_plan_1.var );
    }
    else if( 0 == strcmp( cmd, "alert_plan_cap_enalbe_1" ) )// 布防时间到时，是否启动录像
    {
        char ctemp[16];
        GetTypeValue( hc->http_context, "alert_plan_cap_enalbe_1", ctemp );
        g_config.alert.plan_cap_enalbe_1.var  = atoi( ctemp );
    }
    else if( 0 == strcmp( cmd, "alert_plan_cap_last_sec_1" ) )// 录像持续秒数，0代表录像时间持续到下一个整点
    {
        char ctemp[16];
        GetTypeValue( hc->http_context, "alert_plan_cap_last_sec_1", ctemp );
        g_config.alert.plan_cap_last_sec_1.var  = atoi( ctemp );
    }
    else if( 0 == strcmp( cmd, "alert_capture_pic_enable_2" ) )//启用抓拍图片
    {
        char ctemp[16];
        GetTypeValue( hc->http_context, "alert_capture_pic_enable_2", ctemp );
        g_config.alert.capture_pic_enable_2.var  = atoi( ctemp );
    }
    else if( 0 == strcmp( cmd, "alert_capture_pic_num_2" ) )//图片抓拍数目
    {
        char ctemp[16];
        GetTypeValue( hc->http_context, "alert_capture_pic_num_2", ctemp );
        g_config.alert.capture_pic_num_2.var  = atoi( ctemp );
    }
    else if( 0 == strcmp( cmd, "alert_capture_pic_interval_2" ) )//图片抓拍间隔
    {
        char ctemp[16];
        GetTypeValue( hc->http_context, "alert_capture_pic_interval_2", ctemp );
        g_config.alert.capture_pic_interval_2.var  = atoi( ctemp );
    }
    else if( 0 == strcmp( cmd, "alert_capture_video_enable_2" ) )//启用录像
    {
        char ctemp[16];
        GetTypeValue( hc->http_context, "alert_capture_video_enable_2", ctemp );
        g_config.alert.capture_video_enable_2.var  = atoi( ctemp );
    }
    else if( 0 == strcmp( cmd, "alert_capture_video_last_time_2" ) )//录像持续时间
    {
        char ctemp[16];
        GetTypeValue( hc->http_context, "alert_capture_video_last_time_2", ctemp );
        g_config.alert.capture_video_last_time_2.var  = atoi( ctemp );
    }
    else if( 0 == strcmp( cmd, "alert_alarm_enable_2" ) )//启用警铃
    {
        char ctemp[16];
        GetTypeValue( hc->http_context, "alert_alarm_enable_2", ctemp );
        g_config.alert.alarm_enable_2.var  = atoi( ctemp );
    }
    else if( 0 == strcmp( cmd, "alert_alarm_delay_2" ) )//警铃延迟时间
    {
        char ctemp[16];
        GetTypeValue( hc->http_context, "alert_alarm_delay_2", ctemp );
        g_config.alert.alarm_delay_2.var  = atoi( ctemp );
    }
    else if( 0 == strcmp( cmd, "alert_alarm_last_time_2" ) )//警铃持续时间
    {
        char ctemp[16];
        GetTypeValue( hc->http_context, "alert_alarm_last_time_2", ctemp );
        g_config.alert.alarm_last_time_2.var  = atoi( ctemp );
    }
    else if( 0 == strcmp( cmd, "alert_md_enable_2" ) )//启用移动侦测
    {
        char ctemp[16];
        GetTypeValue( hc->http_context, "alert_md_enable_2", ctemp );
        g_config.alert.md_enable_2.var  = atoi( ctemp );
    }
    else if( 0 == strcmp( cmd, "alert_md_sensitivity_2" ) )//侦测敏感度（30%）
    {
        char ctemp[16];
        GetTypeValue( hc->http_context, "alert_md_sensitivity_2", ctemp );
        g_config.alert.md_sensitivity_2.var  = atoi( ctemp );
    }
    else if( 0 == strcmp( cmd, "alert_md_area_0_2" ) )//侦测区域（矩形）
    {
        GetTypeValue( hc->http_context, "alert_md_area_0_2", g_config.alert.md_area_0_2.var );
        strdecode( g_config.alert.md_area_0_2.var, g_config.alert.md_area_0_2.var );
    }
    else if( 0 == strcmp( cmd, "alert_md_area_1_2" ) )//侦测区域（矩形）
    {
        GetTypeValue( hc->http_context, "alert_md_area_1_2", g_config.alert.md_area_1_2.var );
        strdecode( g_config.alert.md_area_1_2.var, g_config.alert.md_area_1_2.var );
    }
    else if( 0 == strcmp( cmd, "alert_md_area_2_2" ) )//侦测区域（矩形）
    {
        GetTypeValue( hc->http_context, "alert_md_area_2_2", g_config.alert.md_area_2_2.var );
        strdecode( g_config.alert.md_area_2_2.var, g_config.alert.md_area_2_2.var );
    }
    else if( 0 == strcmp( cmd, "alert_md_area_3_2" ) )//侦测区域（矩形）
    {
        GetTypeValue( hc->http_context, "alert_md_area_3_2", g_config.alert.md_area_3_2.var );
        strdecode( g_config.alert.md_area_3_2.var, g_config.alert.md_area_3_2.var );
    }
    else if( 0 == strcmp( cmd, "alert_week_alert_plan_2" ) )
    {
        GetTypeValue( hc->http_context, "alert_week_alert_plan_2", g_config.alert.week_alert_plan_2.var );
        strdecode( g_config.alert.week_alert_plan_2.var, g_config.alert.week_alert_plan_2.var );
    }
    else if( 0 == strcmp( cmd, "alert_plan_cap_enalbe_2" ) )// 布防时间到时，是否启动录像
    {
        char ctemp[16];
        GetTypeValue( hc->http_context, "alert_plan_cap_enalbe_2", ctemp );
        g_config.alert.plan_cap_enalbe_2.var  = atoi( ctemp );
    }
    else if( 0 == strcmp( cmd, "alert_plan_cap_last_sec_2" ) )// 录像持续秒数，0代表录像时间持续到下一个整点
    {
        char ctemp[16];
        GetTypeValue( hc->http_context, "alert_plan_cap_last_sec_2", ctemp );
        g_config.alert.plan_cap_last_sec_2.var  = atoi( ctemp );
    }
    //[store]存储参数	
    else if( 0 == strcmp( cmd, "store_sd_status" ) )//状态，0：未插入，1：已插入
    {
        char ctemp[16];
        GetTypeValue( hc->http_context, "store_sd_status", ctemp );
        g_config.store.sd_status.var  = atoi( ctemp );
    }
    else if( 0 == strcmp( cmd, "store_sd_total_size" ) )//SD卡总容量
    {
        char ctemp[16];
        GetTypeValue( hc->http_context, "store_sd_total_size", ctemp );
        g_config.store.sd_total_size.var  = atoi( ctemp );
    }
    else if( 0 == strcmp( cmd, "store_sd_used_size" ) )//SD卡已使用容量，两个参数在此无意义，主要是封装在一个结构体内，sd_store_enable
    {
        char ctemp[16];
        GetTypeValue( hc->http_context, "store_sd_used_size", ctemp );
        g_config.store.sd_used_size.var  = atoi( ctemp );
    }
    else if( 0 == strcmp( cmd, "store_sd_store_enable" ) )//启用SD卡存储
    {
        char ctemp[16];
        GetTypeValue( hc->http_context, "store_sd_store_enable", ctemp );
        g_config.store.sd_store_enable.var  = atoi( ctemp );
    }
    else if( 0 == strcmp( cmd, "store_auto_cover_older" ) )//自动覆盖旧文件
    {
        char ctemp[16];
        GetTypeValue( hc->http_context, "store_auto_cover_older", ctemp );
        g_config.store.auto_cover_older.var  = atoi( ctemp );
    }
    else if( 0 == strcmp( cmd, "store_percent_alarm" ) )// 执行告警百分比，磁盘剩余空间百分比<=percent_alarm,则进行告警瞤ercent_del
    {
        char ctemp[16];
        GetTypeValue( hc->http_context, "store_percent_alarm", ctemp );
        g_config.store.percent_alarm.var  = atoi( ctemp );
    }
    else if( 0 == strcmp( cmd, "store_percent_del" ) )// 执行删除百分比，磁盘剩余空间百分比<=percent_del,则进行删除操譻ys
    {
        char ctemp[16];
        GetTypeValue( hc->http_context, "store_percent_del", ctemp );
        g_config.store.percent_del.var  = atoi( ctemp );
    }
    //[sys]系统设置	                        	
    else if( 0 == strcmp( cmd, "sys_app_version" ) )
    {
        GetTypeValue( hc->http_context, "sys_app_version", g_config.sys.app_version.var );
        strdecode( g_config.sys.app_version.var, g_config.sys.app_version.var );
    }
    else if( 0 == strcmp( cmd, "sys_app_time" ) )
    {
        GetTypeValue( hc->http_context, "sys_app_time", g_config.sys.app_time.var );
        strdecode( g_config.sys.app_time.var, g_config.sys.app_time.var );
    }
    //[rtv_start] 实时视频传输请求
    else if( 0 == strcmp( cmd, "rtv_start_channel" ) )// 视频信道 0, 1
    {
        char ctemp[16];
        GetTypeValue( hc->http_context, "rtv_start_channel", ctemp );
        g_config.rtv_start.channel.var  = atoi( ctemp );
    }
    //[htv_start] 录像启动请求
    else if( 0 == strcmp( cmd, "htv_start_channel" ) )// 视频信道 0, 1	
    {
        char ctemp[16];
        GetTypeValue( hc->http_context, "htv_start_channel", ctemp );
        g_config.htv_start.channel.var  = atoi( ctemp );
    }
    //[htv_end] 录像停止请求
    else if( 0 == strcmp( cmd, "htv_end_channel" ) )// 视频信道 0, 1
    {
        char ctemp[16];
        GetTypeValue( hc->http_context, "htv_end_channel", ctemp );
        g_config.htv_end.channel.var  = atoi( ctemp );
    }
    //[pic_start] 图片抓拍启动请求
    else if( 0 == strcmp( cmd, "pic_start_channel" ) )// 视频信道 0, 1
    {
        char ctemp[16];
        GetTypeValue( hc->http_context, "pic_start_channel", ctemp );
        g_config.pic_start.channel.var  = atoi( ctemp );
    }
    else if( 0 == strcmp( cmd, "pic_start_num" ) )// 抓拍张数
    {
        char ctemp[16];
        GetTypeValue( hc->http_context, "pic_start_num", ctemp );
        g_config.pic_start.num.var  = atoi( ctemp );
    }
    //[ptz_control] 云台控制请求
    else if( 0 == strcmp( cmd, "ptz_control_channel" ) )// 视频信道 0, 1
    {
        char ctemp[16];
        GetTypeValue( hc->http_context, "ptz_control_channel", ctemp );
        g_config.ptz_control.channel.var  = atoi( ctemp );
    }
    else if( 0 == strcmp( cmd, "ptz_control_left" ) )// 向左转动  0：无操作 1：操作
    {
        char ctemp[16];
        GetTypeValue( hc->http_context, "ptz_control_left", ctemp );
        g_config.ptz_control.left.var  = atoi( ctemp );
    }
    else if( 0 == strcmp( cmd, "ptz_control_right" ) )// 向右转动  0：无操作 1：操作
    {
        char ctemp[16];
        GetTypeValue( hc->http_context, "ptz_control_right", ctemp );
        g_config.ptz_control.right.var  = atoi( ctemp );
    }
    else if( 0 == strcmp( cmd, "ptz_control_up" ) )// 向上转动  0：无操作 1：操作
    {
        char ctemp[16];
        GetTypeValue( hc->http_context, "ptz_control_up", ctemp );
        g_config.ptz_control.up.var  = atoi( ctemp );
    }
    else if( 0 == strcmp( cmd, "ptz_control_down" ) )// 向下转动  0：无操作 1：操作
    {
        char ctemp[16];
        GetTypeValue( hc->http_context, "ptz_control_down", ctemp );
        g_config.ptz_control.down.var  = atoi( ctemp );
    }
    //[sys_quit] IPC退出请求
    else if( 0 == strcmp( cmd, "sys_quit_flag" ) )// 0：IPC不退出，1：IPC退出
    {
        char ctemp[16];
        GetTypeValue( hc->http_context, "sys_quit_flag", ctemp );
        g_config.sys_quit.flag.var  = atoi( ctemp );
    }
    //[log] 日志获取
    else if( 0 == strcmp( cmd, "log_flag" ) )// 0: 不获取日志, 1:获取日志
    {
        char ctemp[16];
        GetTypeValue( hc->http_context, "log_flag", ctemp );
        g_config.log.flag.var  = atoi( ctemp );
    }
    //[usb_remove]
    else if( 0 == strcmp( cmd, "usb_remove_channel" ) )
    {
        char ctemp[16];
        GetTypeValue( hc->http_context, "usb_remove_channel", ctemp );
        g_config.usb_remove.channel.var  = atoi( ctemp );
    }
    //[hb] 心跳
    else if( 0 == strcmp( cmd, "hb_flag" ) )
    {
        char ctemp[16];
        GetTypeValue( hc->http_context, "hb_flag", ctemp );
        g_config.hb.flag.var  = atoi( ctemp );
    }
    //[def_config] 恢复出厂配置
    else if( 0 == strcmp( cmd, "def_config_flag" ) )
    {
        char ctemp[16];
        GetTypeValue( hc->http_context, "def_config_flag", ctemp );
        g_config.def_config.flag.var  = atoi( ctemp );
    }
    //[md_report]
    else if( 0 == strcmp( cmd, "md_report_md_area_0_0" ) )// 0路视频第0号区域是否有移动 0：没有 1：有
    {
        char ctemp[16];
        GetTypeValue( hc->http_context, "md_report_md_area_0_0", ctemp );
        g_config.md_report.md_area_0_0.var  = atoi( ctemp );
    }
    else if( 0 == strcmp( cmd, "md_report_md_area_0_1" ) )
    {
        char ctemp[16];
        GetTypeValue( hc->http_context, "md_report_md_area_0_1", ctemp );
        g_config.md_report.md_area_0_1.var  = atoi( ctemp );
    }
    else if( 0 == strcmp( cmd, "md_report_md_area_0_2" ) )
    {
        char ctemp[16];
        GetTypeValue( hc->http_context, "md_report_md_area_0_2", ctemp );
        g_config.md_report.md_area_0_2.var  = atoi( ctemp );
    }
    else if( 0 == strcmp( cmd, "md_report_md_area_0_3" ) )
    {
        char ctemp[16];
        GetTypeValue( hc->http_context, "md_report_md_area_0_3", ctemp );
        g_config.md_report.md_area_0_3.var  = atoi( ctemp );
    }
    else if( 0 == strcmp( cmd, "md_report_md_area_1_0" ) )
    {
        char ctemp[16];
        GetTypeValue( hc->http_context, "md_report_md_area_1_0", ctemp );
        g_config.md_report.md_area_1_0.var  = atoi( ctemp );
    }
    else if( 0 == strcmp( cmd, "md_report_md_area_1_1" ) )
    {
        char ctemp[16];
        GetTypeValue( hc->http_context, "md_report_md_area_1_1", ctemp );
        g_config.md_report.md_area_1_1.var  = atoi( ctemp );
    }
    else if( 0 == strcmp( cmd, "md_report_md_area_1_2" ) )
    {
        char ctemp[16];
        GetTypeValue( hc->http_context, "md_report_md_area_1_2", ctemp );
        g_config.md_report.md_area_1_2.var  = atoi( ctemp );
    }
    else if( 0 == strcmp( cmd, "md_report_md_area_1_3" ) )
    {
        char ctemp[16];
        GetTypeValue( hc->http_context, "md_report_md_area_1_3", ctemp );
        g_config.md_report.md_area_1_3.var  = atoi( ctemp );
    }
    //[alarm_disk] 参数都由存储参数全局变量提供
    else if( 0 == strcmp( cmd, "alarm_disk_flag" ) )
    {
        char ctemp[16];
        GetTypeValue( hc->http_context, "alarm_disk_flag", ctemp );
        g_config.alarm_disk.flag.var  = atoi( ctemp );
    }
    //[time_syn] 时间同步
    else if( 0 == strcmp( cmd, "time_syn_time" ) )// 更新系统的日期，格式如下: 2008-10-12 13:14:34
    {
        GetTypeValue( hc->http_context, "time_syn_time", g_config.time_syn.time.var );
        strdecode( g_config.time_syn.time.var, g_config.time_syn.time.var );
    }
    //[alarm_error] IPC向RTU上报严重错误消息，如录像保存时的open失败
    else if( 0 == strcmp( cmd, "alarm_error_alarm_error_id" ) )// 告警错误id
    {
        char ctemp[16];
        GetTypeValue( hc->http_context, "alarm_error_alarm_error_id", ctemp );
        g_config.alarm_error.alarm_error_id.var  = atoi( ctemp );
    }
    else if( 0 == strcmp( cmd, "alarm_error_alarm_error_name" ) )
    {
        GetTypeValue( hc->http_context, "alarm_error_alarm_error_name", g_config.alarm_error.alarm_error_name.var );
        strdecode( g_config.alarm_error.alarm_error_name.var, g_config.alarm_error.alarm_error_name.var );
    }
    //[process_info] 获取ipc进程信息
    else if( 0 == strcmp( cmd, "process_info_flag" ) )
    {
        char ctemp[16];
        GetTypeValue( hc->http_context, "process_info_flag", ctemp );
        g_config.process_info.flag.var  = atoi( ctemp );
    }
    //[end]
    else if( 0 == strcmp( cmd, "end_flag" ) )// 结束标记
    {
        char ctemp[16];
        GetTypeValue( hc->http_context, "end_flag", ctemp );
        g_config.end.flag.var  = atoi( ctemp );
    }


