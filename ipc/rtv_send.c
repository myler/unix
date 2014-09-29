#ifdef __cplusplus
#if __cplusplus
extern "C"
{
#endif
#endif /* __cplusplus */

#include <fcntl.h>
#include <errno.h>

#include "rtv_send.h"
#include "rtv.h"
#include "vs_save.h"
#include "md.h"
#include "logger.h"

extern s_syn_ctrl syn_ctrl_rtv;
extern s_syn_ctrl syn_ctrl_parse;
extern s_syn_ctrl frame_syn_ctrl[2][OUTFRMNUMB];
extern struct vdIn videoIn[2];
extern int g_htv_enabled[2];
extern int g_cap_num[2];
extern int g_cache_cp_en[2];
extern pthread_mutex_t g_htv_en_mutex[2];
extern pthread_mutex_t g_cap_num_mutex[2];
extern pthread_mutex_t g_cache_cp_en_mutex[2];
extern int g_htv_interval[2];
extern int g_deling;
extern int g_dosfscking;

void ipc_setblocking(int fd)
{
    if ( fd <= 0 ) return;
    int flags = 0;
    flags = fcntl(fd, F_GETFL);
    fcntl(fd, F_SETFL, flags | ~O_NONBLOCK );

}

void ipc_setnoblocking(int fd)
{
    if ( fd <= 0 ) return;
    int flags = 0;
    flags = fcntl(fd, F_GETFL);
    fcntl(fd, F_SETFL, flags | O_NONBLOCK );
}

int rtv_send(unsigned char *buf, int buf_len, int channel)
{
    int i = 0;
    int bytes_sent;
    s_cmd_res_head cmd_res_head;
    package_cmd_res_construct_1(&cmd_res_head, CMD_ID_RTV_START_SET_RES, buf_len, 0);

    for (i = 0; i < MAX_CONNECT_TO_SERVER; i++)
    {
        if (g_rtv_sock[i][1] == channel)
        {
            bytes_sent = send(g_rtv_sock[i][0], &cmd_res_head, sizeof(s_cmd_res_head), MSG_NOSIGNAL);// | MSG_DONTWAIT);
            if (bytes_sent < 0)
            {
                logger(TLOG_NOTICE, "send cmd_req_head < 0.channel=%d", channel);
                logger(TLOG_NOTICE, "send error:%d-%s", errno, strerror(errno));
                rtv_user_end(g_rtv_sock[i][0]);
                //close(g_rtv_sock[i][0]);
                return -1;
            }
            else if (sizeof(s_cmd_res_head)-bytes_sent != 0)
            {
                logger(TLOG_NOTICE, "send cmd_req_head != 0, channel=%d", channel);
                logger(TLOG_NOTICE, "send error:%d-%s", errno, strerror(errno));
                rtv_user_end(g_rtv_sock[i][0]);
                //close(g_rtv_sock[i][0]);
                return -1;
            }

            bytes_sent = send(g_rtv_sock[i][0], buf, buf_len, MSG_NOSIGNAL); // | MSG_DONTWAIT);
            if (bytes_sent < 0)
            {
                logger(TLOG_NOTICE, "send frame buf < 0, channel=%d", channel);
                logger(TLOG_NOTICE, "send error:%d-%s", errno, strerror(errno));
                rtv_user_end(g_rtv_sock[i][0]);
                //close(g_rtv_sock[i][0]);
                return -1;
            }
            else if (buf_len - bytes_sent != 0)
            {
                logger(TLOG_NOTICE, "send frame buf != 0.channel=%d", channel);
                logger(TLOG_NOTICE, "send error:%d-%s", errno, strerror(errno));
                rtv_user_end(g_rtv_sock[i][0]);
                //close(g_rtv_sock[i][0]);
                return -1;
            }
        }
    }
    return 0;
}

int thread_rtv_send_main(int *param)
{
    int frameout = 0;
    int ret;
    int md_ret;

    int channel = *param;
    int width = 320;
    int height = 240;

    int md_interval = 12;
	int send_interval = 0;

    struct vdIn *vd = &videoIn[channel];
    while (1)
    {
        thread_syn_wait(&frame_syn_ctrl[channel][frameout].mutex_r,
                        &frame_syn_ctrl[channel][frameout].cond_r,
                        &frame_syn_ctrl[channel][frameout].flag_r);
        if (!(((channel == 0) && (!mapThreadID2Handler[THREAD_RTV_SEND_0].thread_quit_flag))
                ||((channel == 1) && (!mapThreadID2Handler[THREAD_RTV_SEND_1].thread_quit_flag))))
        {
//           logger(TLOG_NOTICE, "%s will quit.", __FUNCTION__);
            break;
        }

		send_interval --;
		if(send_interval < 0)
		{
	        ret = rtv_send((unsigned char*)(vd->ptframe[frameout]),
	                       vd->ptframesize[frameout]+sizeof(struct frame_t),
	                       channel+1);
	        if (ret != 0)
	        {
	            logger(TLOG_ERROR, "%s of channel %d send error", __FUNCTION__, channel);
	        }

			if(channel == 0){
				send_interval = g_config.video.frame_interval_1.var;
			}
			else if(channel == 1){
				send_interval = g_config.video.frame_interval_2.var;
			}
		}
		
#if 1
        md_interval --;
        if (md_interval == 0)
        {
            if (((channel == 0) && (g_config.alert.md_enable_1.var == 1))
                    ||((channel == 1) && (g_config.alert.md_enable_2.var == 1)))
            {
                //              printf("start decoder\n");
                ret = jpeg_decoder(vd->ptframe[frameout]+sizeof(struct frame_t),
                                   vd->bmpBuffer[vd->bmpIndex], vd->ptframesize[frameout]);
                //   		ret = jpeg_decode(vd->bmpBuffer[(vd->bmpIndex++)%2], vd->ptframe[frameout]+sizeof(struct frame_t), &width, &height);
                if (ret != 0)
                {
//                   printf("decoder errorRRRRRRRRRRRRRRRRRRRRRRRRRRRRR\n");
//                    continue;
                }
                else
                {
                    vd->bmpIndex = (++(vd->bmpIndex)) % 2;
                    if (channel == 0)
                    {
                        md_ret = md_detect(vd->bmpBuffer[0],vd->bmpBuffer[1],
                                           vd->hdrwidth*vd->hdrheight/64*3, g_config.alert.md_sensitivity_1.var);
                        if (md_ret == 1)
                        {
                            // pgh Ä¬ÈÏ0ºÅÇøÓòÎªÈ«ÆÁ
                            g_config.md_report.md_area_0_0.var = 1;
                            alert_send_start(2);
                            if (g_config.alert.capture_pic_enable_1.var == 1)
                            {
                                pthread_mutex_lock(&g_cap_num_mutex[channel]);
                                g_cap_num[channel] = g_config.alert.capture_pic_num_1.var;
                                pthread_mutex_unlock(&g_cap_num_mutex[channel]);

                     //           pthread_mutex_lock(&g_cache_cp_en_mutex[channel]);
                     //           g_cache_cp_en[channel] = 1;
                     //           pthread_mutex_unlock(&g_cache_cp_en_mutex[channel]);

								logger(TLOG_NOTICE, "md_detected, pic cap num %d of channel %d", g_cap_num[channel], channel);
                            }
                            if (g_config.alert.capture_video_enable_1.var == 1)
                            {
                                htv_enable(channel, 1);

								logger(TLOG_NOTICE, "md_dtected, htv start by auto of channel %d", channel);
                            }
                        }
                    }
                    else if (channel == 1)
                    {
                        md_ret = md_detect(vd->bmpBuffer[0],vd->bmpBuffer[1],
                                           vd->hdrwidth*vd->hdrheight/64*3, g_config.alert.md_sensitivity_2.var);
                        if (md_ret == 1)
                        {
                            g_config.md_report.md_area_1_0.var = 1;
                            alert_send_start(2);
                            if (g_config.alert.capture_pic_enable_2.var == 1)
                            {
                                pthread_mutex_lock(&g_cap_num_mutex[channel]);
                                g_cap_num[channel] = g_config.alert.capture_pic_num_2.var;
                                pthread_mutex_unlock(&g_cap_num_mutex[channel]);

                      //          pthread_mutex_lock(&g_cache_cp_en_mutex[channel]);
                      //          g_cache_cp_en[channel] = 1;
                      //          pthread_mutex_unlock(&g_cache_cp_en_mutex[channel]);

								logger(TLOG_NOTICE, "md_detected, pic cap num %d of channel %d", g_cap_num[channel], channel);
							}
                            if (g_config.alert.capture_video_enable_2.var == 1)
                            {
                                htv_enable(channel, 1);

								logger(TLOG_NOTICE, "md_dtected, htv start by auto of channel %d", channel);
                            }
                        }
					}
                }
            }
            md_interval = 12;
        }
#endif

        if ((ret == 0) && (g_deling == 0) && (g_dosfscking == 0))
        {
            if (1 == g_config.store.sd_store_enable.var)
            {
                // Ô¤»º´æ¿½±´
                if (1 == g_cache_cp_en[channel])
                {
                    int i;
                    for (i = 0; i < OUTFRMNUMB; i = i + 8)
                    {
                        cache_savefile((unsigned char*)(vd->ptframe[i]),vd->ptframesize[i]+sizeof(struct frame_t),
                                       channel+1, PIC_TYPE_CAP, g_config.store.percent_alarm.var, g_config.store.percent_del.var);
                    }
                    pthread_mutex_lock(&g_cache_cp_en_mutex[channel]);
                    g_cache_cp_en[channel]= 0;
                    pthread_mutex_unlock(&g_cache_cp_en_mutex[channel]);

                }

                // Â¼Ïñ
                if (g_htv_enabled[channel] > 0)
                {
                    ipc_savefile((unsigned char*)(vd->ptframe[frameout]),vd->ptframesize[frameout]+sizeof(struct frame_t),
                                 channel+1, PIC_TYPE_CAP, g_config.store.percent_alarm.var, g_config.store.percent_del.var);
                }
                // ×¥ÅÄ
                if (g_cap_num[channel] > 0)
                {
                    ipc_savefile((unsigned char*)(vd->ptframe[frameout]),vd->ptframesize[frameout]+sizeof(struct frame_t),
                                 channel+1, PIC_TYPE_CAP, g_config.store.percent_alarm.var, g_config.store.percent_del.var);
                    pthread_mutex_lock(&g_cap_num_mutex[channel]);
                    g_cap_num[channel]--;
                    pthread_mutex_unlock(&g_cap_num_mutex[channel]);
                }
            }
        }
        thread_syn_flag_clr(&frame_syn_ctrl[channel][frameout].mutex_r,
                            &frame_syn_ctrl[channel][frameout].cond_r,
                            &frame_syn_ctrl[channel][frameout].flag_r);
        thread_syn_flag_set(&frame_syn_ctrl[channel][frameout].mutex_w,
                            &frame_syn_ctrl[channel][frameout].cond_w,
                            &frame_syn_ctrl[channel][frameout].flag_w);
        frameout = (frameout+1)% OUTFRMNUMB;
    }

    logger(TLOG_NOTICE, "%s of channel %d exit.", __FUNCTION__, channel);
    return 0;
}

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */



