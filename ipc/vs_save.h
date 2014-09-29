#ifndef __VS_SAVE_H__
#define __VS_SAVE_H__


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

#include <stdio.h>
#include <time.h>

#define ROOT_SD                 "/ipc/ipc_data"
#define ROOT_HD                 "/"

#define DIR_ROOT_FTP            "/ipc/ipc_data/"        // ftp根目录               
#define DIR_HTV                 "htv/"              // 历史视频根目录
#define DIR_PIC                 "pic/"              // 抓拍图片根目录
#define EXT_NAME                ".jpg"              // 图片文件扩展名
#define PIC_TYPE_HTV                    0
#define PIC_TYPE_CAP                    1

typedef struct tagGSaveAllData
{
    char        save_cap_base_folder[256];        // 保存图片的基本目录
    long        delete_min_space;   // 最小删除的空间
    int         delete_min_percent; // 最小删除的磁盘百分比

    int         auto_delete_cap_day;    // 自动删除多少天前的图片文件
    int         is_auto_delete;         // 是否自动删除
} GSaveAllData;

int ipc_savefile(char *buf, int len, int channel, int pic_type, int percent_alarm, int percent_del);
int xx_space_get(long *size_useable, long *size_sum, int *percent_useable);
int dir_constrcut();
#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __VS_SAVE_H__ */


/* --------------------------------------------------------
设想一下录像，需要些什么样的参数控制
[save_video_param]
A. 针对所有摄像头
save_camera_type = "1230"      // 哪些采取什么方案
   // 0: 表示不保存 1,2,3分别表示方案1,2,3

[save_video_param_0]
[save_video_param_1]
[save_video_param_2]
[save_video_param_3]
B. 针对某个摄像头

方案1：
    开机即录像。
方案2：
    每天定点开始录像，每次录一定时间. 分为4个时间点
    同时，设好是周几的那一天。
方案3：
    计划好整点录像,每个小时判断一次，每次一个小时.有点像布防时间
针对报警：
    报警时的参数，待定

定义参数如下：
// 当方案1时，不用特别参数

// 当方案2时
save_week = "0101010"  // 周几有效
save_hour1 = "10:15:30" // 每天的定点时间
save_hour2 = "10:15:30" // 每天的定点时间
save_hour2 = "10:15:30" // 每天的定点时间
save_hour3 = "10:15:30" // 每天的定点时间
save_timelen = 60      // 存多少秒

// 当方案3时
save_allweek = "1100100010101010100101010100101010101001010101011001" //每周的周计划，整点布防





-------------------------------------------------------- */







