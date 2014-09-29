#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

#include <stdio.h>
#include <semaphore.h>
#include <signal.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/reboot.h>
#include <errno.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/wait.h>

#include "vs_thread.h"
#include "vs_socket.h"
#include "config.h"
#include "vs_sd.h"
#include "sem.h"
#include "logger.h"
#include "rtv.h"
#include "timer_handler.h"
#include "vs_save.h"

extern pthread_t    threadID[THREAD_NUM_MAX];

pid_t               main_pid = -1;

s_syn_ctrl          syn_ctrl_sys;
s_syn_ctrl          syn_ctrl_parse;
s_syn_ctrl          syn_ctrl_rtv;
s_syn_ctrl          syn_ctrl_alarm;
s_syn_ctrl          syn_ctrl_del;
s_syn_ctrl          syn_ctrl_watchdog;
s_syn_ctrl          syn_ctrl_dosfsck;

struct vdIn         videoIn[2];
s_syn_ctrl          frame_syn_ctrl[2][OUTFRMNUMB];

int                 channel_0 = 0;
int                 channel_1 = 1;
int                 sd_mount_ret;

int                 main_core();
int                 ipc_init();
int                 thread_start();
void                rtv_syn_init(int channel);

int
main(void)
{
    logger(TLOG_NOTICE, "IPC start now");

    while (1) {
        if ((main_pid = fork()) < 0) {
            logger(TLOG_ERROR, "Unable to fork!");
            exit(1);
        } else if (main_pid == 0) {
            main_core();
            return 0;
        } else {
            int      status;
            int      n;

            if ((n = waitpid(main_pid, &status, 0)) == -1) {
                logger(TLOG_ERROR, "Waitpid error : %s", strerror(errno));
                exit(1);
            }
            if (WEXITSTATUS(status) == 1) {
                logger(TLOG_WARNING, "child process return 1");
                return 0;
            } else
                logger(TLOG_WARNING, "child process return 0");
        }
    }
    return 0;
}

int
main_core(void)
{
    logger(TLOG_NOTICE, "IPC core begin to run");

    int ret;
    if ((ret = ipc_init()) != 0) {
        logger(TLOG_ERROR, "ipc init failed, ipc core closed.");
        return -1;
    }

    if ((ret = thread_start()) != 0) {
        logger(TLOG_ERROR, "thread create failed, ipc core closed.");
        return -1;
    }

    sd_init(10);
    dir_constrcut();

    thread_syn_wait(&syn_ctrl_sys.mutex_r, &syn_ctrl_sys.cond_r, &syn_ctrl_sys.flag_r);
    logger(TLOG_NOTICE, "all threads finished, ipc core closed.");

    if(1 == g_config.sys_quit.flag.var) {
        logger(TLOG_WARNING, "ipc core exit 1, ipc exit normal");
        exit(1);
    }
    else {
        logger(TLOG_WARNING, "ipc core exit 0, ipc exit error, ipc will restart");
        exit(0);
    }
}

int
ipc_init()
{
    int j;

    if (config_read("/etc/ipc.conf") != 0)
    {
        logger(TLOG_ERROR, "configure file load failed.\n");
        return -1;
    }
    thread_syn_init(&syn_ctrl_parse.mutex_r, &syn_ctrl_parse.cond_r, &syn_ctrl_parse.flag_r);
    thread_syn_init(&syn_ctrl_sys.mutex_r, &syn_ctrl_sys.cond_r, &syn_ctrl_sys.flag_r);
    thread_syn_init(&syn_ctrl_rtv.mutex_r, &syn_ctrl_rtv.cond_r, &syn_ctrl_rtv.flag_r);
    thread_syn_init(&syn_ctrl_alarm.mutex_r, &syn_ctrl_alarm.cond_r, &syn_ctrl_alarm.flag_r);
    thread_syn_init(&syn_ctrl_del.mutex_r, &syn_ctrl_del.cond_r, &syn_ctrl_del.flag_r);
    thread_syn_init(&syn_ctrl_watchdog.mutex_r, &syn_ctrl_watchdog.cond_r, &syn_ctrl_watchdog.flag_r);
    thread_syn_init(&syn_ctrl_dosfsck.mutex_r, &syn_ctrl_dosfsck.cond_r, &syn_ctrl_dosfsck.flag_r);

    for (j = 0; j < 2; j++)
    {
        rtv_syn_init(j);
    }
    timer_init();

    return 0;
}

int
thread_start()
{
    int ret = 0;

    if ((ret = vs_thread_create(THREAD_SOCKET, NULL)) != 0)
        return ret;
    if ((ret = vs_thread_create(THREAD_PARSER, NULL)) != 0)
        return ret;
    if ((ret = vs_thread_create(THREAD_USB_MONITOR, NULL)) != 0)
        return ret;
    if ((ret = vs_thread_create(THREAD_CGI, NULL)) != 0)
        return ret;
    if ((ret = vs_thread_create(THREAD_RTV_SEND_0, &channel_0)) != 0)
        return ret;
    if ((ret = vs_thread_create(THREAD_ALERT_SEND, NULL)) != 0)
        return ret;
    if ((ret = vs_thread_create(THREAD_FILE_DEL, NULL)) != 0)
        return ret;
    if ((ret = vs_thread_create(THREAD_WATCHDOG, NULL)) != 0)
        return ret;
    if ((ret = vs_thread_create(THREAD_DOSFSCK, NULL)) != 0)
        return ret;
    if ((ret = vs_thread_create(THREAD_RTV_0, &channel_0)) != 0)
        return ret;
    if ((ret = vs_thread_create(THREAD_RTV_1, &channel_1)) != 0)
        return ret;

    return ret;
}

void
rtv_syn_init(int channel)
{
    int i;
    for (i = 0; i < OUTFRMNUMB; i++) {
        thread_syn_init(&frame_syn_ctrl[channel][i].mutex_r,
                        &frame_syn_ctrl[channel][i].cond_r,
                        &frame_syn_ctrl[channel][i].flag_r);
        thread_syn_init(&frame_syn_ctrl[channel][i].mutex_w,
                        &frame_syn_ctrl[channel][i].cond_w,
                        &frame_syn_ctrl[channel][i].flag_w);
    }
}

#ifdef __cplusplus
}
#endif /* __cplusplus */
