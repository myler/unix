// 各种大类的枚举
enum CONFIG_INDEX
{
    CFG_login = 1, // web登录
    CFG_user, //用户信息  
    CFG_video, //视频参数
    CFG_network, //网络参数
    CFG_alert, //报警参数	
    CFG_store, //存储参数	
    CFG_sys, //系统设置	                        	
    CFG_rtv_start, // 实时视频传输请求
    CFG_htv_start, // 录像启动请求
    CFG_htv_end, // 录像停止请求
    CFG_pic_start, // 图片抓拍启动请求
    CFG_ptz_control, // 云台控制请求
    CFG_sys_quit, // IPC退出请求
    CFG_log, // 日志获取
    CFG_usb_remove, 
    CFG_hb, // 心跳
    CFG_def_config, // 恢复出厂配置
    CFG_md_report, 
    CFG_alarm_disk, // 参数都由存储参数全局变量提供
    CFG_time_syn, // 时间同步
    CFG_alarm_error, // IPC向RTU上报严重错误消息，如录像保存时的open失败
    CFG_process_info, // 获取ipc进程信息
    CFG_end, 
};

//各种大类的定义
typedef struct tag_login// web登录
{
    char        name[_LEN_NORMAL];
    char        note[_LEN_EXTEND];

    D_int       pgh;
} s_login;

typedef struct tag_user//用户信息  
{
    char        name[_LEN_NORMAL];
    char        note[_LEN_EXTEND];

    D_int       user_num;
    D_string    username_0;// username_0系统管理员
    D_string    password_0;
    D_string    username_1;// username_1 RTU用户					
    D_string    password_1;
    D_string    username_2;// username_2 普通用户
    D_string    password_2;
    D_string    username_3;// username_3 普通用户
    D_string    password_3;
} s_user;

typedef struct tag_video//视频参数
{
    char        name[_LEN_NORMAL];
    char        note[_LEN_EXTEND];

    D_int       rtv_num;//暂定只有2路视频
    D_int       solution_x_1;
    D_int       solution_y_1;
    D_int       bright_1;//亮度 : 0~255
    D_int       contrast_1;//对比度: 0~255
    D_int       frame_interval_1;//传输帧间隔数,0为无间隔
    D_int       speed_1;//帧率
    D_int       cache_time_1;//视频图片预缓存时间长度
    D_int       solution_x_2;
    D_int       solution_y_2;
    D_int       bright_2;
    D_int       contrast_2;
    D_int       frame_interval_2;
    D_int       speed_2;
    D_int       cache_time_2;
} s_video;

typedef struct tag_network//网络参数
{
    char        name[_LEN_NORMAL];
    char        note[_LEN_EXTEND];

    D_string    ip_addr;
    D_string    ip_mask;
    D_string    ip_gateway;
    D_string    dns;
    D_string    mac_addr;
    D_int       web_port;//web服务器访问端口
    D_int       socket_port;//socket命令端口
    D_int       rtv_port;//视频传送端口
    D_string    alarm_remote_addr;//远程地址，用于IPC主动发送告警
    D_int       alarm_remote_port;//远程端口
} s_network;

typedef struct tag_alert//报警参数	
{
    char        name[_LEN_NORMAL];
    char        note[_LEN_EXTEND];

    D_int       alert_num;//2路报警
    D_int       capture_pic_enable_1;//启用抓拍图片
    D_int       capture_pic_num_1;//图片抓拍数目
    D_int       capture_pic_interval_1;//图片抓拍间隔, 后续删除
    D_int       capture_video_enable_1;//启用录像
    D_int       capture_video_last_time_1;//录像持续时间
    D_int       alarm_enable_1;//启用警铃
    D_int       alarm_delay_1;//警铃延迟时间
    D_int       alarm_last_time_1;//警铃持续时间
    D_int       md_enable_1;//启用移动侦测
    D_int       md_sensitivity_1;//侦测敏感度（30%）
    D_string    md_area_0_1;//侦测区域（矩形）
    D_string    md_area_1_1;//侦测区域（矩形）
    D_string    md_area_2_1;//侦测区域（矩形）
    D_string    md_area_3_1;//侦测区域（矩形）
    D_week_string week_alert_plan_1;
    D_int       plan_cap_enalbe_1;// 布防时间到时，是否启动录像
    D_int       plan_cap_last_sec_1;// 录像持续秒数，0代表录像时间持续到下一个整点
    D_int       capture_pic_enable_2;//启用抓拍图片
    D_int       capture_pic_num_2;//图片抓拍数目
    D_int       capture_pic_interval_2;//图片抓拍间隔
    D_int       capture_video_enable_2;//启用录像
    D_int       capture_video_last_time_2;//录像持续时间
    D_int       alarm_enable_2;//启用警铃
    D_int       alarm_delay_2;//警铃延迟时间
    D_int       alarm_last_time_2;//警铃持续时间
    D_int       md_enable_2;//启用移动侦测
    D_int       md_sensitivity_2;//侦测敏感度（30%）
    D_string    md_area_0_2;//侦测区域（矩形）
    D_string    md_area_1_2;//侦测区域（矩形）
    D_string    md_area_2_2;//侦测区域（矩形）
    D_string    md_area_3_2;//侦测区域（矩形）
    D_week_string week_alert_plan_2;
    D_int       plan_cap_enalbe_2;// 布防时间到时，是否启动录像
    D_int       plan_cap_last_sec_2;// 录像持续秒数，0代表录像时间持续到下一个整点
} s_alert;

typedef struct tag_store//存储参数	
{
    char        name[_LEN_NORMAL];
    char        note[_LEN_EXTEND];

    D_int       sd_status;//状态，0：未插入，1：已插入
    D_int       sd_total_size;//SD卡总容量
    D_int       sd_used_size;//SD卡已使用容量，两个参数在此无意义，主要是封装在一个结构体内，sd_store_enable
    D_int       sd_store_enable;//启用SD卡存储
    D_int       auto_cover_older;//自动覆盖旧文件
    D_int       percent_alarm;// 执行告警百分比，磁盘剩余空间百分比<=percent_alarm,则进行告警瞤ercent_del
    D_int       percent_del;// 执行删除百分比，磁盘剩余空间百分比<=percent_del,则进行删除操譻ys
} s_store;

typedef struct tag_sys//系统设置	                        	
{
    char        name[_LEN_NORMAL];
    char        note[_LEN_EXTEND];

    D_string    app_version;
    D_string    app_time;
} s_sys;

typedef struct tag_rtv_start// 实时视频传输请求
{
    char        name[_LEN_NORMAL];
    char        note[_LEN_EXTEND];

    D_int       channel;// 视频信道 0, 1
} s_rtv_start;

typedef struct tag_htv_start// 录像启动请求
{
    char        name[_LEN_NORMAL];
    char        note[_LEN_EXTEND];

    D_int       channel;// 视频信道 0, 1	
} s_htv_start;

typedef struct tag_htv_end// 录像停止请求
{
    char        name[_LEN_NORMAL];
    char        note[_LEN_EXTEND];

    D_int       channel;// 视频信道 0, 1
} s_htv_end;

typedef struct tag_pic_start// 图片抓拍启动请求
{
    char        name[_LEN_NORMAL];
    char        note[_LEN_EXTEND];

    D_int       channel;// 视频信道 0, 1
    D_int       num;// 抓拍张数
} s_pic_start;

typedef struct tag_ptz_control// 云台控制请求
{
    char        name[_LEN_NORMAL];
    char        note[_LEN_EXTEND];

    D_int       channel;// 视频信道 0, 1
    D_int       left;// 向左转动  0：无操作 1：操作
    D_int       right;// 向右转动  0：无操作 1：操作
    D_int       up;// 向上转动  0：无操作 1：操作
    D_int       down;// 向下转动  0：无操作 1：操作
} s_ptz_control;

