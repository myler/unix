#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */


#include <stdlib.h>         /*  for malloc() */
#include <string.h>         /*  for memcpy() */
#include <dirent.h>         /* for opendir() */
#include <sys/vfs.h>        /* for statfs() */
#include <stdio.h>          /* for sprintf() */

#include <sys/stat.h>        /* for stat() */
#include <unistd.h>
#include <sys/types.h>       /* for mkdir() */

#include "config.h"
#include "vs_config_put_var_auto.h"


typedef struct tagConfig_timer_param
{
    int         timer_id_detect;            // 定时移动侦测的定时器编号
    int         timer_id_cap;               // 定时抓拍的定时器编号
}Config_timer_param;
Config_timer_param g_conf_timer;

// sx added auto
//#include "vs_config_put_var_auto.h"
// sx added auto end 


// 将weekplan中的数据拷贝到schedule中

// 读取配置文件
int config_read(char *file_name)
{
    FILE *fp;
    char line[512];
    char name[48];      // 前面的名字，规定最长不超过20
    char var[256];      // 后面的数值
    char note[256];      // 注释文字
    
    char c;
    int start, pos;
	int flag_4_close = 0;       // var部分是否含有"号
	int flag_1_box = 0;
	int flag_1_box_end = 0;
    int flag = 0;
    char *ret = line;

    memset(&g_config, 0, sizeof(AllConfig));
    
    fp = fopen(file_name, "r");
    if ( fp == NULL )
    {
        return -1;
    }
    
    while( !feof(fp) )
    {
        ret = fgets(line, 512, fp);
        if ( ret == NULL )
        {
            break;
        }

        // 进行line的解析, 用=号分隔. 懒得用strstr, 自己来解析. 因为还希望trim,去除"号等等。使用strstr麻烦。

		// 解析的效果： name部分，不允许出现=号
		//              var部分，可以含有=号。
		//              所有空格都忽略。即含有trim功能。var部分，如果希望含有空格或"号，需要用"号括起来(主要是前面部分)
		//              当出现[]时,效果就是name[0]=='\0', 而var赋值为[]中的内部,var是经过trim的。
		// 允许的情况有：
		//aaa=bbbb
		//  aaa   =    bbb
        //  aaa   == bbb
        //  aaa   ===  bb===bb
        //  aaa  ======= "  b ==  b   b  "
        //[abc]
        //  [  abc  ]
        //  [  a  b  c ]

        // 而不恰当的如 aaa = bb bb    就只相当于 aaa = bb了，因为 bb bb 中间有空格，却没有"号包括起来
        
		start = 0;
		flag = 0;
		pos = 0;
		name[0] = '\0';
		var[0] = '\0';
		note[0] = '\0';
		flag_4_close = 0;
		flag_1_box = 0;
		flag_1_box_end = 0;
		c = line[0];

		// |_| AAA |_| = |_| BBB |_|
		// 0   1  2    3     4  5     flag
		while( c != '\0' )
		{
			c = line[pos];
			if ( (( c == ' ' || c == '\t') && flag_4_close == 0 ) || c == '\0' || c == '\n' || c == '\r' || (c == '=' && flag <= 3) || (c == '/' && line[pos+1] == '/') )
			{
				if ( flag == 0 || flag == 3 )
				{
					start = pos;        // 碰到空格，起始段向前走
				}
				if ( flag == 1 )        // 结束
				{
					memcpy( name, line+start, pos-start );
					name[pos-start] = '\0';
					flag ++;
				}
				if ( flag == 4 )
				{
					if (flag_1_box == 1)
					{
						if (start > 0)
						{
							memcpy( var, line+start, flag_1_box_end-start+1);
							var[flag_1_box_end-start+1] = '\0';
						}
						if ( flag_1_box_end-start >= 0 && var[flag_1_box_end-start] == '"' && flag_4_close == 1 )
						{
							var[flag_1_box_end-start] = '\0';  // 去掉 " 号
						}
						break;
					}
					if ( line[start-1] == '/' && line[start] == '/' )       //  a=//ccc 的情况。var是空
					{
						strcpy(note, line+start-1);
						break;
					}
					memcpy( var, line+start, pos-start );
					var[pos-start] = '\0';
					flag ++;
					
					if ( pos-start-1 >= 0 && var[pos-start-1] == '"' && flag_4_close == 1 )
					{
						var[pos-start-1] = '\0';  // 去掉 " 号
					}
					break;
				}
				if ( c == '=' && ( flag == 2 || flag == 5) )
				{
					flag = 3;
				}
			}
			else
			{
				if ( flag_1_box == 1 && c != ' ' && c != '\t' && c != ']' )
				{
					if (start < 0)
					{
						start = pos;
					}
					flag_1_box_end = pos;
				}
				if ( flag == 0 || flag == 3 )
				{
					flag ++;
					start = pos;

					if ( flag == 1 && c == '[' )
					{
						flag = 4;
						flag_1_box = 1;	// 中括号方式
						flag_4_close = 1;		// 含有"号
						start = -1;
					}
					if ( flag == 4 && c == '"' )
					{
						flag_4_close = 1;		// 含有"号
						start ++;
						flag_1_box = 1;
					}
				}
				if ( flag == 4 && flag_1_box == 1 && c == ']' )
				{
					if (start > 0)
					{
						memcpy( var, line+start, flag_1_box_end-start+1);
						var[flag_1_box_end-start+1] = '\0';
					}
					break;
				}
			}
			pos ++;
		}

		// 从pos开始，查找note注释文字
		if (note[0] =='\0')
		{
			while (line[pos] != '\0')
			{
				if ( line[pos] == '/' && line[pos+1] == '/' )
				{
					strcpy(note, line+pos);
					/*
					int note_len = strlen(note);
					if ( note[note_len-1] == '\n' )
					    note[note_len-1] = '\0';
					if ( note[note_len -2] == '\r' )
					    note[note_len -2] = '\0';
					*/
					break;
				}
				pos ++;
			}
		}
		if (name[0] == '\r' || name[0] == '\n')
		{
			continue;
		}
        // 进行全局变量的赋值
        vs_config_put_var(name, var, note);
        
    }

    fclose(fp);
    return 0;
}

// 写一行带[]的信息
int vs_config_box_line(FILE *fp, char *line, char *name, char *note)
{
    int max_first_len = 48;     // 前面最长48个字符
    int len = 0;

    //fprintf(fp, "\r\n");
    
    sprintf(line, "[%s]", name);
    if ( note[0] != '\0' )
    {
        len = strlen(line);     // 计划前面的长度，追加一定的空格，对齐
        if (len < max_first_len)
        {
            memset(line+len, ' ', max_first_len - len);
            line[max_first_len] = '\0';
        }
        strcat(line, note);  // 将注释追加
    }
    fprintf(fp, "%s\r\n", line);
    return 0;
}

// 写一项具体的数值. name = var   note(//...)
int vs_config_var_line(FILE *fp, char *line, char *name, char *var, char *note)
{
    int max_first_len = 48;     // 前面最长48个字符
    int len = 0;

    if ( name[0] == '\0' )
    {
        return 0;
    }
    if ( var[0] == '\0' )
    {
        sprintf(line, "  %s = ", name);
    }
    else
    {
        sprintf(line, "  %s = \"%s\"", name, var);
    }
    if ( note[0] != '\0' )
    {
        len = strlen(line);     // 计划前面的长度，追加一定的空格，对齐
        if (len < max_first_len)
        {
            memset(line+len, ' ', max_first_len - len);
            line[max_first_len] = '\0';
        }
        if ( note[0] == '\0')
        {
            strcat(line, "\n");
        }
        else
        {
            strcat(line, note);  // 将注释追加
            if (note[strlen(note)-1] != '\n' )
            {
                strcat(line, "\n");
            }
        }
    }
    fprintf(fp, "%s\r\n", line);
    return 0;
}

// 写一项具体的数值. name = var   note(//...)
int vs_config_var_line2(FILE *fp, char *line, char *name, long var, char *note)
{
    int max_first_len = 48;     // 前面最长48个字符
    int len = 0;

    if ( name[0] == '\0' )
    {
        return 0;
    }

    sprintf(line, "  %s = %ld", name, var);
    if ( note[0] != '\0' )
    {
        len = strlen(line);     // 计划前面的长度，追加一定的空格，对齐
        if (len < max_first_len)
        {
            memset(line+len, ' ', max_first_len - len);
            line[max_first_len] = '\0';
        }
        if ( note[0] == '\0')
        {
            strcat(line, "\n");
        }
        else
        {
            strcat(line, note);  // 将注释追加
            if (note[strlen(note)-1] != '\n' )
            {
                strcat(line, "\n");
            }
        }
    }
    fprintf(fp, "%s\r\n", line);
    return 0;
}

// sx added auto
#include "vs_config_write_auto.h"
// sx added auto en

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

