#ifndef __CGI_TYPES_H__
#define __CGI_TYPES_H__

#include "config.h"

/************************Global Define***********************/
//#define DEBUG 1

#define SEGSIZE 2048 //1024*2

#define CGI_SET_DATA 	0
#define CGI_GET_DATA 	1

#define ID_CGI_LOGIN_ACTION	0
#define ID_CGI_RTV_SET_ACTION	1
#define ID_CGI_NETWORK_SET_ACTION	2
#define ID_CGI_ALERT_SET_ACTION	3
#define ID_CGI_STORE_SET_ACTION	4
#define ID_CGI_USER_SET_ACTION	5
#define ID_CGI_SYS_SET_ACTION	6

// 网页的每一个提交，对应一个CGI,对应一个vs的CGI处理程序，他们的连接关系:
// cgi_data_DS -- id_cgi_data_DS    id_cgi_handler -- cgi_handler
// 只要共享内存的双方的id_cgi_data_DS/id_cgi_handler使用相同的编号，就能实现提交和vs处理程序的对应
typedef int(*cgi_CallBack_operation)(char *p_shm);
typedef struct tag_map_CGI_flag2Handler
{

	int id_cgi_handler;
	cgi_CallBack_operation cgi_handler;               // 处理对应CGI的handler
} s_map_CGI_flag2Handler;
/************************login**************************/

typedef struct tag_cgi_login_action   // 登录页面数据结构
{
	char username[32];
	char password[32];
} s_cgi_login_action;

#endif

