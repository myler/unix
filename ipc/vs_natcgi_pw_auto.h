            //[login] web登录
            if( 0 == strcmp( cginame, "login_pgh" ) )
            {
                get_login_pgh( outbuf );
            }
            //[user]用户信息  
            else if( 0 == strcmp( cginame, "user_user_num" ) )
            {
                get_user_user_num( outbuf );
            }
            else if( 0 == strcmp( cginame, "user_username_0" ) )
            {
                get_user_username_0( outbuf );// username_0系统管理员
            }
            else if( 0 == strcmp( cginame, "user_password_0" ) )
            {
                get_user_password_0( outbuf );
            }
            else if( 0 == strcmp( cginame, "user_username_1" ) )
            {
                get_user_username_1( outbuf );// username_1 RTU用户					
            }
            else if( 0 == strcmp( cginame, "user_password_1" ) )
            {
                get_user_password_1( outbuf );
            }
            else if( 0 == strcmp( cginame, "user_username_2" ) )
            {
                get_user_username_2( outbuf );// username_2 普通用户
            }
            else if( 0 == strcmp( cginame, "user_password_2" ) )
            {
                get_user_password_2( outbuf );
            }
            else if( 0 == strcmp( cginame, "user_username_3" ) )
            {
                get_user_username_3( outbuf );// username_3 普通用户
            }
            else if( 0 == strcmp( cginame, "user_password_3" ) )
            {
                get_user_password_3( outbuf );
            }
            //[video]视频参数
            else if( 0 == strcmp( cginame, "video_rtv_num" ) )
            {
                get_video_rtv_num( outbuf );//暂定只有2路视频
            }
            else if( 0 == strcmp( cginame, "video_solution_x_1" ) )
            {
                get_video_solution_x_1( outbuf );
            }
            else if( 0 == strcmp( cginame, "video_solution_y_1" ) )
            {
                get_video_solution_y_1( outbuf );
            }
            else if( 0 == strcmp( cginame, "video_bright_1" ) )
            {
                get_video_bright_1( outbuf );//亮度 : 0~255
            }
            else if( 0 == strcmp( cginame, "video_contrast_1" ) )
            {
                get_video_contrast_1( outbuf );//对比度: 0~255
            }
            else if( 0 == strcmp( cginame, "video_frame_interval_1" ) )
            {
                get_video_frame_interval_1( outbuf );//传输帧间隔数,0为无间隔
            }
            else if( 0 == strcmp( cginame, "video_speed_1" ) )
            {
                get_video_speed_1( outbuf );//帧率
            }
            else if( 0 == strcmp( cginame, "video_cache_time_1" ) )
            {
                get_video_cache_time_1( outbuf );//视频图片预缓存时间长度
            }
            else if( 0 == strcmp( cginame, "video_solution_x_2" ) )
            {
                get_video_solution_x_2( outbuf );
            }
            else if( 0 == strcmp( cginame, "video_solution_y_2" ) )
            {
                get_video_solution_y_2( outbuf );
            }
            else if( 0 == strcmp( cginame, "video_bright_2" ) )
            {
                get_video_bright_2( outbuf );
            }
            else if( 0 == strcmp( cginame, "video_contrast_2" ) )
            {
                get_video_contrast_2( outbuf );
            }
            else if( 0 == strcmp( cginame, "video_frame_interval_2" ) )
            {
                get_video_frame_interval_2( outbuf );
            }
            else if( 0 == strcmp( cginame, "video_speed_2" ) )
            {
                get_video_speed_2( outbuf );
            }
            else if( 0 == strcmp( cginame, "video_cache_time_2" ) )
            {
                get_video_cache_time_2( outbuf );
            }
            //[network]网络参数
            else if( 0 == strcmp( cginame, "network_ip_addr" ) )
            {
                get_network_ip_addr( outbuf );
            }
            else if( 0 == strcmp( cginame, "network_ip_mask" ) )
            {
                get_network_ip_mask( outbuf );
            }
            else if( 0 == strcmp( cginame, "network_ip_gateway" ) )
            {
                get_network_ip_gateway( outbuf );
            }
            else if( 0 == strcmp( cginame, "network_dns" ) )
            {
                get_network_dns( outbuf );
            }
            else if( 0 == strcmp( cginame, "network_mac_addr" ) )
            {
                get_network_mac_addr( outbuf );
            }
            else if( 0 == strcmp( cginame, "network_web_port" ) )
            {
                get_network_web_port( outbuf );//web服务器访问端口
            }
            else if( 0 == strcmp( cginame, "network_socket_port" ) )
            {
                get_network_socket_port( outbuf );//socket命令端口
            }
            else if( 0 == strcmp( cginame, "network_rtv_port" ) )
            {
                get_network_rtv_port( outbuf );//视频传送端口
            }
            else if( 0 == strcmp( cginame, "network_alarm_remote_addr" ) )
            {
                get_network_alarm_remote_addr( outbuf );//远程地址，用于IPC主动发送告警
            }
            else if( 0 == strcmp( cginame, "network_alarm_remote_port" ) )
            {
                get_network_alarm_remote_port( outbuf );//远程端口
            }
            //[alert]报警参数	
            else if( 0 == strcmp( cginame, "alert_alert_num" ) )
            {
                get_alert_alert_num( outbuf );//2路报警
            }
            else if( 0 == strcmp( cginame, "alert_capture_pic_enable_1" ) )
            {
                get_alert_capture_pic_enable_1( outbuf );//启用抓拍图片
            }
            else if( 0 == strcmp( cginame, "alert_capture_pic_num_1" ) )
            {
                get_alert_capture_pic_num_1( outbuf );//图片抓拍数目
            }
            else if( 0 == strcmp( cginame, "alert_capture_pic_interval_1" ) )
            {
                get_alert_capture_pic_interval_1( outbuf );//图片抓拍间隔, 后续删除
            }
            else if( 0 == strcmp( cginame, "alert_capture_video_enable_1" ) )
            {
                get_alert_capture_video_enable_1( outbuf );//启用录像
            }
            else if( 0 == strcmp( cginame, "alert_capture_video_last_time_1" ) )
            {
                get_alert_capture_video_last_time_1( outbuf );//录像持续时间
            }
            else if( 0 == strcmp( cginame, "alert_alarm_enable_1" ) )
            {
                get_alert_alarm_enable_1( outbuf );//启用警铃
            }
            else if( 0 == strcmp( cginame, "alert_alarm_delay_1" ) )
            {
                get_alert_alarm_delay_1( outbuf );//警铃延迟时间
            }
            else if( 0 == strcmp( cginame, "alert_alarm_last_time_1" ) )
            {
                get_alert_alarm_last_time_1( outbuf );//警铃持续时间
            }
            else if( 0 == strcmp( cginame, "alert_md_enable_1" ) )
            {
                get_alert_md_enable_1( outbuf );//启用移动侦测
            }
            else if( 0 == strcmp( cginame, "alert_md_sensitivity_1" ) )
            {
                get_alert_md_sensitivity_1( outbuf );//侦测敏感度（30%）
            }
            else if( 0 == strcmp( cginame, "alert_md_area_0_1" ) )
            {
                get_alert_md_area_0_1( outbuf );//侦测区域（矩形）
            }
            else if( 0 == strcmp( cginame, "alert_md_area_1_1" ) )
            {
                get_alert_md_area_1_1( outbuf );//侦测区域（矩形）
            }
            else if( 0 == strcmp( cginame, "alert_md_area_2_1" ) )
            {
                get_alert_md_area_2_1( outbuf );//侦测区域（矩形）
            }
            else if( 0 == strcmp( cginame, "alert_md_area_3_1" ) )
            {
                get_alert_md_area_3_1( outbuf );//侦测区域（矩形）
            }
            else if( 0 == strcmp( cginame, "alert_week_alert_plan_1" ) )
            {
                get_alert_week_alert_plan_1( outbuf );
            }
            else if( 0 == strcmp( cginame, "alert_plan_cap_enalbe_1" ) )
            {
                get_alert_plan_cap_enalbe_1( outbuf );// 布防时间到时，是否启动录像
            }
            else if( 0 == strcmp( cginame, "alert_plan_cap_last_sec_1" ) )
            {
                get_alert_plan_cap_last_sec_1( outbuf );// 录像持续秒数，0代表录像时间持续到下一个整点
            }
            else if( 0 == strcmp( cginame, "alert_capture_pic_enable_2" ) )
            {
                get_alert_capture_pic_enable_2( outbuf );//启用抓拍图片
            }
            else if( 0 == strcmp( cginame, "alert_capture_pic_num_2" ) )
            {
                get_alert_capture_pic_num_2( outbuf );//图片抓拍数目
            }
            else if( 0 == strcmp( cginame, "alert_capture_pic_interval_2" ) )
            {
                get_alert_capture_pic_interval_2( outbuf );//图片抓拍间隔
            }
            else if( 0 == strcmp( cginame, "alert_capture_video_enable_2" ) )
            {
                get_alert_capture_video_enable_2( outbuf );//启用录像
            }
            else if( 0 == strcmp( cginame, "alert_capture_video_last_time_2" ) )
            {
                get_alert_capture_video_last_time_2( outbuf );//录像持续时间
            }
            else if( 0 == strcmp( cginame, "alert_alarm_enable_2" ) )
            {
                get_alert_alarm_enable_2( outbuf );//启用警铃
            }
            else if( 0 == strcmp( cginame, "alert_alarm_delay_2" ) )
            {
                get_alert_alarm_delay_2( outbuf );//警铃延迟时间
            }
            else if( 0 == strcmp( cginame, "alert_alarm_last_time_2" ) )
            {
                get_alert_alarm_last_time_2( outbuf );//警铃持续时间
            }
            else if( 0 == strcmp( cginame, "alert_md_enable_2" ) )
            {
                get_alert_md_enable_2( outbuf );//启用移动侦测
            }
            else if( 0 == strcmp( cginame, "alert_md_sensitivity_2" ) )
            {
                get_alert_md_sensitivity_2( outbuf );//侦测敏感度（30%）
            }
            else if( 0 == strcmp( cginame, "alert_md_area_0_2" ) )
            {
                get_alert_md_area_0_2( outbuf );//侦测区域（矩形）
            }
            else if( 0 == strcmp( cginame, "alert_md_area_1_2" ) )
            {
                get_alert_md_area_1_2( outbuf );//侦测区域（矩形）
            }
            else if( 0 == strcmp( cginame, "alert_md_area_2_2" ) )
            {
                get_alert_md_area_2_2( outbuf );//侦测区域（矩形）
            }
            else if( 0 == strcmp( cginame, "alert_md_area_3_2" ) )
            {
                get_alert_md_area_3_2( outbuf );//侦测区域（矩形）
            }
            else if( 0 == strcmp( cginame, "alert_week_alert_plan_2" ) )
            {
                get_alert_week_alert_plan_2( outbuf );
            }
            else if( 0 == strcmp( cginame, "alert_plan_cap_enalbe_2" ) )
            {
                get_alert_plan_cap_enalbe_2( outbuf );// 布防时间到时，是否启动录像
            }
            else if( 0 == strcmp( cginame, "alert_plan_cap_last_sec_2" ) )
            {
                get_alert_plan_cap_last_sec_2( outbuf );// 录像持续秒数，0代表录像时间持续到下一个整点
            }
            //[store]存储参数	
            else if( 0 == strcmp( cginame, "store_sd_status" ) )
            {
                get_store_sd_status( outbuf );//状态，0：未插入，1：已插入
            }
            else if( 0 == strcmp( cginame, "store_sd_total_size" ) )
            {
                get_store_sd_total_size( outbuf );//SD卡总容量
            }
            else if( 0 == strcmp( cginame, "store_sd_used_size" ) )
            {
                get_store_sd_used_size( outbuf );//SD卡已使用容量，两个参数在此无意义，主要是封装在一个结构体内，sd_store_enable
            }
            else if( 0 == strcmp( cginame, "store_sd_store_enable" ) )
            {
                get_store_sd_store_enable( outbuf );//启用SD卡存储
            }
            else if( 0 == strcmp( cginame, "store_auto_cover_older" ) )
            {
                get_store_auto_cover_older( outbuf );//自动覆盖旧文件
            }
            else if( 0 == strcmp( cginame, "store_percent_alarm" ) )
            {
                get_store_percent_alarm( outbuf );// 执行告警百分比，磁盘剩余空间百分比<=percent_alarm,则进行告警瞤ercent_del
            }
            else if( 0 == strcmp( cginame, "store_percent_del" ) )
            {
                get_store_percent_del( outbuf );// 执行删除百分比，磁盘剩余空间百分比<=percent_del,则进行删除操譻ys
            }
            //[sys]系统设置	                        	
            else if( 0 == strcmp( cginame, "sys_app_version" ) )
            {
                get_sys_app_version( outbuf );
            }
            else if( 0 == strcmp( cginame, "sys_app_time" ) )
            {
                get_sys_app_time( outbuf );
            }
            //[rtv_start] 实时视频传输请求
            else if( 0 == strcmp( cginame, "rtv_start_channel" ) )
            {
                get_rtv_start_channel( outbuf );// 视频信道 0, 1
            }
            //[htv_start] 录像启动请求
            else if( 0 == strcmp( cginame, "htv_start_channel" ) )
            {
                get_htv_start_channel( outbuf );// 视频信道 0, 1	
            }
            //[htv_end] 录像停止请求
            else if( 0 == strcmp( cginame, "htv_end_channel" ) )
            {
                get_htv_end_channel( outbuf );// 视频信道 0, 1
            }
            //[pic_start] 图片抓拍启动请求
            else if( 0 == strcmp( cginame, "pic_start_channel" ) )
            {
                get_pic_start_channel( outbuf );// 视频信道 0, 1
            }
            else if( 0 == strcmp( cginame, "pic_start_num" ) )
            {
                get_pic_start_num( outbuf );// 抓拍张数
            }
            //[ptz_control] 云台控制请求
            else if( 0 == strcmp( cginame, "ptz_control_channel" ) )
            {
                get_ptz_control_channel( outbuf );// 视频信道 0, 1
            }
            else if( 0 == strcmp( cginame, "ptz_control_left" ) )
            {
                get_ptz_control_left( outbuf );// 向左转动  0：无操作 1：操作
            }
            else if( 0 == strcmp( cginame, "ptz_control_right" ) )
            {
                get_ptz_control_right( outbuf );// 向右转动  0：无操作 1：操作
            }
            else if( 0 == strcmp( cginame, "ptz_control_up" ) )
            {
                get_ptz_control_up( outbuf );// 向上转动  0：无操作 1：操作
            }
            else if( 0 == strcmp( cginame, "ptz_control_down" ) )
            {
                get_ptz_control_down( outbuf );// 向下转动  0：无操作 1：操作
            }
            //[sys_quit] IPC退出请求
            else if( 0 == strcmp( cginame, "sys_quit_flag" ) )
            {
                get_sys_quit_flag( outbuf );// 0：IPC不退出，1：IPC退出
            }
            //[log] 日志获取
            else if( 0 == strcmp( cginame, "log_flag" ) )
            {
                get_log_flag( outbuf );// 0: 不获取日志, 1:获取日志
            }
            //[usb_remove]
            else if( 0 == strcmp( cginame, "usb_remove_channel" ) )
            {
                get_usb_remove_channel( outbuf );
            }
            //[hb] 心跳
            else if( 0 == strcmp( cginame, "hb_flag" ) )
            {
                get_hb_flag( outbuf );
            }
            //[def_config] 恢复出厂配置
            else if( 0 == strcmp( cginame, "def_config_flag" ) )
            {
                get_def_config_flag( outbuf );
            }
            //[md_report]
            else if( 0 == strcmp( cginame, "md_report_md_area_0_0" ) )
            {
                get_md_report_md_area_0_0( outbuf );// 0路视频第0号区域是否有移动 0：没有 1：有
            }
            else if( 0 == strcmp( cginame, "md_report_md_area_0_1" ) )
            {
                get_md_report_md_area_0_1( outbuf );
            }
            else if( 0 == strcmp( cginame, "md_report_md_area_0_2" ) )
            {
                get_md_report_md_area_0_2( outbuf );
            }
            else if( 0 == strcmp( cginame, "md_report_md_area_0_3" ) )
            {
                get_md_report_md_area_0_3( outbuf );
            }
            else if( 0 == strcmp( cginame, "md_report_md_area_1_0" ) )
            {
                get_md_report_md_area_1_0( outbuf );
            }
            else if( 0 == strcmp( cginame, "md_report_md_area_1_1" ) )
            {
                get_md_report_md_area_1_1( outbuf );
            }
            else if( 0 == strcmp( cginame, "md_report_md_area_1_2" ) )
            {
                get_md_report_md_area_1_2( outbuf );
            }
            else if( 0 == strcmp( cginame, "md_report_md_area_1_3" ) )
            {
                get_md_report_md_area_1_3( outbuf );
            }
            //[alarm_disk] 参数都由存储参数全局变量提供
            else if( 0 == strcmp( cginame, "alarm_disk_flag" ) )
            {
                get_alarm_disk_flag( outbuf );
            }
            //[time_syn] 时间同步
            else if( 0 == strcmp( cginame, "time_syn_time" ) )
            {
                get_time_syn_time( outbuf );// 更新系统的日期，格式如下: 2008-10-12 13:14:34
            }
            //[alarm_error] IPC向RTU上报严重错误消息，如录像保存时的open失败
            else if( 0 == strcmp( cginame, "alarm_error_alarm_error_id" ) )
            {
                get_alarm_error_alarm_error_id( outbuf );// 告警错误id
            }
            else if( 0 == strcmp( cginame, "alarm_error_alarm_error_name" ) )
            {
                get_alarm_error_alarm_error_name( outbuf );
            }
            //[process_info] 获取ipc进程信息
            else if( 0 == strcmp( cginame, "process_info_flag" ) )
            {
                get_process_info_flag( outbuf );
            }
            //[end]
            else if( 0 == strcmp( cginame, "end_flag" ) )
            {
                get_end_flag( outbuf );// 结束标记
            }
