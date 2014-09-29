// 各种大类的枚举
enum CONFIG_VAR_INDEX_
{
    CFG_var_login = 1, // web登录
    CFG_var_user, //用户信息  
    CFG_var_video, //视频参数
    CFG_var_network, //网络参数
    CFG_var_alert, //报警参数	
    CFG_var_store, //存储参数	
    CFG_var_sys, //系统设置	                        	
    CFG_var_rtv_start, // 实时视频传输请求
    CFG_var_htv_start, // 录像启动请求
    CFG_var_htv_end, // 录像停止请求
    CFG_var_pic_start, // 图片抓拍启动请求
    CFG_var_ptz_control, // 云台控制请求
    CFG_var_sys_quit, // IPC退出请求
    CFG_var_log, // 日志获取
    CFG_var_usb_remove, 
    CFG_var_hb, // 心跳
    CFG_var_def_config, // 恢复出厂配置
    CFG_var_md_report, 
    CFG_var_alarm_disk, // 参数都由存储参数全局变量提供
    CFG_var_time_syn, // 时间同步
    CFG_var_alarm_error, // IPC向RTU上报严重错误消息，如录像保存时的open失败
    CFG_var_process_info, // 获取ipc进程信息
    CFG_var_end, 
};

//各种大类的定义
typedef struct tag_var_login// web登录
{
    int pgh;
}s_var_login;

typedef struct tag_var_login_get_req
{
   s_user_info user_info;
}s_var_login_get_req;

typedef struct tag_var_login_set_req
{
   s_user_info user_info;
   s_var_login var_login;
}s_var_login_set_req;

typedef struct tag_var_user//用户信息  
{
    int user_num;
    char username_0[_LEN_NORMAL];// username_0系统管理员
    char password_0[_LEN_NORMAL];
    char username_1[_LEN_NORMAL];// username_1 RTU用户					
    char password_1[_LEN_NORMAL];
    char username_2[_LEN_NORMAL];// username_2 普通用户
    char password_2[_LEN_NORMAL];
    char username_3[_LEN_NORMAL];// username_3 普通用户
    char password_3[_LEN_NORMAL];
}s_var_user;

typedef struct tag_var_user_get_req
{
   s_user_info user_info;
}s_var_user_get_req;

typedef struct tag_var_user_set_req
{
   s_user_info user_info;
   s_var_user var_user;
}s_var_user_set_req;

typedef struct tag_var_video//视频参数
{
    int rtv_num;//暂定只有2路视频
    int solution_x_1;
    int solution_y_1;
    int bright_1;//亮度 : 0~255
    int contrast_1;//对比度: 0~255
    int frame_interval_1;//传输帧间隔数,0为无间隔
    int speed_1;//帧率
    int cache_time_1;//视频图片预缓存时间长度
    int solution_x_2;
    int solution_y_2;
    int bright_2;
    int contrast_2;
    int frame_interval_2;
    int speed_2;
    int cache_time_2;
}s_var_video;

typedef struct tag_var_video_get_req
{
   s_user_info user_info;
}s_var_video_get_req;

typedef struct tag_var_video_set_req
{
   s_user_info user_info;
   s_var_video var_video;
}s_var_video_set_req;

typedef struct tag_var_network//网络参数
{
    char ip_addr[_LEN_NORMAL];
    char ip_mask[_LEN_NORMAL];
    char ip_gateway[_LEN_NORMAL];
    char dns[_LEN_NORMAL];
    char mac_addr[_LEN_NORMAL];
    int web_port;//web服务器访问端口
    int socket_port;//socket命令端口
    int rtv_port;//视频传送端口
    char alarm_remote_addr[_LEN_NORMAL];//远程地址，用于IPC主动发送告警
    int alarm_remote_port;//远程端口
}s_var_network;

typedef struct tag_var_network_get_req
{
   s_user_info user_info;
}s_var_network_get_req;

typedef struct tag_var_network_set_req
{
   s_user_info user_info;
   s_var_network var_network;
}s_var_network_set_req;

