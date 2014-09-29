#include "cgic.h"
#include "config.h"
#include "cgi_types.h"
#include "cgi_sem_utils.h"
#include "cgi_html_utils.h"

void cgi_network_get_action(char * shm){
	*(int *)(shm+sizeof(int)) = ID_CGI_NETWORK_SET_ACTION;
	*(int *)(shm+sizeof(int)*2) = CGI_GET_DATA;
}

void cgi_network_set_action(char * shm){
	s_var_network *network_setting = (s_var_network *)(shm+sizeof(int)*3);

	*(int *)(shm+sizeof(int)) = ID_CGI_NETWORK_SET_ACTION;
	*(int *)(shm+sizeof(int)*2) = CGI_SET_DATA;

	memset(network_setting, 0, sizeof(s_var_network));
	cgiFormString("ip_addr", network_setting->ip_addr, _LEN_NORMAL);
	cgiFormString("ip_mask", network_setting->ip_mask, _LEN_NORMAL);
	cgiFormString("ip_gateway", network_setting->ip_gateway, _LEN_NORMAL);
	cgiFormString("dns", network_setting->dns, _LEN_NORMAL);
	cgiFormString("mac_addr", network_setting->mac_addr, _LEN_NORMAL);
	cgiFormInteger("web_port", &network_setting->web_port, 0);
	cgiFormInteger("socket_port", &network_setting->socket_port, 0);
	cgiFormInteger("rtv_port", &network_setting->rtv_port, 0);
	cgiFormInteger("alarm_remote_port", &network_setting->alarm_remote_port, 0);
	cgiFormString("alarm_remote_addr", network_setting->alarm_remote_addr, _LEN_NORMAL);
}

void cgi_network_puts(char *p_shm){
	s_var_network *network_setting;
	
	network_setting = (s_var_network *)(p_shm + sizeof(int)*3);

	CGI_HTML_HEAD_PUT("IPC WEB控制端");
	CGI_HTML_BODY_LOGO_MENU_PUT;
	CGI_HTML_BODY_CONTENT_PUT("../html_network_set_body.html");
	CGI_HTML_BODY_COPYRIGHT_PUT;
	fprintf(cgiOut,"<script>\n");
	
	CGI_JS_VAR_SET_STRING("ip_addr", network_setting->ip_addr);
	CGI_JS_VAR_SET_STRING("ip_mask", network_setting->ip_mask);
	CGI_JS_VAR_SET_STRING("ip_gateway", network_setting->ip_gateway);
	CGI_JS_VAR_SET_STRING("dns", network_setting->dns);
	CGI_JS_VAR_SET_STRING("mac_addr", network_setting->mac_addr);
	CGI_JS_VAR_SET_INT("web_port", network_setting->web_port);
	CGI_JS_VAR_SET_INT("socket_port", network_setting->socket_port);
	CGI_JS_VAR_SET_INT("rtv_port", network_setting->rtv_port);
	CGI_JS_VAR_SET_INT("alarm_remote_port", network_setting->alarm_remote_port);
	CGI_JS_VAR_SET_STRING("alarm_remote_addr", network_setting->alarm_remote_addr);

	cgi_html_include("../js_network_set.js");
	fprintf(cgiOut,"\n</script>");
	CGI_HTML_BODY_SET_MENU("network", "网络设置");
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
		cgi_network_get_action(shm);
		post_v(sem_id);             // 使能vs程序操作共享内存信号量
		wait_v(sem_id_cgi);

		ret = *(int *)shm;
		if(0 != ret )                          
		{
			char temp[32];
			sprintf(temp,"error is %d\n",ret);
			cgiHeaderContentType("text/html; charset=gb2312");
			puts("<html><head><title>network get error</title><h1><font color='red'>wrong username or password</f><h1>"); 
			puts(temp);
			return -1;    
		}
		
		cgi_network_puts(shm);

	}
	else if(0 == flag){
		cgi_network_set_action(shm);
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
		
		cgi_network_puts(shm);
	}

	shmdt(shm); 

	return 0; 
} 

