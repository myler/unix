#include "cgic.h"
#include "config.h"
#include "cgi_types.h"
#include "cgi_sem_utils.h"
#include "cgi_html_utils.h"

void cgi_user_get_action(char * shm){
	*(int *)(shm+sizeof(int)) = ID_CGI_USER_SET_ACTION;
	*(int *)(shm+sizeof(int)*2) = CGI_GET_DATA;
}

void cgi_user_set_action(char * shm){
	s_var_user *user_setting = (s_var_user *)(shm+sizeof(int)*3);

	*(int *)(shm+sizeof(int)) = ID_CGI_USER_SET_ACTION;
	*(int *)(shm+sizeof(int)*2) = CGI_SET_DATA;

	memset(user_setting, 0, sizeof(s_var_user));

	cgiFormInteger("user_num", &user_setting->user_num, 4);
	cgiFormString("username_0", user_setting->username_0, _LEN_NORMAL);
	cgiFormString("password_0", user_setting->password_0, _LEN_NORMAL);
	cgiFormString("username_1", user_setting->username_1, _LEN_NORMAL);
	cgiFormString("password_1", user_setting->password_1, _LEN_NORMAL);
	cgiFormString("username_2", user_setting->username_2, _LEN_NORMAL);
	cgiFormString("password_2", user_setting->password_2, _LEN_NORMAL);
	cgiFormString("username_3", user_setting->username_3, _LEN_NORMAL);
	cgiFormString("password_3", user_setting->password_3, _LEN_NORMAL);	
}

void cgi_user_puts(char *p_shm){
	s_var_user *user_setting;
	
	user_setting = (s_var_user *)(p_shm + sizeof(int)*3);

	CGI_HTML_HEAD_PUT("IPC WEB控制端");
	CGI_HTML_BODY_LOGO_MENU_PUT;
	CGI_HTML_BODY_CONTENT_PUT("../html_user_set_body.html");
	CGI_HTML_BODY_COPYRIGHT_PUT;
	fprintf(cgiOut,"<script>\n");

	CGI_JS_VAR_SET_INT("user_num", user_setting->user_num);
	CGI_JS_VAR_SET_STRING("username_0", user_setting->username_0);
	CGI_JS_VAR_SET_STRING("password_0", user_setting->password_0);
	CGI_JS_VAR_SET_STRING("username_1", user_setting->username_1);
	CGI_JS_VAR_SET_STRING("password_1", user_setting->password_1);
	CGI_JS_VAR_SET_STRING("username_2", user_setting->username_2);
	CGI_JS_VAR_SET_STRING("password_2", user_setting->password_2);
	CGI_JS_VAR_SET_STRING("username_3", user_setting->username_3);
	CGI_JS_VAR_SET_STRING("password_3", user_setting->password_3);	
	
	cgi_html_include("../js_user_set.js");
	fprintf(cgiOut,"\n</script>");
	CGI_HTML_BODY_SET_MENU("user", "用户设置");
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
		cgi_user_get_action(shm);
		post_v(sem_id);             // 使能vs程序操作共享内存信号量
		wait_v(sem_id_cgi);

		ret = *(int *)shm;
		if(0 != ret )                          
		{
			char temp[32];
			sprintf(temp,"error is %d\n",ret);
			cgiHeaderContentType("text/html; charset=gb2312");
			puts("<html><head><title>user get error</title><h1><font color='red'>wrong username or password</f><h1>"); 
			puts(temp);
			return -1;    
		}
		
		cgi_user_puts(shm);

	}
	else if(0 == flag){
		cgi_user_set_action(shm);
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
		
		cgi_user_puts(shm);
	}

	shmdt(shm); 

	return 0; 
} 



