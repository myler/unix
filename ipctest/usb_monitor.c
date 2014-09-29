#ifdef __cplusplus
#if __cplusplus
extern "C"
{
#endif
#endif /* __cplusplus */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/un.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <linux/types.h>
#include <linux/netlink.h>
#include <errno.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#include "logger.h"
#include "vs_thread.h"
#include "vs_sd.h"

#define UEVENT_BUFFER_SIZE 2048

extern int sd_mount_ret;

static int init_hotplug_sock()
{
    const int buffersize = 1024;
    int ret;

    struct sockaddr_nl snl;
    bzero(&snl, sizeof(struct sockaddr_nl));
    snl.nl_family = AF_NETLINK;
    snl.nl_pid = getpid();
    snl.nl_groups = 1;

    int s = socket(PF_NETLINK, SOCK_DGRAM, NETLINK_KOBJECT_UEVENT);
    if (s == -1)
    {
        perror("socket");
        return -1;
    }
    setsockopt(s, SOL_SOCKET, SO_RCVBUF, &buffersize, sizeof(buffersize));

    ret = bind(s, (struct sockaddr *)&snl, sizeof(struct sockaddr_nl));
    if (ret < 0)
    {
        perror("bind");
        close(s);
        return -1;
    }

    return s;
}

int thread_usb_monitor_main()
{
//	logger(TLOG_NOTICE, "thread %s id %d\n", __FUNCTION__, getpid());
    int channel_0 = 0;
    int channel_1 = 1;
    char buf[UEVENT_BUFFER_SIZE];
    int recv_bytes;
    int ret;

    int hotplug_sock = init_hotplug_sock();
    while ( !mapThreadID2Handler[THREAD_USB_MONITOR].thread_quit_flag )
    {
        memset(buf, 0, UEVENT_BUFFER_SIZE);
        recv_bytes = recv(hotplug_sock, &buf, sizeof(buf), 0);
//		logger(TLOG_NOTICE, "usb monitor: %s\n", buf);
        if (buf[0] == 'r') 		//remove
        {
            if (buf[8] == 'c') 		//usb camera
            {
                if (buf[31] == '0')
                {
                    logger(TLOG_NOTICE, "remove usb video0.\n");
                    mapThreadID2Handler[THREAD_RTV_0].thread_quit_flag = 1;
                }
                else if (buf[31] == '1')
                {
                    logger(TLOG_NOTICE, "remove usb video1.\n");
                    mapThreadID2Handler[THREAD_RTV_1].thread_quit_flag = 1;
                }
            }
            else if (buf[8] == 'b' && buf[25] == 'b') 	//sd card
            {
	            logger(TLOG_NOTICE, "detecetd sd card remove");
                if(sd_umount(10) == 0){
					dir_constrcut();
					logger(TLOG_NOTICE, "usb_monitor:sd card umount success");
				}
            }
        }
        else if (buf[0] == 'a') 		//add
        {
            if (buf[5] == 'c') 		//usb camera
            {
                if (buf[28] == '0')
                {
                    logger(TLOG_NOTICE, "add video0.\n");
                    rtv_syn_init(0);
                    ret = vs_thread_create(THREAD_RTV_0, &channel_0);
                    ret = vs_thread_create(THREAD_RTV_SEND_0, &channel_0);
                    if (ret!=0)
                    {
                        logger(TLOG_ERROR, "start rtv channel 0 failed.\n");
                    }
                }
                else if (buf[28] == '1')
                {
                    logger(TLOG_NOTICE, "add video1.\n");
                    rtv_syn_init(1);
                    ret = vs_thread_create(THREAD_RTV_1, &channel_1);
                    ret = vs_thread_create(THREAD_RTV_SEND_1, &channel_1);
                    if (ret!=0)
                    {
                        logger(TLOG_ERROR, "start rtv channel 1 failed.\n");
                    }
                }
            }
            else if (buf[5] == 'b' && buf[22] == 'b') 	//sd card
            {
            	logger(TLOG_NOTICE, "detecetd sd card insert");
				if(sd_mount(10) == 0){
					dir_constrcut();
					logger(TLOG_NOTICE, "usb_monitor:sd card mount success");
				}
            }
        }
/*		
		else if (buf[0] == 'm') 			//mount
        {
            logger(TLOG_NOTICE, "usb monitor :mount success\n");
//            sd_mount_ret = 1;
			sd_status_set();
        }
		else if (buf[0] == 'u')
		{
			sd_status_clr();
		}
*/		
        else
        {
//            logger(TLOG_NOTICE, "%d-%s\n", recv_bytes, buf);
        }
//		logger(TLOG_NOTICE, "%d-%s\n", recv_bytes, buf);
    }
    return 0;
}


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