typedef struct tag_var_alert//报警参数	
{
    int alert_num;//2路报警
    int capture_pic_enable_1;//启用抓拍图片
    int capture_pic_num_1;//图片抓拍数目
    int capture_pic_interval_1;//图片抓拍间隔, 后续删除
    int capture_video_enable_1;//启用录像
    int capture_video_last_time_1;//录像持续时间
    int alarm_enable_1;//启用警铃
    int alarm_delay_1;//警铃延迟时间
    int alarm_last_time_1;//警铃持续时间
    int md_enable_1;//启用移动侦测
    int md_sensitivity_1;//侦测敏感度（30%）
    char md_area_0_1[_LEN_NORMAL];//侦测区域（矩形）
    char md_area_1_1[_LEN_NORMAL];//侦测区域（矩形）
    char md_area_2_1[_LEN_NORMAL];//侦测区域（矩形）
    char md_area_3_1[_LEN_NORMAL];//侦测区域（矩形）
    char week_alert_plan_1[_LEN_WEEK];
    int plan_cap_enalbe_1;// 布防时间到时，是否启动录像
    int plan_cap_last_sec_1;// 录像持续秒数，0代表录像时间持续到下一个整点
    int capture_pic_enable_2;//启用抓拍图片
    int capture_pic_num_2;//图片抓拍数目
    int capture_pic_interval_2;//图片抓拍间隔
    int capture_video_enable_2;//启用录像
    int capture_video_last_time_2;//录像持续时间
    int alarm_enable_2;//启用警铃
    int alarm_delay_2;//警铃延迟时间
    int alarm_last_time_2;//警铃持续时间
    int md_enable_2;//启用移动侦测
    int md_sensitivity_2;//侦测敏感度（30%）
    char md_area_0_2[_LEN_NORMAL];//侦测区域（矩形）
    char md_area_1_2[_LEN_NORMAL];//侦测区域（矩形）
    char md_area_2_2[_LEN_NORMAL];//侦测区域（矩形）
    char md_area_3_2[_LEN_NORMAL];//侦测区域（矩形）
    char week_alert_plan_2[_LEN_WEEK];
    int plan_cap_enalbe_2;// 布防时间到时，是否启动录像
    int plan_cap_last_sec_2;// 录像持续秒数，0代表录像时间持续到下一个整点
}s_var_alert;

typedef struct tag_var_alert_get_req
{
   s_user_info user_info;
}s_var_alert_get_req;

typedef struct tag_var_alert_set_req
{
   s_user_info user_info;
   s_var_alert var_alert;
}s_var_alert_set_req;

typedef struct tag_var_store//存储参数	
{
    int sd_status;//状态，0：未插入，1：已插入
    int sd_total_size;//SD卡总容量
    int sd_used_size;//SD卡已使用容量，两个参数在此无意义，主要是封装在一个结构体内，sd_store_enable
    int sd_store_enable;//启用SD卡存储
    int auto_cover_older;//自动覆盖旧文件
    int percent_alarm;// 执行告警百分比，磁盘剩余空间百分比<=percent_alarm,则进行告警瞤ercent_del
    int percent_del;// 执行删除百分比，磁盘剩余空间百分比<=percent_del,则进行删除操譻ys
}s_var_store;

typedef struct tag_var_store_get_req
{
   s_user_info user_info;
}s_var_store_get_req;

typedef struct tag_var_store_set_req
{
   s_user_info user_info;
   s_var_store var_store;
}s_var_store_set_req;

typedef struct tag_var_sys//系统设置	                        	
{
    char app_version[_LEN_NORMAL];
    char app_time[_LEN_NORMAL];
}s_var_sys;

typedef struct tag_var_sys_get_req
{
   s_user_info user_info;
}s_var_sys_get_req;

typedef struct tag_var_sys_set_req
{
   s_user_info user_info;
   s_var_sys var_sys;
}s_var_sys_set_req;

typedef struct tag_var_rtv_start// 实时视频传输请求
{
    int channel;// 视频信道 0, 1
}s_var_rtv_start;

typedef struct tag_var_rtv_start_get_req
{
   s_user_info user_info;
}s_var_rtv_start_get_req;

typedef struct tag_var_rtv_start_set_req
{
   s_user_info user_info;
   s_var_rtv_start var_rtv_start;
}s_var_rtv_start_set_req;

typedef struct tag_var_htv_start// 录像启动请求
{
    int channel;// 视频信道 0, 1	
}s_var_htv_start;

typedef struct tag_var_htv_start_get_req
{
   s_user_info user_info;
}s_var_htv_start_get_req;

typedef struct tag_var_htv_start_set_req
{
   s_user_info user_info;
   s_var_htv_start var_htv_start;
}s_var_htv_start_set_req;

typedef struct tag_var_htv_end// 录像停止请求
{
    int channel;// 视频信道 0, 1
}s_var_htv_end;

typedef struct tag_var_htv_end_get_req
{
   s_user_info user_info;
}s_var_htv_end_get_req;

typedef struct tag_var_htv_end_set_req
{
   s_user_info user_info;
   s_var_htv_end var_htv_end;
}s_var_htv_end_set_req;

typedef struct tag_var_pic_start// 图片抓拍启动请求
{
    int channel;// 视频信道 0, 1
    int num;// 抓拍张数
}s_var_pic_start;

typedef struct tag_var_pic_start_get_req
{
   s_user_info user_info;
}s_var_pic_start_get_req;

typedef struct tag_var_pic_start_set_req
{
   s_user_info user_info;
   s_var_pic_start var_pic_start;
}s_var_pic_start_set_req;

typedef struct tag_var_ptz_control// 云台控制请求
{
    int channel;// 视频信道 0, 1
    int left;// 向左转动  0：无操作 1：操作
    int right;// 向右转动  0：无操作 1：操作
    int up;// 向上转动  0：无操作 1：操作
    int down;// 向下转动  0：无操作 1：操作
}s_var_ptz_control;

typedef struct tag_var_ptz_control_get_req
{
   s_user_info user_info;
}s_var_ptz_control_get_req;

typedef struct tag_var_ptz_control_set_req
{
   s_user_info user_info;
   s_var_ptz_control var_ptz_control;
}s_var_ptz_control_set_req;

typedef struct tag_var_sys_quit// IPC退出请求
{
    int flag;// 0：IPC不退出，1：IPC退出
}s_var_sys_quit;

typedef struct tag_var_sys_quit_get_req
{
   s_user_info user_info;
}s_var_sys_quit_get_req;

typedef struct tag_var_sys_quit_set_req
{
   s_user_info user_info;
   s_var_sys_quit var_sys_quit;
}s_var_sys_quit_set_req;

typedef struct tag_var_log// 日志获取
{
    int flag;// 0: 不获取日志, 1:获取日志
}s_var_log;

typedef struct tag_var_log_get_req
{
   s_user_info user_info;
}s_var_log_get_req;

typedef struct tag_var_log_set_req
{
   s_user_info user_info;
   s_var_log var_log;
}s_var_log_set_req;

typedef struct tag_var_usb_remove
{
    int channel;
}s_var_usb_remove;

typedef struct tag_var_usb_remove_get_req
{
   s_user_info user_info;
}s_var_usb_remove_get_req;

typedef struct tag_var_usb_remove_set_req
{
   s_user_info user_info;
   s_var_usb_remove var_usb_remove;
}s_var_usb_remove_set_req;

typedef struct tag_var_hb// 心跳
{
    int flag;
}s_var_hb;

typedef struct tag_var_hb_get_req
{
   s_user_info user_info;
}s_var_hb_get_req;

typedef struct tag_var_hb_set_req
{
   s_user_info user_info;
   s_var_hb var_hb;
}s_var_hb_set_req;

typedef struct tag_var_def_config// 恢复出厂配置
{
    int flag;
}s_var_def_config;

typedef struct tag_var_def_config_get_req
{
   s_user_info user_info;
}s_var_def_config_get_req;

typedef struct tag_var_def_config_set_req
{
   s_user_info user_info;
   s_var_def_config var_def_config;
}s_var_def_config_set_req;

