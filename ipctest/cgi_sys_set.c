#include "cgic.h"
#include "config.h"
#include "cgi_types.h"
#include "cgi_sem_utils.h"
#include "cgi_html_utils.h"

void cgi_sys_get_action(char * shm){
	*(int *)(shm+sizeof(int)) = ID_CGI_SYS_SET_ACTION;
	*(int *)(shm+sizeof(int)*2) = CGI_GET_DATA;
}

void cgi_sys_set_action(char * shm){
	s_var_sys *sys_setting = (s_var_sys *)(shm+sizeof(int)*3);

	*(int *)(shm+sizeof(int)) = ID_CGI_SYS_SET_ACTION;
	*(int *)(shm+sizeof(int)*2) = CGI_SET_DATA;

//	memset(sys_setting, 0, sizeof(s_var_sys));

}

void cgi_sys_puts(char *p_shm){
	s_var_sys *sys_setting;
	
	sys_setting = (s_var_sys *)(p_shm + sizeof(int)*3);

	CGI_HTML_HEAD_PUT("IPC WEB控制端");
	CGI_HTML_BODY_LOGO_MENU_PUT;
	CGI_HTML_BODY_CONTENT_PUT("../html_sys_set_body.html");
	CGI_HTML_BODY_COPYRIGHT_PUT;
	fprintf(cgiOut,"<script>\n");

	CGI_JS_VAR_SET_STRING("app_version", sys_setting->app_version);
	CGI_JS_VAR_SET_STRING("app_time", sys_setting->app_time);
	
	cgi_html_include("../js_sys_set.js");
	fprintf(cgiOut,"\n</script>");
	CGI_HTML_BODY_SET_MENU("sys", "系统设置");
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
		cgi_sys_get_action(shm);
		post_v(sem_id);             // 使能vs程序操作共享内存信号量
		wait_v(sem_id_cgi);

		ret = *(int *)shm;
		if(0 != ret )                          
		{
			char temp[32];
			sprintf(temp,"error is %d\n",ret);
			cgiHeaderContentType("text/html; charset=gb2312");
			puts("<html><head><title>sys get error</title><h1><font color='red'>wrong sysname or password</f><h1>"); 
			puts(temp);
			return -1;    
		}
		
		cgi_sys_puts(shm);

	}
	else if(0 == flag){
		cgi_sys_set_action(shm);
		post_v(sem_id);             // 使能vs程序操作共享内存信号量
		wait_v(sem_id_cgi);

		ret = *(int *)shm;
		if(0 != ret )                          
		{
			char temp[32];
			sprintf(temp,"error is %d\n",ret);
			cgiHeaderContentType("text/html; charset=gb2312");
			puts("<html><head><title>login error</title><h1><font color='red'>wrong sysname or password</f><h1>"); 
			puts(temp);
			return -1;    
		}
		
		cgi_sys_puts(shm);
	}

	shmdt(shm); 

	return 0; 
} 




