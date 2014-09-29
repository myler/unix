#include "cgic.h"
#include "config.h"
#include "cgi_types.h"
#include "cgi_sem_utils.h"
#include "cgi_html_utils.h"

void cgi_rtv_get_action(char * shm){
	*(int *)(shm+sizeof(int)) = ID_CGI_RTV_SET_ACTION;
	*(int *)(shm+sizeof(int)*2) = CGI_GET_DATA;
}

void cgi_rtv_set_action(char * shm){
	s_var_video *rtv_setting = (s_var_video *)(shm+sizeof(int)*3);

	*(int *)(shm+sizeof(int)) = ID_CGI_RTV_SET_ACTION;
	*(int *)(shm+sizeof(int)*2) = CGI_SET_DATA;

	memset(rtv_setting, 0, sizeof(s_var_video));

	cgiFormInteger("solution_x_1", &rtv_setting->solution_x_1, 352);
	cgiFormInteger("solution_y_1", &rtv_setting->solution_y_1, 288);
	cgiFormInteger("bright_1", &rtv_setting->bright_1, 20);
	cgiFormInteger("contrast_1", &rtv_setting->contrast_1, 30);
	cgiFormInteger("frame_interval_1", &rtv_setting->frame_interval_1, 0);
	
	cgiFormInteger("speed_1", &rtv_setting->speed_1, 64);
	cgiFormInteger("cache_time_1", &rtv_setting->cache_time_1, 10);

	cgiFormInteger("solution_x_2", &rtv_setting->solution_x_2, 352);
	cgiFormInteger("solution_y_2", &rtv_setting->solution_y_2, 288);
	cgiFormInteger("bright_2", &rtv_setting->bright_2, 20);
	cgiFormInteger("contrast_2", &rtv_setting->contrast_2, 30);
	cgiFormInteger("frame_interval_2", &rtv_setting->frame_interval_2, 0);
	
	cgiFormInteger("speed_2", &rtv_setting->speed_2, 64);
	cgiFormInteger("cache_time_2", &rtv_setting->cache_time_2, 10);
}

void cgi_rtv_puts(char *p_shm){
	s_var_video *rtv_setting;
	
	rtv_setting = (s_var_video *)(p_shm + sizeof(int)*3);

	CGI_HTML_HEAD_PUT("IPC WEB控制端");
	CGI_HTML_BODY_LOGO_MENU_PUT;
	CGI_HTML_BODY_CONTENT_PUT("../html_rtv_set_body.html");
	CGI_HTML_BODY_COPYRIGHT_PUT;
	fprintf(cgiOut,"<script>\n");
	
	CGI_JS_VAR_SET_INT("rtv_num", rtv_setting->rtv_num);	

	CGI_JS_VAR_SET_INT("solution_x_1", rtv_setting->solution_x_1);	
	CGI_JS_VAR_SET_INT("solution_y_1", rtv_setting->solution_y_1);		
	CGI_JS_VAR_SET_INT("bright_1", rtv_setting->bright_1);
	CGI_JS_VAR_SET_INT("contrast_1", rtv_setting->contrast_1);
	CGI_JS_VAR_SET_INT("frame_interval_1", rtv_setting->frame_interval_1);
	
	CGI_JS_VAR_SET_INT("speed_1", rtv_setting->speed_1);
	CGI_JS_VAR_SET_INT("cache_time_1", rtv_setting->cache_time_1);
	
	CGI_JS_VAR_SET_INT("solution_x_2", rtv_setting->solution_x_2);	
	CGI_JS_VAR_SET_INT("solution_y_2", rtv_setting->solution_y_2);		
	CGI_JS_VAR_SET_INT("bright_2", rtv_setting->bright_2);
	CGI_JS_VAR_SET_INT("contrast_2", rtv_setting->contrast_2);
	CGI_JS_VAR_SET_INT("frame_interval_2", rtv_setting->frame_interval_2);
	
	CGI_JS_VAR_SET_INT("speed_2", rtv_setting->speed_2);
	CGI_JS_VAR_SET_INT("cache_time_2", rtv_setting->cache_time_2);
	
	cgi_html_include("../js_rtv_set.js");
	fprintf(cgiOut,"\n</script>");
	CGI_HTML_BODY_SET_MENU("rtv", "视频设置");
	CGI_HTML_TAIL_PUT;
}

int cgiMain(void) 
{    
	int ret;
	key_t key; 
	key_t key_cgi;
	int flag;

	int shm_id,sem_id, sem_id_cgi; 
	char *shm; 

	// 创建并关联共享内存
	key       = ftok("./vs_shm",0); 
	key_cgi  = ftok("./vs_shm_cgi",0); 
	shm_id  = shmget(key,SEGSIZE,0); 
	if(-1 == shm_id)
	{
		cgiHeaderContentType("text/html; charset=gb2312");
		puts("<html><head><title>share memeroy error</title><h1><font color='red'>create shared memory error</f><h1><html><head>"); 
		return -1; 
	} 

	shm = (char *)shmat(shm_id,0,0);
	if (-1 == (int)shm)
	{ 
		cgiHeaderContentType("text/html; charset=gb2312");
		puts(" attach shared memory error\n"); 
		return -1; 
	} 

	// 创建互斥锁
	sem_id     = sem_creat(key);                      // vs程序操作共享内存信号量
	sem_id_cgi = sem_creat(key_cgi);                  // 外部程序cgi操作共享内存信号量

	cgiFormInteger("flag", &flag, 1);
	if(1 == flag){				//getData
		cgi_rtv_get_action(shm);
		post_v(sem_id);             // 使能vs程序操作共享内存信号量
		wait_v(sem_id_cgi);

		ret = *(int *)shm;
		if(0 != ret )                          
		{
			char temp[32];
			sprintf(temp,"error is %d\n",ret);
			cgiHeaderContentType("text/html; charset=gb2312");
			puts("<html><head><title>rtv get error</title><h1><font color='red'>wrong username or password</f><h1>"); 
			puts(temp);
			return -1;    
		}
		
		cgi_rtv_puts(shm);

	}
	else if(0 == flag){
		cgi_rtv_set_action(shm);
		post_v(sem_id);             // 使能vs程序操作共享内存信号量
		wait_v(sem_id_cgi);

		ret = *(int *)shm;
		if(0 != ret )                          
		{
			char temp[32];
			sprintf(temp,"error is %d\n",ret);
			cgiHeaderContentType("text/html; charset=gb2312");
			puts("<html><head><title>login error</title><h1><font color='red'>wrong username or password</f><h1>"); 
			puts(temp);
			return -1;    
		}
		
		cgi_rtv_puts(shm);
	}

	shmdt(shm); 

	return 0; 
} 

