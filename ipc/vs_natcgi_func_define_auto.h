//[login] web登录
void get_login_pgh( char * outbuf );
//[user]用户信息  
void get_user_user_num( char * outbuf );
void get_user_username_0( char * outbuf );// username_0系统管理员
void get_user_password_0( char * outbuf );
void get_user_username_1( char * outbuf );// username_1 RTU用户					
void get_user_password_1( char * outbuf );
void get_user_username_2( char * outbuf );// username_2 普通用户
void get_user_password_2( char * outbuf );
void get_user_username_3( char * outbuf );// username_3 普通用户
void get_user_password_3( char * outbuf );
//[video]视频参数
void get_video_rtv_num( char * outbuf );//暂定只有2路视频
void get_video_solution_x_1( char * outbuf );
void get_video_solution_y_1( char * outbuf );
void get_video_bright_1( char * outbuf );//亮度 : 0~255
void get_video_contrast_1( char * outbuf );//对比度: 0~255
void get_video_frame_interval_1( char * outbuf );//传输帧间隔数,0为无间隔
void get_video_speed_1( char * outbuf );//帧率
void get_video_cache_time_1( char * outbuf );//视频图片预缓存时间长度
void get_video_solution_x_2( char * outbuf );
void get_video_solution_y_2( char * outbuf );
void get_video_bright_2( char * outbuf );
void get_video_contrast_2( char * outbuf );
void get_video_frame_interval_2( char * outbuf );
void get_video_speed_2( char * outbuf );
void get_video_cache_time_2( char * outbuf );
//[network]网络参数
void get_network_ip_addr( char * outbuf );
void get_network_ip_mask( char * outbuf );
void get_network_ip_gateway( char * outbuf );
void get_network_dns( char * outbuf );
void get_network_mac_addr( char * outbuf );
void get_network_web_port( char * outbuf );//web服务器访问端口
void get_network_socket_port( char * outbuf );//socket命令端口
void get_network_rtv_port( char * outbuf );//视频传送端口
void get_network_alarm_remote_addr( char * outbuf );//远程地址，用于IPC主动发送告警
void get_network_alarm_remote_port( char * outbuf );//远程端口
//[alert]报警参数	
void get_alert_alert_num( char * outbuf );//2路报警
void get_alert_capture_pic_enable_1( char * outbuf );//启用抓拍图片
void get_alert_capture_pic_num_1( char * outbuf );//图片抓拍数目
void get_alert_capture_pic_interval_1( char * outbuf );//图片抓拍间隔, 后续删除
void get_alert_capture_video_enable_1( char * outbuf );//启用录像
void get_alert_capture_video_last_time_1( char * outbuf );//录像持续时间
void get_alert_alarm_enable_1( char * outbuf );//启用警铃
void get_alert_alarm_delay_1( char * outbuf );//警铃延迟时间
void get_alert_alarm_last_time_1( char * outbuf );//警铃持续时间
void get_alert_md_enable_1( char * outbuf );//启用移动侦测
void get_alert_md_sensitivity_1( char * outbuf );//侦测敏感度（30%）
void get_alert_md_area_0_1( char * outbuf );//侦测区域（矩形）
void get_alert_md_area_1_1( char * outbuf );//侦测区域（矩形）
void get_alert_md_area_2_1( char * outbuf );//侦测区域（矩形）
void get_alert_md_area_3_1( char * outbuf );//侦测区域（矩形）
void get_alert_week_alert_plan_1( char * outbuf );
void get_alert_plan_cap_enalbe_1( char * outbuf );// 布防时间到时，是否启动录像
void get_alert_plan_cap_last_sec_1( char * outbuf );// 录像持续秒数，0代表录像时间持续到下一个整点
void get_alert_capture_pic_enable_2( char * outbuf );//启用抓拍图片
void get_alert_capture_pic_num_2( char * outbuf );//图片抓拍数目
void get_alert_capture_pic_interval_2( char * outbuf );//图片抓拍间隔
void get_alert_capture_video_enable_2( char * outbuf );//启用录像
void get_alert_capture_video_last_time_2( char * outbuf );//录像持续时间
void get_alert_alarm_enable_2( char * outbuf );//启用警铃
void get_alert_alarm_delay_2( char * outbuf );//警铃延迟时间
void get_alert_alarm_last_time_2( char * outbuf );//警铃持续时间
void get_alert_md_enable_2( char * outbuf );//启用移动侦测
void get_alert_md_sensitivity_2( char * outbuf );//侦测敏感度（30%）
void get_alert_md_area_0_2( char * outbuf );//侦测区域（矩形）
void get_alert_md_area_1_2( char * outbuf );//侦测区域（矩形）
void get_alert_md_area_2_2( char * outbuf );//侦测区域（矩形）
void get_alert_md_area_3_2( char * outbuf );//侦测区域（矩形）
void get_alert_week_alert_plan_2( char * outbuf );
void get_alert_plan_cap_enalbe_2( char * outbuf );// 布防时间到时，是否启动录像
void get_alert_plan_cap_last_sec_2( char * outbuf );// 录像持续秒数，0代表录像时间持续到下一个整点
//[store]存储参数	
void get_store_sd_status( char * outbuf );//状态，0：未插入，1：已插入
void get_store_sd_total_size( char * outbuf );//SD卡总容量
void get_store_sd_used_size( char * outbuf );//SD卡已使用容量，两个参数在此无意义，主要是封装在一个结构体内，sd_store_enable
void get_store_sd_store_enable( char * outbuf );//启用SD卡存储
void get_store_auto_cover_older( char * outbuf );//自动覆盖旧文件
void get_store_percent_alarm( char * outbuf );// 执行告警百分比，磁盘剩余空间百分比<=percent_alarm,则进行告警瞤ercent_del
void get_store_percent_del( char * outbuf );// 执行删除百分比，磁盘剩余空间百分比<=percent_del,则进行删除操譻ys
//[sys]系统设置	                        	
void get_sys_app_version( char * outbuf );
void get_sys_app_time( char * outbuf );
//[rtv_start] 实时视频传输请求
void get_rtv_start_channel( char * outbuf );// 视频信道 0, 1
//[htv_start] 录像启动请求
void get_htv_start_channel( char * outbuf );// 视频信道 0, 1	
//[htv_end] 录像停止请求
void get_htv_end_channel( char * outbuf );// 视频信道 0, 1
//[pic_start] 图片抓拍启动请求
void get_pic_start_channel( char * outbuf );// 视频信道 0, 1
void get_pic_start_num( char * outbuf );// 抓拍张数
//[ptz_control] 云台控制请求
void get_ptz_control_channel( char * outbuf );// 视频信道 0, 1
void get_ptz_control_left( char * outbuf );// 向左转动  0：无操作 1：操作
void get_ptz_control_right( char * outbuf );// 向右转动  0：无操作 1：操作
void get_ptz_control_up( char * outbuf );// 向上转动  0：无操作 1：操作
void get_ptz_control_down( char * outbuf );// 向下转动  0：无操作 1：操作
//[sys_quit] IPC退出请求
void get_sys_quit_flag( char * outbuf );// 0：IPC不退出，1：IPC退出
//[log] 日志获取
void get_log_flag( char * outbuf );// 0: 不获取日志, 1:获取日志
//[usb_remove]
void get_usb_remove_channel( char * outbuf );
//[hb] 心跳
void get_hb_flag( char * outbuf );
//[def_config] 恢复出厂配置
void get_def_config_flag( char * outbuf );
//[md_report]
void get_md_report_md_area_0_0( char * outbuf );// 0路视频第0号区域是否有移动 0：没有 1：有
void get_md_report_md_area_0_1( char * outbuf );
void get_md_report_md_area_0_2( char * outbuf );
void get_md_report_md_area_0_3( char * outbuf );
void get_md_report_md_area_1_0( char * outbuf );
void get_md_report_md_area_1_1( char * outbuf );
void get_md_report_md_area_1_2( char * outbuf );
void get_md_report_md_area_1_3( char * outbuf );
//[alarm_disk] 参数都由存储参数全局变量提供
void get_alarm_disk_flag( char * outbuf );
//[time_syn] 时间同步
void get_time_syn_time( char * outbuf );// 更新系统的日期，格式如下: 2008-10-12 13:14:34
//[alarm_error] IPC向RTU上报严重错误消息，如录像保存时的open失败
void get_alarm_error_alarm_error_id( char * outbuf );// 告警错误id
void get_alarm_error_alarm_error_name( char * outbuf );
//[process_info] 获取ipc进程信息
void get_process_info_flag( char * outbuf );
//[end]
void get_end_flag( char * outbuf );// 结束标记


