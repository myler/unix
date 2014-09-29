#include "cgic.h"
#include "config.h"
#include "cgi_types.h"
#include "cgi_sem_utils.h"
#include "cgi_html_utils.h"

void cgi_alert_get_action(char * shm){
	*(int *)(shm+sizeof(int)) = ID_CGI_ALERT_SET_ACTION;
	*(int *)(shm+sizeof(int)*2) = CGI_GET_DATA;
}

void cgi_alert_set_action(char * shm){
	s_var_alert *alert_setting = (s_var_alert *)(shm+sizeof(int)*3);

	*(int *)(shm+sizeof(int)) = ID_CGI_ALERT_SET_ACTION;
	*(int *)(shm+sizeof(int)*2) = CGI_SET_DATA;

	memset(alert_setting, 0, sizeof(s_var_alert));
	
	cgiFormInteger("capture_pic_enable_1", &alert_setting->capture_pic_enable_1, 0);	
	cgiFormInteger("capture_pic_num_1", &alert_setting->capture_pic_num_1, 0);
	cgiFormInteger("capture_pic_interval_1", &alert_setting->capture_pic_interval_1, 0);
	cgiFormInteger("capture_video_enable_1", &alert_setting->capture_video_enable_1, 0);	
	cgiFormInteger("capture_video_last_time_1", &alert_setting->capture_video_last_time_1, 0);
	cgiFormInteger("alarm_enable_1", &alert_setting->alarm_enable_1, 0);
	cgiFormInteger("alarm_delay_1", &alert_setting->alarm_delay_1, 0);
	cgiFormInteger("alarm_last_time_1", &alert_setting->alarm_last_time_1, 0);
	cgiFormInteger("md_enable_1", &alert_setting->md_enable_1, 0);
	cgiFormInteger("md_sensitivity_1", &alert_setting->md_sensitivity_1, 0);
	cgiFormString("md_area_0_1", alert_setting->md_area_0_1, _LEN_NORMAL);
	cgiFormString("md_area_1_1", alert_setting->md_area_1_1, _LEN_NORMAL);
	cgiFormString("md_area_2_1", alert_setting->md_area_2_1, _LEN_NORMAL);
	cgiFormString("md_area_3_1", alert_setting->md_area_3_1, _LEN_NORMAL);
	cgiFormString("week_alert_plan_1", alert_setting->week_alert_plan_1, _LEN_WEEK);
	cgiFormInteger("plan_cap_enable_1", &alert_setting->plan_cap_enalbe_1, 0);
	cgiFormInteger("plan_cap_last_sec_1", &alert_setting->plan_cap_last_sec_1, 0);
 
	cgiFormInteger("capture_pic_enable_2", &alert_setting->capture_pic_enable_2, 0);	
	cgiFormInteger("capture_pic_num_2", &alert_setting->capture_pic_num_2, 0);
	cgiFormInteger("capture_pic_interval_2", &alert_setting->capture_pic_interval_2, 0);
	cgiFormInteger("capture_video_enable_2", &alert_setting->capture_video_enable_2, 0);	
	cgiFormInteger("capture_video_last_time_2", &alert_setting->capture_video_last_time_2, 0);
	cgiFormInteger("alarm_enable_2", &alert_setting->alarm_enable_2, 0);
	cgiFormInteger("alarm_delay_2", &alert_setting->alarm_delay_2, 0);
	cgiFormInteger("alarm_last_time_2", &alert_setting->alarm_last_time_2, 0);
	cgiFormInteger("md_enable_2", &alert_setting->md_enable_2, 0);
	cgiFormInteger("md_sensitivity_2", &alert_setting->md_sensitivity_2, 0);
	cgiFormString("md_area_0_2", alert_setting->md_area_0_2, _LEN_NORMAL);
	cgiFormString("md_area_1_2", alert_setting->md_area_1_2, _LEN_NORMAL);
	cgiFormString("md_area_2_2", alert_setting->md_area_2_2, _LEN_NORMAL);
	cgiFormString("md_area_3_2", alert_setting->md_area_3_2, _LEN_NORMAL);
	cgiFormString("week_alert_plan_2", alert_setting->week_alert_plan_2, _LEN_WEEK);	
	cgiFormInteger("plan_cap_enable_2", &alert_setting->plan_cap_enalbe_2, 0);
	cgiFormInteger("plan_cap_last_sec_2", &alert_setting->plan_cap_last_sec_2, 0);
}

void cgi_alert_puts(char *p_shm){

	s_var_alert *alert_setting;
	
	alert_setting = (s_var_alert *)(p_shm + sizeof(int)*3);

	CGI_HTML_HEAD_PUT("IPC WEB控制端");
	CGI_HTML_BODY_LOGO_MENU_PUT;
	CGI_HTML_BODY_CONTENT_PUT("../html_alert_set_body.html");
	CGI_HTML_BODY_COPYRIGHT_PUT;
	fprintf(cgiOut,"<script>\n");
	
//	CGI_JS_VAR_SET_STRING("ip_addr", alert_setting->ip_addr);
	CGI_JS_VAR_SET_INT("alert_num", alert_setting->alert_num);

	CGI_JS_VAR_SET_INT("capture_pic_enable_1", alert_setting->capture_pic_enable_1);
	CGI_JS_VAR_SET_INT("capture_pic_num_1", alert_setting->capture_pic_num_1);
	CGI_JS_VAR_SET_INT("capture_pic_interval_1", alert_setting->capture_pic_interval_1);
	CGI_JS_VAR_SET_INT("capture_video_enable_1", alert_setting->capture_video_enable_1);
	CGI_JS_VAR_SET_INT("capture_video_last_time_1", alert_setting->capture_video_last_time_1);
	CGI_JS_VAR_SET_INT("alarm_enable_1", alert_setting->alarm_enable_1);
	CGI_JS_VAR_SET_INT("alarm_delay_1", alert_setting->alarm_delay_1);
	CGI_JS_VAR_SET_INT("alarm_last_time_1", alert_setting->alarm_last_time_1);
	CGI_JS_VAR_SET_INT("md_enable_1", alert_setting->md_enable_1);
	CGI_JS_VAR_SET_INT("md_sensitivity_1", alert_setting->md_sensitivity_1);
	CGI_JS_VAR_SET_STRING("md_area_0_1", alert_setting->md_area_0_1);
	CGI_JS_VAR_SET_STRING("md_area_1_1", alert_setting->md_area_1_1);
	CGI_JS_VAR_SET_STRING("md_area_2_1", alert_setting->md_area_2_1);
	CGI_JS_VAR_SET_STRING("md_area_3_1", alert_setting->md_area_3_1);
	CGI_JS_VAR_SET_STRING("week_alert_plan_1", alert_setting->week_alert_plan_1);
	CGI_JS_VAR_SET_INT("plan_cap_enable_1", alert_setting->plan_cap_enalbe_1);
	CGI_JS_VAR_SET_INT("plan_cap_last_sec_1", alert_setting->plan_cap_last_sec_1);
	
	CGI_JS_VAR_SET_INT("capture_pic_enable_2", alert_setting->capture_pic_enable_2);
	CGI_JS_VAR_SET_INT("capture_pic_num_2", alert_setting->capture_pic_num_2);
	CGI_JS_VAR_SET_INT("capture_pic_interval_2", alert_setting->capture_pic_interval_2);
	CGI_JS_VAR_SET_INT("capture_video_enable_2", alert_setting->capture_video_enable_2);
	CGI_JS_VAR_SET_INT("capture_video_last_time_2", alert_setting->capture_video_last_time_2);
	CGI_JS_VAR_SET_INT("alarm_enable_2", alert_setting->alarm_enable_2);
	CGI_JS_VAR_SET_INT("alarm_delay_2", alert_setting->alarm_delay_2);
	CGI_JS_VAR_SET_INT("alarm_last_time_2", alert_setting->alarm_last_time_2);
	CGI_JS_VAR_SET_INT("md_enable_2", alert_setting->md_enable_2);
	CGI_JS_VAR_SET_INT("md_sensitivity_2", alert_setting->md_sensitivity_2);
	CGI_JS_VAR_SET_STRING("md_area_0_2", alert_setting->md_area_0_2);
	CGI_JS_VAR_SET_STRING("md_area_1_2", alert_setting->md_area_1_2);
	CGI_JS_VAR_SET_STRING("md_area_2_2", alert_setting->md_area_2_2);
	CGI_JS_VAR_SET_STRING("md_area_3_2", alert_setting->md_area_3_2);
	CGI_JS_VAR_SET_STRING("week_alert_plan_2", alert_setting->week_alert_plan_2);
	CGI_JS_VAR_SET_INT("plan_cap_enable_2", alert_setting->plan_cap_enalbe_2);
	CGI_JS_VAR_SET_INT("plan_cap_last_sec_2", alert_setting->plan_cap_last_sec_2);

	cgi_html_include("../js_alert_set.js");
	fprintf(cgiOut,"\n</script>");
	CGI_HTML_BODY_SET_MENU("alert", "报警设置");
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
		cgi_alert_get_action(shm);
		post_v(sem_id);             // 使能vs程序操作共享内存信号量
		wait_v(sem_id_cgi);

		ret = *(int *)shm;
		if(0 != ret )                          
		{
			char temp[32];
			sprintf(temp,"error is %d\n",ret);
			cgiHeaderContentType("text/html; charset=gb2312");
			puts("<html><head><title>alert get error</title><h1><font color='red'>wrong username or password</f><h1>"); 
			puts(temp);
			return -1;    
		}
		
		cgi_alert_puts(shm);

	}
	else if(0 == flag){
		cgi_alert_set_action(shm);
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
		
		cgi_alert_puts(shm);
	}

	shmdt(shm); 

	return 0; 
} 



