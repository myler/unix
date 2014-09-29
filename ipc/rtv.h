#ifndef __RTV_H__
#define __RTV_H__

#ifdef __cplusplus
#if __cplusplus
extern "C"
{
#endif
#endif

#include <sys/sem.h>
#include <sys/ipc.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <signal.h>
#include <errno.h>
#include <time.h>
#include <math.h>
#include <stdarg.h>
#include <linux/types.h>
#include <linux/videodev.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <sys/file.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <pthread.h>

#include "sem.h"
#include "logger.h"
#include "protocol.h"
#include "vs_thread.h"
#include "vs_socket.h"
#include "rtv_utils.h"
#include "jdatatype.h"
#include "marker.h"
#include "quant.h"
#include "encoder.h"
#include "huffman.h"

/* Our private ioctl */
#define SPCAGVIDIOPARAM _IOR('v',BASE_VIDIOCPRIVATE + 1,struct video_param)
#define SPCASVIDIOPARAM _IOW('v',BASE_VIDIOCPRIVATE + 2,struct video_param)

/* V4L1 extension API */
#define VIDEO_PALETTE_JPEG  21
/* in case default setting */
#define WIDTH 352
#define HEIGHT 288
#define BPPIN 8
#define OUTFRMNUMB 64//128 //16
#define BMP_BUFF_SIZE 20480
/* ITU-R-BT.601 PAL/NTSC */
#define MASQ 1
#define JPG MASQ
#define VGA MASQ
#define PAL (MASQ << 1)
#define SIF (MASQ << 2)
#define CIF (MASQ << 3)
#define QPAL (MASQ << 4)
#define QSIF (MASQ << 5)
#define QCIF (MASQ << 6)
/* fourcc palette check in preference order*/
#define JPG MASQ
#define YUV420P (MASQ << 1)
#define RGB24 (MASQ << 2)
#define RGB565 (MASQ << 3)
#define RGB32 (MASQ << 4)

extern s_syn_ctrl syn_ctrl_rtv;

struct video_param
{
    int chg_para;
#define CHGABRIGHT 1
#define CHGQUALITY 2
#define CHGTINTER  4
    __u8 autobright;
    __u8 quality;
    __u16 time_interval;
};

struct frame_t
{
    int date;
    int time;
    char header[5];
    int nbframe;
    double seqtimes;
    int deltatimes;
    int w;
    int h;
    int size;
    int format;
    unsigned short bright;
    unsigned short contrast;
    unsigned short colors;
    unsigned short exposure;
    unsigned char wakeup;
    int acknowledge;
} __attribute__ ((packed));

struct client_t
{
    char message[4];
    unsigned char x;
    unsigned char y;
    unsigned char fps;
    unsigned char updobright;
    unsigned char updocontrast;
    unsigned char updocolors;
    unsigned char updoexposure;
    unsigned char updosize;
    unsigned char sleepon;
} __attribute__ ((packed));


struct vdIn
{
    int fd;
    char *videodevice ;
    struct video_mmap vmmap;
    struct video_capability videocap;
    int mmapsize;
    struct video_mbuf videombuf;
    struct video_picture videopict;
    struct video_window videowin;
    struct video_channel videochan;
    struct video_param videoparam;
    int cameratype ;
    char *cameraname;
    char bridge[9];
    int sizenative; // available size in jpeg
    int sizeothers;	// others palette
    int palette; // available palette
    int norme ; // set spca506 usb video grabber
    int channel ; // set spca506 usb video grabber
    int grabMethod ;
    unsigned char *pFramebuffer;
    unsigned char *ptframe[OUTFRMNUMB];
    int framelock[OUTFRMNUMB];
    int ptframesize[OUTFRMNUMB];
    pthread_mutex_t grabmutex;
    int framesizeIn ;
    volatile int frame_cour;
    int bppIn;
    int  hdrwidth;
    int  hdrheight;
    int  formatIn;
    int signalquit;

	char *bmpBuffer[2];
	int bmpIndex;
};


enum {
    JPEG = 0,
    YUVY,
    YYUV,
    YUYV,
    GREY,
    GBRG,
    SN9C,
    GBGR,
    UNOW,
};

/* specific for the spca5xx webcam */
enum {
    BRIDGE_SPCA505 = 0,
    BRIDGE_SPCA506,
    BRIDGE_SPCA501,
    BRIDGE_SPCA508,
    BRIDGE_SPCA504,
    BRIDGE_SPCA500,
    BRIDGE_SPCA504B,
    BRIDGE_SPCA533,
    BRIDGE_SPCA504C,
    BRIDGE_SPCA561,
    BRIDGE_SPCA536,
    BRIDGE_SONIX,
    BRIDGE_ZR364XX,
    BRIDGE_ZC3XX,
    BRIDGE_CX11646,
    BRIDGE_TV8532,
    BRIDGE_ETOMS,
    BRIDGE_SN9CXXX,
    BRIDGE_MR97311,
    BRIDGE_UNKNOW,
    MAX_BRIDGE,
};

struct palette_list
{
    int num;
    const char *name;
};

struct bridge_list
{
    int num;
    const char *name;
};

//#define MAX_RTV_USER 4
//int g_rtv_sock[MAX_RTV_USER][2];

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif
