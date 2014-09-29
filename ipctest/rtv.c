#ifdef __cplusplus
#if __cplusplus
extern "C"
{
#endif
#endif /* __cplusplus */

#include <fcntl.h>

#include "rtv.h"
#include "rtv_utils.h"
#include "jdatatype.h"
#include "encoder.h"
#include "tcputils.h"
#include "logger.h"
#include "watchdog.h"

extern s_syn_ctrl syn_ctrl_rtv;
extern s_syn_ctrl syn_ctrl_watchdog;
extern s_watchdog_event   g_watchdog_event[ID_EVENT_BUTT];

extern s_syn_ctrl frame_syn_ctrl[2][OUTFRMNUMB];
extern struct vdIn videoIn[2];

extern int channel_0;
extern int channel_1;

extern pthread_t threadID[THREAD_NUM_MAX];

//extern struct vdIn videoIn;
//extern struct vdIn *vd;
int fd = 0;

// 置非0，则保存相应channel的视频，请求包括整点录像和手动录像，没有录像 0, 自动录像 1, 手动录像2
// 手动录像级别最高，即如果当前已经为手动录像，则不理睬自动录像
int g_htv_enabled[2] = {0, 0};
int g_cap_num[2] = {0, 0};              // 分别代表两路视频
int g_cache_cp_en[2] = {0, 0};					// 缓存拷贝使能
int g_htv_interval[2] = {5, 5};					// 录像保存间隔图片张数，用来减少保存次数，否则cpu使用率很高

pthread_mutex_t g_htv_en_mutex[2];
pthread_mutex_t g_cap_num_mutex[2];
pthread_mutex_t g_cache_cp_en_mutex[2];

static int init_v4l (struct vdIn *vd, int channel);
static int checkpalette (struct vdIn *vd);
static int check_palettesize(struct vdIn *vd );

static struct bridge_list Blist[]={

    {BRIDGE_SPCA505,"SPCA505"},
    {BRIDGE_SPCA506,"SPCA506"},
    {BRIDGE_SPCA501,"SPCA501"},
    {BRIDGE_SPCA508,"SPCA508"},
    {BRIDGE_SPCA504,"SPCA504"},
    {BRIDGE_SPCA500,"SPCA500"},
    {BRIDGE_SPCA504B,"SPCA504B"},
    {BRIDGE_SPCA533,"SPCA533"},
    {BRIDGE_SPCA504C,"SPCA504C"},
    {BRIDGE_SPCA561,"SPCA561"},
    {BRIDGE_SPCA536,"SPCA536"},
    {BRIDGE_SONIX,"SN9C102"},
    {BRIDGE_ZR364XX,"ZR364XX"},
    {BRIDGE_ZC3XX,"ZC301-2"},
    {BRIDGE_CX11646,"CX11646"},
    {BRIDGE_TV8532,"TV8532"},
    {BRIDGE_ETOMS,"ET61XX51"},
    {BRIDGE_SN9CXXX,"SN9CXXX"},
    {BRIDGE_MR97311,"MR97311"},
    {BRIDGE_UNKNOW,"UNKNOW"},
    {-1,NULL}
};


/* Camera type jpeg yuvy yyuv yuyv grey gbrg*/
/*
static struct palette_list Plist[] ={
    {JPEG,"JPEG"},
    {YUVY,"YUVY"},
    {YYUV,"YYUV"},
    {YUYV,"YUYV"},
    {GREY,"GREY"},
    {GBRG,"GBRG"},
    {SN9C,"SN9C"},
    {GBGR,"GBGR"},
    {UNOW,"UNOW"},
    {-1,NULL}
};
*/

/****************************************************************************
*			Public
****************************************************************************/
// mode 为录像启动模式:1,自动， 2 手动
int htv_enable(int channel, int mode)
{
    if ((channel != 0) && (channel != 1))
        return -1;
    if ((mode != 1)&&(mode != 2))
        return -1;

    pthread_mutex_lock(&g_htv_en_mutex[channel]);
    if (2 != g_htv_enabled[channel])
    {
        g_htv_enabled[channel] = mode;
    }
//	logger(TLOG_NOTICE, "htv_enable channel:%d, htv_en:%d\n", channel, g_htv_enabled[channel]);
    pthread_mutex_unlock(&g_htv_en_mutex[channel]);


    pthread_mutex_lock(&g_cache_cp_en_mutex[channel]);
    if (0 == g_htv_enabled[channel])
        g_cache_cp_en[channel] = 1;
    pthread_mutex_unlock(&g_cache_cp_en_mutex[channel]);

    return 0;
}

int htv_disable(int channel, int mode)
{
    if ((channel != 0) && (channel != 1))
        return -1;
    if ((mode != 1)&&(mode != 2))
        return -1;

    pthread_mutex_lock(&g_htv_en_mutex[channel]);
    if (2 == mode)
        g_htv_enabled[channel]= 0;
    if (1 == mode)
    {
        if (1 == g_htv_enabled[channel])
            g_htv_enabled[channel]= 0;
    }

//	logger(TLOG_NOTICE, " htv_disable ::::g_htv_enabled[%d]=%d\n", channel, g_htv_enabled[channel]);
    pthread_mutex_unlock(&g_htv_en_mutex[channel]);
    return 0;
}

/* 对指定channel设置抓拍张数，
实时视频发送线程每次发送前检查各个channel的抓拍张数，如果不为0，则进行图片本地保存。
保存后将此抓拍张数-1,
直到num减为0,则不再进行抓拍。
注意，发送线程判断num数值的时候，消息解析线程不能对该num数值进行改变。pghpgh, 加入互斥机制。
pghpgh, 今后优化可将图片保存独立为线程
*/
int cap_enable(int chn, int num)
{
    if ((chn != 0) && (chn != 1))
        return -1;
    pthread_mutex_lock(&g_cap_num_mutex[chn]);
    g_cap_num[chn] = num;
    pthread_mutex_unlock(&g_cap_num_mutex[chn]);
    pthread_mutex_lock(&g_cache_cp_en_mutex[chn]);
    g_cache_cp_en[chn] = 1;
    pthread_mutex_unlock(&g_cache_cp_en_mutex[chn]);
    return 0;
}


int
init_videoIn (struct vdIn *vd, char *device, int width, int height,
              int format, int grabmethod, int channel)
{
    int err = 0;
    int i;
    if (vd == NULL || device == NULL)
        return -1;
    if (width == 0 || height == 0)
        return -1;
    if (grabmethod < 0 || grabmethod > 1)
        grabmethod = 1; //read by default;
    // check format
    vd->videodevice = NULL;
    vd->cameraname = NULL;
    vd->videodevice = NULL;
    vd->videodevice = (char *) realloc (vd->videodevice, 16); // pghpgh
    vd->cameraname = (char *) realloc (vd->cameraname, 32);
    
    snprintf (vd->videodevice, 12, "%s", device);
//    logger(TLOG_NOTICE, "video %s \n",vd->videodevice);
    memset (vd->cameraname, 0, sizeof (vd->cameraname));
    memset(vd->bridge, 0, sizeof(vd->bridge));
    vd->signalquit = 1;
    vd->hdrwidth = width;
    vd->hdrheight = height;
    /*          compute the max frame size   */
    vd->formatIn = format;
    vd->bppIn = GetDepth (vd->formatIn);
    vd->grabMethod = grabmethod;		//mmap or read
    vd->pFramebuffer = NULL;
    /* init and check all setting */
    if (init_v4l (vd, channel) == -1)
    {
        logger(TLOG_ERROR, "v4l init failed");
        return -1;
    }

    /* allocate the 4 frames output buffer */
    for (i = 0; i < OUTFRMNUMB; i++)
    {
        vd->ptframe[i] = NULL;
        vd->ptframe[i] =
            (unsigned char *) realloc (vd->ptframe[i], sizeof(struct frame_t) + (size_t) vd->framesizeIn );
        vd->framelock[i] = 0;
    }

//	printf("ddddddddddddddd%d\n", (size_t)vd->framesizeIn);
	
	vd->bmpBuffer[0] = (char *)realloc(vd->bmpBuffer[0], BMP_BUFF_SIZE);
	vd->bmpBuffer[1] = (char *)realloc(vd->bmpBuffer[1], BMP_BUFF_SIZE);

    
	
	vd->bmpIndex = 0;
	
    vd->frame_cour = 0;
    for (i = 0; i < OUTFRMNUMB; i++)
    {
        thread_syn_flag_set(&frame_syn_ctrl[channel][i].mutex_w,
                            &frame_syn_ctrl[channel][i].cond_w,
                            &frame_syn_ctrl[channel][i].flag_w);
        thread_syn_flag_clr(&frame_syn_ctrl[channel][i].mutex_r,
                            &frame_syn_ctrl[channel][i].cond_r,
                            &frame_syn_ctrl[channel][i].flag_r);
    }
    pthread_mutex_init (&vd->grabmutex, NULL);
    return err;
}

int
close_v4l (struct vdIn *vd)
{
    int i;
    if (vd->grabMethod)
    {
        logger(TLOG_NOTICE, "unmapping frame buffer");
        munmap (vd->pFramebuffer, vd->mmapsize);
    }
    else
    {
        free(vd->pFramebuffer);
        vd->pFramebuffer = NULL;
    }
    logger(TLOG_NOTICE, "close video_device");
    close (vd->fd);
    /* dealloc the whole buffers */
    if (vd->videodevice)
    {
        free (vd->videodevice);
        vd->videodevice = NULL;
    }
    if (vd->cameraname)
    {
        free (vd->cameraname);
        vd->cameraname = NULL;
    }
    for (i = 0; i < OUTFRMNUMB; i++)
    {
        if (vd->ptframe[i])
        {
            free (vd->ptframe[i]);
            vd->ptframe[i] = NULL;
            vd->framelock[i] = 0;
//            printf ("freeing output buffer %d\n",i);
        }
    }
	logger(TLOG_NOTICE, "free output buffer");
    pthread_mutex_destroy (&vd->grabmutex);
    pthread_mutex_destroy(&g_htv_en_mutex[0]);
    pthread_mutex_destroy(&g_htv_en_mutex[1]);
    pthread_mutex_destroy(&g_cache_cp_en[0]);
    pthread_mutex_destroy(&g_cache_cp_en[1]);
    pthread_mutex_destroy(&g_cap_num_mutex[0]);
    pthread_mutex_destroy(&g_cap_num_mutex[1]);

	return 0;
}

int
convertframe(unsigned char *dst,unsigned char *src, int width,int height, int formatIn, int qualite)
{
//    int i;
//    unsigned char tmp;
    int jpegsize =0;
    switch (formatIn)
    {
    case VIDEO_PALETTE_JPEG:
        jpegsize = get_jpegsize(src, width*height);
        if (jpegsize > 0)
            memcpy(dst,src,jpegsize);
        break;
    case VIDEO_PALETTE_YUV420P:
        jpegsize = encode_image(src,dst,qualite,YUVto420,width,height);
        break;
    case VIDEO_PALETTE_RGB24:
        jpegsize = encode_image(src,dst,qualite,RGBto420,width,height);
        break;
    case VIDEO_PALETTE_RGB565:
        jpegsize = encode_image(src,dst,qualite,RGB565to420,width,height);
        break;
    case VIDEO_PALETTE_RGB32:
        jpegsize = encode_image(src,dst,qualite,RGB32to420,width,height);
        break;
    default:
        break;
    }
    return jpegsize;
}

int frame_time( int *yymmdd, int *hhmmss )
{
    time_t timep;
    struct tm *p;
    time(&timep);
    p=gmtime(&timep);


    *yymmdd = (1900+p->tm_year) * 10000 + (1 + p->tm_mon) * 100 + p->tm_mday;
    *hhmmss = p->tm_hour * 10000 + p->tm_min * 100 + p->tm_sec;

    return 0;
}

int
v4lGrab (struct vdIn *vd, int channel )
{
//    static	int frame = 0;

//    int len;
//    int status;
//    int count = 0;
//    int size;
    int erreur = 0;
    int jpegsize = 0;
    int qualite = 1024;
    struct frame_t *headerframe;
//    double timecourant =0;
//    double temps = 0;
//  timecourant = ms_time();
    if (vd->grabMethod)
    {

        vd->vmmap.height = vd->hdrheight;
        vd->vmmap.width = vd->hdrwidth;
        vd->vmmap.format = vd->formatIn;
//            logger(TLOG_NOTICE, "channel:%d step 1.\n", channel);
        if (ioctl (vd->fd, VIDIOCSYNC,&vd->vmmap.frame) < 0)
        {
            logger(TLOG_ERROR, "rtv cvsync err\n");
            erreur = -1;
        }

        thread_syn_wait(&frame_syn_ctrl[channel][vd->frame_cour].mutex_w,
                        &frame_syn_ctrl[channel][vd->frame_cour].cond_w,
                        &frame_syn_ctrl[channel][vd->frame_cour].flag_w);
        //         logger(TLOG_NOTICE, "channel:%d step 3.\n", channel);
        jpegsize= convertframe(vd->ptframe[vd->frame_cour]+ sizeof(struct frame_t),
                               vd->pFramebuffer + vd->videombuf.offsets[vd->vmmap.frame],
                               vd->hdrwidth,vd->hdrheight,vd->formatIn,qualite);
        vd->ptframesize[vd->frame_cour] = ((jpegsize < 0)?0:jpegsize);

        headerframe=(struct frame_t*)vd->ptframe[vd->frame_cour];
//        snprintf(headerframe->header,5,"%s","SPCA");
//        headerframe->seqtimes = ms_time();
        frame_time(&(headerframe->date), &(headerframe->time));
//        headerframe->deltatimes=(int)(headerframe->seqtimes-timecourant);
        headerframe->w = vd->hdrwidth;
        headerframe->h = vd->hdrheight;
        headerframe->size = (( jpegsize < 0)?0:jpegsize);
        headerframe->format = vd->formatIn;
//        headerframe->nbframe = frame++;
        //       logger(TLOG_NOTICE, "channel:%d step 4.\n", channel);
        thread_syn_flag_clr(&frame_syn_ctrl[channel][vd->frame_cour].mutex_w,
                            &frame_syn_ctrl[channel][vd->frame_cour].cond_w,
                            &frame_syn_ctrl[channel][vd->frame_cour].flag_w);
        thread_syn_flag_set(&frame_syn_ctrl[channel][vd->frame_cour].mutex_r,
                            &frame_syn_ctrl[channel][vd->frame_cour].cond_r,
                            &frame_syn_ctrl[channel][vd->frame_cour].flag_r);
        // logger(TLOG_NOTICE, "compress frame %d times %f\n",frame, headerframe->seqtimes-temps);
//	pthread_mutex_unlock (&vd->grabmutex);
        /************************************/
        //        logger(TLOG_NOTICE, "channel:%d step 5.\n", channel);
        if ((ioctl (vd->fd, VIDIOCMCAPTURE, &(vd->vmmap))) < 0)
        {
            logger(TLOG_ERROR, "rtv cmcapture err\n");
            erreur = -1;
        }
        vd->vmmap.frame = (vd->vmmap.frame + 1) % vd->videombuf.frames;
        vd->frame_cour = (vd->frame_cour +1) % OUTFRMNUMB;
        //         logger(TLOG_NOTICE, "channel:%d step 6.\n", channel);
        //logger(TLOG_NOTICE, "frame nb %d\n",vd->vmmap.frame);

    }
#if 0
    else
    {
        /* read method */
        size = vd->framesizeIn;
        len = read (vd->fd, vd->pFramebuffer, size);
        if (len <= 0 )
        {
            printf ("v4l read error\n");
            printf ("len %d asked %d \n", len, size);
            return 0;
        }
        /* Is there someone using the frame */
        while ((vd->framelock[vd->frame_cour] != 0)&& vd->signalquit)
            usleep(1000);
        pthread_mutex_lock (&vd->grabmutex);
        /*
         memcpy (vd->ptframe[vd->frame_cour]+ sizeof(struct frame_t), vd->pFramebuffer, vd->framesizeIn);
         jpegsize =jpeg_compress(vd->ptframe[vd->frame_cour]+ sizeof(struct frame_t),len,
         vd->pFramebuffer, vd->hdrwidth, vd->hdrheight, qualite);
         */
        temps = ms_time();
        jpegsize= convertframe(vd->ptframe[vd->frame_cour]+ sizeof(struct frame_t),
                               vd->pFramebuffer ,
                               vd->hdrwidth,vd->hdrheight,vd->formatIn,qualite);
        headerframe=(struct frame_t*)vd->ptframe[vd->frame_cour];
        snprintf(headerframe->header,5,"%s","SPCA");
        headerframe->seqtimes = ms_time();
        headerframe->deltatimes=(int)(headerframe->seqtimes-timecourant);
        headerframe->w = vd->hdrwidth;
        headerframe->h = vd->hdrheight;
        headerframe->size = (( jpegsize < 0)?0:jpegsize);;
        headerframe->format = vd->formatIn;
        headerframe->nbframe = frame++;
        //  printf("compress frame %d times %f\n",frame, headerframe->seqtimes-temps);
        vd->frame_cour = (vd->frame_cour +1) % OUTFRMNUMB;
        pthread_mutex_unlock (&vd->grabmutex);
        /************************************/

    }
#endif

    return erreur;
}

/*****************************************************************************
* 				Private
******************************************************************************/
static int
GetVideoPict (struct vdIn *vd)
{
    if (ioctl (vd->fd, VIDIOCGPICT, &vd->videopict) < 0)
    {
        logger(TLOG_ERROR, "Couldnt get videopict params with VIDIOCGPICT");
        return -1;
    }

    /*
      printf ("VIDIOCGPICT brightnes=%d hue=%d color=%d contrast=%d whiteness=%d"
    	  "depth=%d palette=%d\n", vd->videopict.brightness,
    	  vd->videopict.hue, vd->videopict.colour, vd->videopict.contrast,
    	  vd->videopict.whiteness, vd->videopict.depth,
    	  vd->videopict.palette);
    */
    return 0;
}

static int
SetVideoPict (struct vdIn *vd)
{
    if (ioctl (vd->fd, VIDIOCSPICT, &vd->videopict) < 0)
    {
        logger(TLOG_ERROR, "Couldnt set videopict params with VIDIOCSPICT");
        return -1;
    }

//    printf ("VIDIOCSPICT brightnes=%d hue=%d color=%d contrast=%d whiteness=%d"
//            "depth=%d palette=%d\n", vd->videopict.brightness,
//            vd->videopict.hue, vd->videopict.colour, vd->videopict.contrast,
//            vd->videopict.whiteness, vd->videopict.depth,
//            vd->videopict.palette);

    return 0;
}

static void spcaPrintParam (int fd,struct video_param *videoparam);
static void spcaSetTimeInterval(int fd, struct video_param *videoparam, unsigned short time);
static void spcaSetQuality(int fd, struct video_param *videoparam, unsigned char index);

static int
init_v4l (struct vdIn *vd, int channel)
{
    int f;
    int erreur = 0;
    int err;
//    int flags = 0;
    if ((vd->fd = open (vd->videodevice, O_RDWR)) == -1)
    {
        logger(TLOG_ERROR, "ERROR opening V4L interface");
        return -1;
    }

//	flags = fcntl(vd->fd, F_GETFL);
//    fcntl(vd->fd, F_SETFL, flags | O_NONBLOCK );

    if (ioctl (vd->fd, VIDIOCGCAP, &(vd->videocap)) == -1)
    {
        logger(TLOG_ERROR, "Couldn't get videodevice capability");
        return -1;
    }

    logger(TLOG_NOTICE, "Camera found: %s at channel %d", vd->videocap.name, channel);
    snprintf (vd->cameraname, 32, "%s", vd->videocap.name);

    erreur = GetVideoPict (vd);
    if (ioctl (vd->fd, VIDIOCGCHAN, &vd->videochan) == -1)
    {
        printf ("Hmm did not support Video_channel\n");
        vd->cameratype = UNOW;
    }
    else
    {
        if (vd->videochan.name)
        {
//            printf ("Bridge found: %s \n", vd->videochan.name);
            snprintf (vd->bridge, 9, "%s", vd->videochan.name);
            vd->cameratype = GetStreamId (vd->videochan.name);
            spcaPrintParam (vd->fd,&vd->videoparam);
        }
        else
        {
            printf ("Bridge not found not a spca5xx Webcam Probing the hardware !!\n");
            vd->cameratype = UNOW;
        }
    }
//    printf ("StreamId: %d  Camera\n", vd->cameratype);
    /* probe all available palette and size */
    if (probePalette(vd ) < 0)
    {
        logger(TLOG_ERROR, "could't probe video palette Abort !");
        return -1;
    }
    if (probeSize(vd ) < 0)
    {
        logger(TLOG_ERROR, "could't probe video size Abort !");
        return -1;
    }

//
//  vd->formatIn = 21;
//

    /* now check if the needed setting match the available
    	if not find a new set and populate the change */
    err = check_palettesize(vd);
    logger(TLOG_NOTICE, " Format asked %d at channel %d",vd->formatIn, channel);

    vd->videopict.palette = vd->formatIn;
    vd->videopict.depth = GetDepth (vd->formatIn);

//
    if (channel == 0)
    {
        vd->videopict.brightness = g_config.video.bright_1.var << 8;
        vd->videopict.contrast = g_config.video.contrast_1.var << 8;
    }
    else if (channel == 1)
    {
        vd->videopict.brightness = g_config.video.bright_2.var << 8;
        vd->videopict.contrast = g_config.video.contrast_2.var << 8;
    }

//

    vd->bppIn = GetDepth (vd->formatIn);

    vd->framesizeIn = (vd->hdrwidth * vd->hdrheight * vd->bppIn) >> 3;

    erreur = SetVideoPict (vd);
    erreur = GetVideoPict (vd);
    if (vd->formatIn != vd->videopict.palette ||
            vd->bppIn != vd->videopict.depth)
    {
        logger(TLOG_ERROR, "could't set video palette Abort !");
        return -1;
    }
    if (erreur < 0)
    {
        logger(TLOG_ERROR, "could't set video palette Abort !");
        return -1;
    }

    if (vd->grabMethod)
    {
        logger(TLOG_NOTICE, " Grabbing method default MMAP asked at channel %d", channel);
        // MMAP VIDEO acquisition
        memset (&(vd->videombuf), 0, sizeof (vd->videombuf));
        if (ioctl (vd->fd, VIDIOCGMBUF, &(vd->videombuf)) < 0)
        {
            perror (" init VIDIOCGMBUF FAILED\n");
        }
//        printf ("VIDIOCGMBUF size %d  frames %d  offets[0]=%d offsets[1]=%d\n",
//                vd->videombuf.size, vd->videombuf.frames,
//                vd->videombuf.offsets[0], vd->videombuf.offsets[1]);
        vd->pFramebuffer =
            (unsigned char *) mmap (0, vd->videombuf.size, PROT_READ | PROT_WRITE,
                                    MAP_SHARED, vd->fd, 0);
        vd->mmapsize = vd->videombuf.size;
        vd->vmmap.height = vd->hdrheight;
        vd->vmmap.width = vd->hdrwidth;
        vd->vmmap.format = vd->formatIn;
        for (f = 0; f < vd->videombuf.frames; f++)
        {
            vd->vmmap.frame = f;
            if (ioctl (vd->fd, VIDIOCMCAPTURE, &(vd->vmmap)))
            {
                perror ("cmcapture");
            }
        }
        vd->vmmap.frame = 0;
    }
    else
    {
        /* read method */
        /* allocate the read buffer */
        vd->pFramebuffer =
            (unsigned char *) realloc (vd->pFramebuffer, (size_t) vd->framesizeIn);
        printf (" grabbing method READ asked \n");
        if (ioctl (vd->fd, VIDIOCGWIN, &(vd->videowin)) < 0)
            perror ("VIDIOCGWIN failed \n");
        vd->videowin.height = vd->hdrheight;
        vd->videowin.width = vd->hdrwidth;
        if (ioctl (vd->fd, VIDIOCSWIN, &(vd->videowin)) < 0)
            perror ("VIDIOCSWIN failed \n");
        printf ("VIDIOCSWIN height %d  width %d \n",
                vd->videowin.height, vd->videowin.width);
    }
    vd->frame_cour = 0;
    return erreur;
}
static
int probePalette ( struct vdIn *vd )
{	/* probe palette and set a default one for unknow cams*/
    int pal[] ={VIDEO_PALETTE_JPEG,VIDEO_PALETTE_YUV420P,VIDEO_PALETTE_RGB24,VIDEO_PALETTE_RGB565,VIDEO_PALETTE_RGB32};
    struct video_picture pict;
    int masq = 0x1;
    int i;
    int availpal = 0;
    int defaut = 1;
    /* initialize the internal struct */
    if (ioctl (vd->fd, VIDIOCGPICT, &pict) < 0)
    {
        perror ("Couldnt get videopict params with VIDIOCGPICT\n");
        return -1;
    }
    /* try each palette we have we skip raw_jpeg */
    for (i = 0; i < 5 ; i++)
    {
        pict.palette = pal[i];
        /* maybe correct the bug on qca driver depth always 24 ? */
        pict.depth = GetDepth (pal[i]);
//	logger(TLOG_NOTICE, "try palette %d depth %d\n",pict.palette,pict.depth);
        if (ioctl (vd->fd, VIDIOCSPICT, &pict) < 0)
        {
            logger(TLOG_ERROR, "Couldnt set palette first try %d \n", pal[i]);

        }
        if (ioctl (vd->fd, VIDIOCGPICT, &pict) < 0)
        {
            logger(TLOG_ERROR, "Couldnt get palette %d \n", pal[i]);

        }
        if (pict.palette != pal[i])
        {
            logger(TLOG_ERROR, "Damned second try fail \n");
        }
        else
        {
            availpal = availpal | masq ;
//logger(TLOG_NOTICE, "Available  palette %d \n", pal[i]);
            if (defaut)
            {
                defaut = 0;
                //vd->formatIn = pal[i];
                // vd->bppIn = GetDepth (pal[i]);
            }
        }

        masq = masq << 1;
    }
    vd->palette = availpal;
    //should set default palette here ?
    return 1;
}

static
int probeSize ( struct vdIn *vd )
{	/* probe size and set a default one for unknow cams */
    int size[] = { 640,480,384,288,352,288,320,240,192,144,176,144,160,120 };
    struct video_window win;
    int maxw,minw,maxh,minh;
    int masq = 0x1;
    int i = 0;
    int defaut = 1 ;
    /* initialize de parameters */
    maxw = vd->videocap.maxwidth;
    minw = vd->videocap.minwidth;
    maxh = vd->videocap.maxheight;
    minh = vd->videocap.minheight;
//logger(TLOG_NOTICE, "probe size in \n");
    while (size[i] > maxw)
    {
//	logger(TLOG_NOTICE, "skip size %d x %d\n",size[i],size[i+1]);
        i += 2;
        masq = masq << 1;
        if (i > 13) break;
    }
    /* initialize the internal struct */
    if (ioctl (vd->fd, VIDIOCGWIN, &win) < 0)
    {
        perror ("VIDIOCGWIN failed \n");
        return -1;
    }
    /* now i is on the first possible width */
    while ((size[i] >= minw) && i < 13)
    {
        win.width = size[i];
        win.height = size[i+1];
        if (ioctl (vd->fd, VIDIOCSWIN, &win) < 0)
        {
            printf ("VIDIOCSWIN reject width %d  height %d \n",
                    win.width, win.height);
        }
        else
        {
            vd->sizeothers = vd->sizeothers | masq;
//	 printf ("Available Resolutions width %d  heigth %d \n",
//	 		win.width, win.height);
            if (defaut)
            {

                // vd->hdrwidth = win.width;
                // vd->hdrheight = win.height;
                defaut = 0;
            }
        }
        masq = masq << 1 ;
        i += 2;
    }

    return 1;
}

int
changeSize (struct vdIn *vd)
{
    int erreur;
    erreur = GetVideoPict (vd);
    vd->formatIn = vd->videopict.palette;
    vd->bppIn = vd->videopict.depth;
    /* To Compute the estimate frame size perhaps not need !!! */
    if ((vd->bppIn = GetDepth (vd->formatIn)) < 0)
    {
        perror ("getdepth  failed \n");
        exit (1);
    }
    if (vd->grabMethod)
    {
        vd->vmmap.height = vd->hdrheight;
        vd->vmmap.width = vd->hdrwidth;
        vd->vmmap.format = vd->formatIn;

    }
    else
    {

        if (ioctl (vd->fd, VIDIOCGWIN, &vd->videowin) < 0)
            perror ("VIDIOCGWIN failed \n");
        vd->videowin.height = vd->hdrheight;
        vd->videowin.width = vd->hdrwidth;
        if (ioctl (vd->fd, VIDIOCSWIN, &vd->videowin) < 0)
            perror ("VIDIOCSWIN failed \n");
        printf ("VIDIOCGWIN height %d  width %d \n",
                vd->videowin.height, vd->videowin.width);
    }
    vd->framesizeIn = ((vd->hdrwidth * vd->hdrheight * vd->bppIn) >> 3);
//  vd->pixTmp =
//    (unsigned char *) realloc (vd->pixTmp, (size_t) vd->framesizeIn);

	return 0;
}

/* return masq byte for the needed size */
static int convertsize( int width, int height)
{
    switch (width)
    {
    case 640:
        if (height == 480)
            return VGA;
        break;
    case 384:
        if (height == 288)
            return PAL;
        break;
    case 352:
        if (height == 288)
            return SIF;
        break;
    case 320:
        if (height == 240)
            return CIF;
        break;
    case 192:
        if (height == 144)
            return QPAL;
        break;
    case 176:
        if (height == 144)
            return QSIF;
        break;
    case 160:
        if (height == 120)
            return QCIF;
        break;
    default:
        break;
    }
    return -1;
}
static int sizeconvert( int *width, int *height, int size)
{
    switch (size)
    {
    case VGA:
        *height = 480;
        *width = 640;
        break;
    case PAL:
        *height = 288;
        *width = 384;
        break;
    case SIF:
        *height = 288;
        *width = 352;
        break;
    case CIF:
        *height = 240;
        *width = 320;
        break;
    case QPAL:
        *height = 144;
        *width = 192;
        break;
    case QSIF:
        *height = 144;
        *width = 176;
        break;
    case QCIF:
        *height = 120;
        *width = 160;
        break;
    default:
        return -1;
        break;
    }
    return 0;
}
static int convertpalette( int palette)
{
    switch (palette)
    {
    case VIDEO_PALETTE_JPEG:
        return JPG;
        break;
    case VIDEO_PALETTE_YUV420P:
        return YUV420P;
        break;
    case VIDEO_PALETTE_RGB24:
        return RGB24;
        break;
    case VIDEO_PALETTE_RGB565:
        return RGB565;
        break;
    case VIDEO_PALETTE_RGB32:
        return RGB32;
        break;
    default:
        break;
    }
    return -1;
}
static int paletteconvert( int code)
{
    switch (code)
    {
    case JPG:
        return VIDEO_PALETTE_JPEG;
        break;
    case YUV420P:
        return VIDEO_PALETTE_YUV420P;
        break;
    case RGB24:
        return VIDEO_PALETTE_RGB24;
        break;
    case RGB565:
        return VIDEO_PALETTE_RGB565;
        break;
    case RGB32:
        return VIDEO_PALETTE_RGB32;
        break;
    default:
        return -1;
        break;
    }
    return 0;
}
/*check palette not so easy try VIDIOCMCAPTURE IOCTL the only one with palette and size */
/* some drivers may fail here  */
static int checkpalette (struct vdIn *vd)
{
    unsigned char masq = 0x00;
//    int f = 0;
    int needpalette = 0;
    int palette =0;

    needpalette = convertpalette(vd->formatIn);
    /* is the palette available */
    if (!(vd->palette & needpalette))
    {
        /* find an other one */
        if (needpalette >1)
        {
            masq = needpalette -1;
        }
        if (( masq & vd->palette) > 1)
        {
            /* check lower masq upper size */
            while (!((needpalette = needpalette >> 1) & vd->palette) && needpalette);
        }
        else if ((masq & vd->palette) == 0)
        {
            masq = 0xff -(needpalette << 1) +1;
            if ((masq & vd->palette) == 0)
            {
                /* no more size available */
                needpalette = 0;
            }
            else
            {
                /* check upper masq */
                while (!((needpalette = needpalette << 1) & vd->palette) && needpalette);
            }
        } // maybe == 1
    }

    if ((palette = paletteconvert( needpalette)) < 0)
    {
        logger(TLOG_ERROR, "Invalid palette in check palette fatal !! \n");
        return -1;
    }

    if (palette)
    {
        vd->vmmap.height = vd->hdrheight;
        vd->vmmap.width = vd->hdrwidth;
        vd->vmmap.format = palette;

        vd->vmmap.frame = 0;
        if (ioctl (vd->fd, VIDIOCMCAPTURE, &(vd->vmmap)))
        {
            perror ("cmcapture");
            return -1;
        }
    }
    else
    {
        logger(TLOG_ERROR, "palette not find check palette fatal !! \n");
        return -1;
    }
    /*populate the change */
    vd->formatIn = palette;
    return palette;

}
/* test is palette and size are available otherwhise return the next available palette and size
palette is set by preference order jpeg yuv420p rbg24 rgb565 and rgb32 */
static int check_palettesize(struct vdIn *vd )
{
    int needsize = 0;
    int needpalette = 0;
    unsigned char masq = 0x00;
    /* initialize needed size */
    if ((needsize = convertsize(vd->hdrwidth,vd->hdrheight)) < 0)
    {
        logger(TLOG_ERROR,  "size seem unavailable fatal errors !!\n");
        return -1;
    }
    /* is there a match with available palette */
    /* check */
    if (!(vd->sizeothers & needsize))
    {
        if (needsize > 1)
        {
            masq = needsize -1;
        }
        if (( masq & vd->sizeothers) > 1)
        {
            /* check lower masq upper size */
            while (!((needsize = needsize >> 1) & vd->sizeothers) && needsize);
        }
        else if ((masq & vd->sizeothers) == 0)
        {
            masq = 0xff -(needsize << 1) +1;
            if ((masq & vd->sizeothers) == 0)
            {
                /* no more size available */
                needsize = 0;
            }
            else
            {
                /* check upper masq */
                while (!((needsize = needsize << 1) & vd->sizeothers) && needsize);
            }
        } // maybe == 1

    }
    if (needsize)
    {
        /* set the size now check for a palette */
        if (sizeconvert( &vd->hdrwidth,&vd->hdrheight,needsize) > 0)
        {
            logger(TLOG_ERROR,  "size not set fatal errors !!\n");
            return -1;
        }
        if ((needpalette = checkpalette(vd) < 0))
        {
            return -1;
        }
    }
    else
    {
        printf ("Damned no match found Fatal errors !!\n");
        return -1;
    }
    return needsize;
}

static int
isSpcaChip (const char *BridgeName)
{
    int i = -1;
    int find = -1;
    int size = 0;

    /* Spca506 return more with channel video, cut it */

    /* return Bridge otherwhise -1 */
    for (i = 0; i < MAX_BRIDGE -1; i++)
    {
        size = strlen (Blist[i].name) ;
//    printf ("is_spca %s \n",Blist[i].name);
        if (strncmp (BridgeName, Blist[i].name, size) == 0)
        {
            find = i;
            break;
        }
    }

    return find;
}

static int
GetStreamId (const char *BridgeName)
{
    int i = -1;
    int match = -1;
    /* return Stream_id otherwhise -1 */
    if ((match = isSpcaChip (BridgeName)) < 0)
    {
        printf ("Not an Spca5xx Camera !!\n");
        return match;
    }
    switch (match)
    {
    case BRIDGE_SPCA505:
    case BRIDGE_SPCA506:
        i = YYUV;
        break;
    case BRIDGE_SPCA501:
        i = YUYV;
        break;
    case BRIDGE_SPCA508:
        i = YUVY;
        break;
    case BRIDGE_SPCA536:
    case BRIDGE_SPCA504:
    case BRIDGE_SPCA500:
    case BRIDGE_SPCA504B:
    case BRIDGE_SPCA533:
    case BRIDGE_SPCA504C:
    case BRIDGE_ZR364XX:
    case BRIDGE_ZC3XX:
    case BRIDGE_CX11646:
    case BRIDGE_SN9CXXX:
    case BRIDGE_MR97311:
        i = JPEG;
        break;
    case BRIDGE_ETOMS:
    case BRIDGE_SONIX:
    case BRIDGE_SPCA561:
    case BRIDGE_TV8532:
        i = GBRG;
        break;
    default:
        i = UNOW; // -1;
        printf ("Unable to find a StreamId !!\n");
        break;

    }
    return i;
}

static int
GetDepth (int format)
{
    int depth;
    switch (format)
    {

    case VIDEO_PALETTE_JPEG:
    {
        depth = 8;
    }
    break;
    case VIDEO_PALETTE_RAW:
    {
        depth = 8;
    }
    break;
    case VIDEO_PALETTE_YUV420P:
    {
        depth = (8 * 3) >> 1;
    }
    break;
    case VIDEO_PALETTE_RGB565:
        depth = 16;
        break;
    case VIDEO_PALETTE_RGB24:
        depth = 24;
        break;
    case VIDEO_PALETTE_RGB32:
    {
        depth = 32;
    }
    break;
    default:
        depth = -1;
        break;
    }
    return depth;
}

__u8
SpcaGetBrightness (struct vdIn * vdin)
{
    if (GetVideoPict (vdin) < 0)
    {
        printf (" Error getBrightness \n");
        return 0;
    }
    return ((vdin->videopict.brightness) >> 8);
}

void
SpcaSetBrightness (struct vdIn *vdin, __u8 bright)
{
    vdin->videopict.brightness = bright << 8;
    if (SetVideoPict (vdin) < 0)
    {
        printf (" Error setBrightness \n");
    }

}
__u8
SpcaGetContrast (struct vdIn *vdin)
{
    if (GetVideoPict (vdin) < 0)
    {
        printf (" Error getContrast \n");
        return 0;
    }
    return ((vdin->videopict.contrast) >> 8);
}

void
SpcaSetContrast (struct vdIn *vdin, __u8 contrast)
{
    vdin->videopict.contrast = contrast << 8;
    if (SetVideoPict (vdin) < 0)
    {
        printf (" Error setContrast \n");
    }
}
__u8
SpcaGetColors (struct vdIn *vdin)
{
    if (GetVideoPict (vdin) < 0)
    {
        printf (" Error getColors \n");
        return 0;
    }
    return ((vdin->videopict.colour) >> 8);
}

void
SpcaSetColors (struct vdIn *vdin, __u8 colors)
{
    vdin->videopict.colour = colors << 8;
    if (SetVideoPict (vdin) < 0)
    {
        printf (" Error setColors \n");
    }
}
/* we assume that struct videopict is initialized */
unsigned short upbright( struct vdIn *vdin)
{
    unsigned short bright =0;

    bright = vdin->videopict.brightness;
    if (( bright+0x200) < 0xffff)
    {
        bright += 0x200;
        vdin->videopict.brightness = bright;
        if (SetVideoPict (vdin) < 0)
        {
            printf (" Error setVideopict \n");
            return 0;
        }
    }
    return bright;
}
unsigned short downbright( struct vdIn *vdin)
{
    unsigned short bright =0;

    bright = vdin->videopict.brightness;
    if (( bright-0x200) > 0)
    {
        bright -= 0x200;
        vdin->videopict.brightness = bright;
        if (SetVideoPict (vdin) < 0)
        {
            printf (" Error setVideopict \n");
            return 0;
        }
    }
    return bright;
}
unsigned short upcontrast( struct vdIn *vdin)
{
    unsigned short contrast =0;

    contrast = vdin->videopict.contrast;
    if ((contrast+0x200) < 0xffff)
    {
        contrast += 0x200;
        vdin->videopict.contrast = contrast;
        if (SetVideoPict (vdin) < 0)
        {
            printf (" Error setVideopict \n");
            return 0;
        }
    }
    return contrast;
}
unsigned short downcontrast( struct vdIn *vdin)
{
    unsigned short contrast =0;

    contrast = vdin->videopict.contrast;
    if ( (contrast-0x200) > 0)
    {
        contrast -= 0x200;
        vdin->videopict.contrast = contrast;
        if (SetVideoPict (vdin) < 0)
        {
            printf (" Error setVideopict \n");
            return 0;
        }
    }
    return contrast;
}
void
qualityUp(struct vdIn *vdin)
{
    struct video_param *videoparam= &vdin->videoparam;
    int fd = vdin->fd;
    unsigned char index = videoparam->quality;
    index += 1;
    spcaSetQuality(fd,videoparam,index);
    return;
}
void
qualityDown(struct vdIn *vdin)
{
    struct video_param *videoparam= &vdin->videoparam;
    int fd = vdin->fd;
    unsigned char index = videoparam->quality;
    if (index > 0) index--;
    spcaSetQuality(fd,videoparam,index);
    return;
}
void
timeUp(struct vdIn *vdin)
{
    struct video_param *videoparam= &vdin->videoparam;
    int fd = vdin->fd;
    unsigned short index = videoparam->time_interval;
    index+=10;
    spcaSetTimeInterval(fd,videoparam,index);
    return;
}
void
timeDown(struct vdIn *vdin)
{
    struct video_param *videoparam= &vdin->videoparam;
    int fd = vdin->fd;
    unsigned short index = videoparam->time_interval;
    if (index > 0) index -=10;
    spcaSetTimeInterval(fd,videoparam,index);

    return;
}
void
spcaSetAutoExpo(struct vdIn *vdin)
{
    struct video_param *videoparam= &vdin->videoparam;
    int fd = vdin->fd;
    videoparam->chg_para = CHGABRIGHT;
    videoparam->autobright = !videoparam->autobright;
    if (ioctl(fd,SPCASVIDIOPARAM, videoparam) == -1)
    {
        logger(TLOG_ERROR, "autobright error !!\n");
    }
    else
        spcaPrintParam (fd,videoparam);

}
static void spcaPrintParam (int fd, struct video_param *videoparam)
{
    if (ioctl(fd,SPCAGVIDIOPARAM, videoparam) == -1)
    {
 //       logger(TLOG_ERROR, "wrong spca5xx device\n");
    }
    
    return;
}

static void spcaSetTimeInterval(int fd, struct video_param *videoparam, unsigned short time)
{
    if (time < 1000)
    {
        videoparam->chg_para = CHGTINTER;
        videoparam->time_interval = time;
        if (ioctl(fd,SPCASVIDIOPARAM, videoparam) == -1)
        {
            logger(TLOG_ERROR, "frame_times error !!\n");
        }
        else
            spcaPrintParam (fd,videoparam);
    }

    return;

}
static void spcaSetQuality(int fd, struct video_param *videoparam, unsigned char index)
{
    if (index < 6)
    {
        videoparam->chg_para = CHGQUALITY;
        videoparam->quality = index;
        if (ioctl(fd,SPCASVIDIOPARAM, videoparam) == -1)
        {
            logger(TLOG_ERROR, "quality error !!\n");
        }
        else
            spcaPrintParam (fd,videoparam);
    }

    return;
}

/*
void
grab (void)
{
int err = 0;
  for (;;)
    {
      //logger(TLOG_NOTICE, "I am the GRABBER !!!!! \n");
      err = v4lGrab(&videoIn);
      if (!videoIn.signalquit || (err < 0)){
      logger(TLOG_NOTICE, "GRABBER going out !!!!! \n");
	break;
	}
    }
}

void sigchld_handler(int s)
{
	videoIn.signalquit = 0;
}
*/

int
rtv_init (int channel, struct vdIn *vd)//int argc, char *argv[])
{
//    int videoon = 0;
//    int ret;
    char *videodevice = NULL;
//    char *partdevice = NULL;
//    int usepartport = 0;
//    int err;
    int grabmethod = 1;
    int format = VIDEO_PALETTE_JPEG;//VIDEO_PALETTE_YUV420P;
    int width = 640;//352;
    int height = 480;//288;
    if (channel == 0)
    {
        width = g_config.video.solution_x_1.var;
        height = g_config.video.solution_y_1.var;
        g_htv_interval[channel] = 5;
    }
    else if (channel == 1)
    {
        width = g_config.video.solution_x_2.var;
        height = g_config.video.solution_y_2.var;
        g_htv_interval[channel] = 5;
    }

    /*
        char *separateur;
        char *sizestring = NULL;
        char *mode = NULL;
        int i;
        int serv_sock,new_sock;
        pthread_t w1;
        pthread_t server_th;
        int sin_size;
        unsigned short serverport = 7070;
        struct sockaddr_in their_addr;
        struct sigaction sa;
    */

    if (channel == 0)
    {
        videodevice = "/dev/video0";
    }
    else if (channel == 1)
    {
        videodevice = "/dev/video1";
    }
//  if(usepartport && partdevice == NULL)
//  	partdevice = "/dev/parport0";

    memset (vd, 0, sizeof (struct vdIn));
    if (init_videoIn(vd, videodevice, width, height, format,grabmethod, channel) != 0)
    {
        logger(TLOG_ERROR, "init_videoIn failed, channel=%d", channel);
        return -1;
    }

    pthread_mutex_init(&g_htv_en_mutex[0], NULL);
    pthread_mutex_init(&g_htv_en_mutex[1], NULL);
    pthread_mutex_init(&g_cache_cp_en[0], NULL);
    pthread_mutex_init(&g_cache_cp_en[1], NULL);
    pthread_mutex_init(&g_cap_num_mutex[0], NULL);
    pthread_mutex_init(&g_cap_num_mutex[1], NULL);

    return 0;
}

// 实时视频主线程:获取视频数据，然后直接发送出去
int thread_rtv_main(int *param)
{
    int	channel = *param;
    struct vdIn *vd = &videoIn[channel];
	
	pthread_mutex_lock(&g_watchdog_event[channel].mutex);
	g_watchdog_event[channel].event_enable = 0;
	pthread_mutex_unlock(&g_watchdog_event[channel].mutex);
	
    if (rtv_init(channel, vd) != 0)
    {
        if (0 == channel)
        {
            mapThreadID2Handler[THREAD_RTV_0].thread_quit_flag = 1;
            mapThreadID2Handler[THREAD_RTV_SEND_0].thread_quit_flag = 1;
            thread_syn_flag_set(&frame_syn_ctrl[0][0].mutex_r,
                                &frame_syn_ctrl[0][0].cond_r,
                                &frame_syn_ctrl[0][0].flag_r);
        }
        else if (1 == channel)
        {
            mapThreadID2Handler[THREAD_RTV_1].thread_quit_flag = 1;
            mapThreadID2Handler[THREAD_RTV_SEND_1].thread_quit_flag = 1;
            thread_syn_flag_set(&frame_syn_ctrl[1][0].mutex_r,
                                &frame_syn_ctrl[1][0].cond_r,
                                &frame_syn_ctrl[1][0].flag_r);
                                
        }

		logger(TLOG_ERROR, "rtv init failed. channel=%d", channel);
        return -1;

    }
	
	pthread_mutex_lock(&g_watchdog_event[channel].mutex);	
	g_watchdog_event[channel].event_counter++;
	g_watchdog_event[channel].event_enable = 1;	
	pthread_mutex_unlock(&g_watchdog_event[channel].mutex);
	logger(TLOG_NOTICE, "rtv init success at channel %d", channel);

//    thread_syn_flag_set(&syn_ctrl_rtv.mutex_r, &syn_ctrl_rtv.cond_r, &syn_ctrl_rtv.flag_r);

/*
    // 唤醒看门狗        
    thread_syn_flag_set(&syn_ctrl_watchdog.mutex_r, 
                            &syn_ctrl_watchdog.cond_r,
                            &syn_ctrl_watchdog.flag_r);
*/
	while (1)
    {
		pthread_mutex_lock(&g_watchdog_event[channel].mutex);
		g_watchdog_event[channel].event_counter++;
		pthread_mutex_unlock(&g_watchdog_event[channel].mutex);
		
        if (!(((channel == 0) && (!mapThreadID2Handler[THREAD_RTV_0].thread_quit_flag))
                ||((channel == 1) && (!mapThreadID2Handler[THREAD_RTV_1].thread_quit_flag))))
        {
         //   logger(TLOG_NOTICE, "%s quits.\n", __FUNCTION__);
            break;
        }
//			logger(TLOG_NOTICE, "============%s not quits=============.\n", __FUNCTION__);

        if (v4lGrab(vd, channel) != 0)
        {
            logger(TLOG_ERROR, "Grab failed.\n");
            if (0 == channel)
                mapThreadID2Handler[THREAD_RTV_0].thread_quit_flag = 1;
            else
                mapThreadID2Handler[THREAD_RTV_1].thread_quit_flag = 1;
        }
 //       logger(TLOG_NOTICE, "thread_rtv_main\n");

    }
	
	pthread_mutex_lock(&g_watchdog_event[channel].mutex);
	g_watchdog_event[channel].event_enable = 0;	
	pthread_mutex_unlock(&g_watchdog_event[channel].mutex);
	
    close_v4l(vd);
/*
    // 如果两路rtv都停止了，则阻塞看门狗       
    if((0 == threadID[THREAD_RTV_0]) && (0 == threadID[THREAD_RTV_1]))
        thread_syn_flag_clr(&syn_ctrl_watchdog.mutex_r, 
                                &syn_ctrl_watchdog.cond_r,
                                &syn_ctrl_watchdog.flag_r);
*/

	logger(TLOG_NOTICE, "%s of channel %d exit", __FUNCTION__, channel);

    return 0;
}

int set_bright(int channel, int bright)
{
    SpcaSetBrightness(&videoIn[channel], (__u8) bright);
    return 0;
}

int set_contrast(int channel, int contrast)
{
    SpcaSetContrast(&videoIn[channel], (__u8) contrast);
    return 0;
}

int set_solution(int channel, int x, int y)
{
    //停止线程
    rtv_usb_remove(channel+1);
    sleep(1);

    //重新启动线程
    if (channel == 0)
    {
        rtv_syn_init(channel);
        vs_thread_create(THREAD_RTV_SEND_0, &channel_0);
        vs_thread_create(THREAD_RTV_0, &channel_0);
    }
    else if (channel == 1)
    {
        rtv_syn_init(channel);
        vs_thread_create(THREAD_RTV_SEND_1, &channel_1);
        vs_thread_create(THREAD_RTV_1, &channel_1);
    }

	return 0;
}

// 设置视频参数:分辨率，亮度和对比度
int vm_para_set(s_var_video *var_video)
{
    if (var_video->solution_x_1 != g_config.video.solution_x_1.var
            || var_video->solution_y_1 != g_config.video.solution_y_1.var)
    {
        g_config.video.solution_x_1.var = var_video->solution_x_1;
        g_config.video.solution_y_1.var = var_video->solution_y_1;
        set_solution(0, var_video->solution_x_1, var_video->solution_y_1);
    }

    if (var_video->bright_1 != g_config.video.bright_1.var)
        set_bright(0, var_video->bright_1);
    if (var_video->contrast_1 != g_config.video.contrast_1.var)
        set_contrast(0, var_video->contrast_1);



    if (var_video->solution_x_2 != g_config.video.solution_x_2.var
            || var_video->solution_y_2 != g_config.video.solution_y_2.var)
    {
        g_config.video.solution_x_2.var = var_video->solution_x_2;
        g_config.video.solution_y_2.var = var_video->solution_y_2;
        set_solution(1, var_video->solution_x_2, var_video->solution_y_2);
    }
    if (var_video->bright_2 != g_config.video.bright_2.var)
        set_bright(1, var_video->bright_2);
    if (var_video->contrast_2 != g_config.video.contrast_2.var)
        set_contrast(1, var_video->contrast_2);
    return 0;
}

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


