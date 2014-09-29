#ifndef __CGI_HTML_UTILS_H__
#define __CGI_HTML_UTILS_H__

#include <string.h>
#include <stdio.h>

#define CHARSET		"gb2312"

#define CGI_HTML_MAX_LEN_LINE               1024                    // 注意文件一行的大小

#define CGI_HTML_HEAD_PUT(TITLE)  	do{		\
	fprintf(cgiOut, "Content-type: text/html; charset=%s\r\n\r\n", CHARSET);	\
	fprintf(cgiOut, "<html><head><title>%s</title>", TITLE);		\
	cgi_html_include("../html_frame_style.css");		\
	fprintf(cgiOut, "</head>");				\
}while(0)

#define CGI_HTML_TAIL_PUT		do{		\
	fprintf(cgiOut, "</body></html>");				\
}while(0)

#define CGI_HTML_BODY_LOGO_MENU_PUT		do{		\
	fprintf(cgiOut, "<body>");		\
	fprintf(cgiOut,  "<table align=\"center\" width=\"783\" cellpadding=\"0\"  cellspacing=\"0\" border=\"0\" >");	\
	cgi_html_include("../html_body_logo_menu.html");		\
}while(0)

#define CGI_HTML_BODY_CONTENT_PUT(CONTENT)	do{		\
	fprintf(cgiOut, "<tr valign=\"top\"><td width=\"28\" height=\"500\" ></td>");	\
	fprintf(cgiOut, "<td width=\"639\">");		\
	cgi_html_include(CONTENT);				\
	fprintf(cgiOut, "</td><td width=\"111\"></td></tr>");	\
}while(0)

#define CGI_HTML_BODY_COPYRIGHT_PUT	do{		\
	cgi_html_include("../html_body_copyright.html");	\
	fprintf(cgiOut, "</table>");			\
}while(0)

#define CGI_HTML_BODY_SET_MENU(ID, TIP)  do{	\
	fprintf(cgiOut, "<script>window.onload=init;\n var menu_id=\"%s\";\n var menu_tip=\"%s\";\n", ID, TIP);	\
	fprintf(cgiOut, "\n function init(){\n document.getElementById(\"menu_\"+menu_id).src=\"../images/\"+menu_id+\"_set_1.jpg\";\n");	\
	fprintf(cgiOut,"document.getElementById(\"menuTip\").innerHTML=menu_tip;\n setValue();}</script>");	\
}while(0)

#define CGI_JS_VAR_SET_STRING( VARNAME, VALUE) do{	\
	fprintf(cgiOut,"var %s=\"%s\";\n", VARNAME, VALUE);	\
}while(0)

#define CGI_JS_VAR_SET_INT( VARNAME, VALUE) do{	\
	fprintf(cgiOut,"var %s=\"%d\";\n", VARNAME, VALUE);	\
}while(0)

int cgi_html_include(char *file_name)
{
	FILE * fp;

	char str[CGI_HTML_MAX_LEN_LINE];
	memset(str, 0 ,CGI_HTML_MAX_LEN_LINE);

	fp=fopen(file_name, "r");
	if(fp == NULL) 
		return -1;

	while(!feof(fp))                                  //通过循环判断指针是否指向文件末尾
	{
		fgets(str,CGI_HTML_MAX_LEN_LINE,fp);
		puts(str);
	}

	fclose(fp);
	return 0;
}

#endif