typedef struct tag_sys_quit// IPC退出请求
{
    char        name[_LEN_NORMAL];
    char        note[_LEN_EXTEND];

    D_int       flag;// 0：IPC不退出，1：IPC退出
} s_sys_quit;

typedef struct tag_log// 日志获取
{
    char        name[_LEN_NORMAL];
    char        note[_LEN_EXTEND];

    D_int       flag;// 0: 不获取日志, 1:获取日志
} s_log;

typedef struct tag_usb_remove
{
    char        name[_LEN_NORMAL];
    char        note[_LEN_EXTEND];

    D_int       channel;
} s_usb_remove;

typedef struct tag_hb// 心跳
{
    char        name[_LEN_NORMAL];
    char        note[_LEN_EXTEND];

    D_int       flag;
} s_hb;

typedef struct tag_def_config// 恢复出厂配置
{
    char        name[_LEN_NORMAL];
    char        note[_LEN_EXTEND];

    D_int       flag;
} s_def_config;

typedef struct tag_md_report
{
    char        name[_LEN_NORMAL];
    char        note[_LEN_EXTEND];

    D_int       md_area_0_0;// 0路视频第0号区域是否有移动 0：没有 1：有
    D_int       md_area_0_1;
    D_int       md_area_0_2;
    D_int       md_area_0_3;
    D_int       md_area_1_0;
    D_int       md_area_1_1;
    D_int       md_area_1_2;
    D_int       md_area_1_3;
} s_md_report;

typedef struct tag_alarm_disk// 参数都由存储参数全局变量提供
{
    char        name[_LEN_NORMAL];
    char        note[_LEN_EXTEND];

    D_int       flag;
} s_alarm_disk;

typedef struct tag_time_syn// 时间同步
{
    char        name[_LEN_NORMAL];
    char        note[_LEN_EXTEND];

    D_string    time;// 更新系统的日期，格式如下: 2008-10-12 13:14:34
} s_time_syn;

typedef struct tag_alarm_error// IPC向RTU上报严重错误消息，如录像保存时的open失败
{
    char        name[_LEN_NORMAL];
    char        note[_LEN_EXTEND];

    D_int       alarm_error_id;// 告警错误id
    D_string    alarm_error_name;
} s_alarm_error;

typedef struct tag_process_info// 获取ipc进程信息
{
    char        name[_LEN_NORMAL];
    char        note[_LEN_EXTEND];

    D_int       flag;
} s_process_info;

typedef struct tag_end
{
    char        name[_LEN_NORMAL];
    char        note[_LEN_EXTEND];

    D_int       flag;// 结束标记
}s_end;

//全局变量
typedef struct tagAllConfig
{
    s_login    login;// web登录
    s_user    user;//用户信息  
    s_video    video;//视频参数
    s_network    network;//网络参数
    s_alert    alert;//报警参数	
    s_store    store;//存储参数	
    s_sys    sys;//系统设置	                        	
    s_rtv_start    rtv_start;// 实时视频传输请求
    s_htv_start    htv_start;// 录像启动请求
    s_htv_end    htv_end;// 录像停止请求
    s_pic_start    pic_start;// 图片抓拍启动请求
    s_ptz_control    ptz_control;// 云台控制请求
    s_sys_quit    sys_quit;// IPC退出请求
    s_log    log;// 日志获取
    s_usb_remove    usb_remove;
    s_hb    hb;// 心跳
    s_def_config    def_config;// 恢复出厂配置
    s_md_report    md_report;
    s_alarm_disk    alarm_disk;// 参数都由存储参数全局变量提供
    s_time_syn    time_syn;// 时间同步
    s_alarm_error    alarm_error;// IPC向RTU上报严重错误消息，如录像保存时的open失败
    s_process_info    process_info;// 获取ipc进程信息
    s_end    end;

    int config_index;
}AllConfig;