typedef struct tag_var_md_report
{
    int md_area_0_0;// 0路视频第0号区域是否有移动 0：没有 1：有
    int md_area_0_1;
    int md_area_0_2;
    int md_area_0_3;
    int md_area_1_0;
    int md_area_1_1;
    int md_area_1_2;
    int md_area_1_3;
}s_var_md_report;

typedef struct tag_var_md_report_get_req
{
   s_user_info user_info;
}s_var_md_report_get_req;

typedef struct tag_var_md_report_set_req
{
   s_user_info user_info;
   s_var_md_report var_md_report;
}s_var_md_report_set_req;

typedef struct tag_var_alarm_disk// 参数都由存储参数全局变量提供
{
    int flag;
}s_var_alarm_disk;

typedef struct tag_var_alarm_disk_get_req
{
   s_user_info user_info;
}s_var_alarm_disk_get_req;

typedef struct tag_var_alarm_disk_set_req
{
   s_user_info user_info;
   s_var_alarm_disk var_alarm_disk;
}s_var_alarm_disk_set_req;

typedef struct tag_var_time_syn// 时间同步
{
    char time[_LEN_NORMAL];// 更新系统的日期，格式如下: 2008-10-12 13:14:34
}s_var_time_syn;

typedef struct tag_var_time_syn_get_req
{
   s_user_info user_info;
}s_var_time_syn_get_req;

typedef struct tag_var_time_syn_set_req
{
   s_user_info user_info;
   s_var_time_syn var_time_syn;
}s_var_time_syn_set_req;

typedef struct tag_var_alarm_error// IPC向RTU上报严重错误消息，如录像保存时的open失败
{
    int alarm_error_id;// 告警错误id
    char alarm_error_name[_LEN_NORMAL];
}s_var_alarm_error;

typedef struct tag_var_alarm_error_get_req
{
   s_user_info user_info;
}s_var_alarm_error_get_req;

typedef struct tag_var_alarm_error_set_req
{
   s_user_info user_info;
   s_var_alarm_error var_alarm_error;
}s_var_alarm_error_set_req;

typedef struct tag_var_process_info// 获取ipc进程信息
{
    int flag;
}s_var_process_info;

typedef struct tag_var_process_info_get_req
{
   s_user_info user_info;
}s_var_process_info_get_req;

typedef struct tag_var_process_info_set_req
{
   s_user_info user_info;
   s_var_process_info var_process_info;
}s_var_process_info_set_req;

typedef struct tag_var_end
{
    int flag;// 结束标记
}s_var_end;

typedef struct tag_var_end_get_req
{
   s_user_info user_info;
}s_var_end_get_req;

typedef struct tag_var_end_set_req
{
   s_user_info user_info;
   s_var_end var_end;
}s_var_end_set_req;


//全局变量
typedef struct tagAllConfigVar
{
    s_var_login    login;// web登录
    s_var_user    user;//用户信息  
    s_var_video    video;//视频参数
    s_var_network    network;//网络参数
    s_var_alert    alert;//报警参数	
    s_var_store    store;//存储参数	
    s_var_sys    sys;//系统设置	                        	
    s_var_rtv_start    rtv_start;// 实时视频传输请求
    s_var_htv_start    htv_start;// 录像启动请求
    s_var_htv_end    htv_end;// 录像停止请求
    s_var_pic_start    pic_start;// 图片抓拍启动请求
    s_var_ptz_control    ptz_control;// 云台控制请求
    s_var_sys_quit    sys_quit;// IPC退出请求
    s_var_log    log;// 日志获取
    s_var_usb_remove    usb_remove;
    s_var_hb    hb;// 心跳
    s_var_def_config    def_config;// 恢复出厂配置
    s_var_md_report    md_report;
    s_var_alarm_disk    alarm_disk;// 参数都由存储参数全局变量提供
    s_var_time_syn    time_syn;// 时间同步
    s_var_alarm_error    alarm_error;// IPC向RTU上报严重错误消息，如录像保存时的open失败
    s_var_process_info    process_info;// 获取ipc进程信息
    s_var_end    end;

    int config_index;
}AllConfigVar;


