/***********************************************************************************
*              Copyright 2007 - 2010, Megaeyes. Co., Ltd.
*                           ALL RIGHTS RESERVED
* FileName: hi_server.c
* Description: main model .
*
* History:
* Version   Date              Author        DefectNum    Description
* 1.1       2007-08-22   q60002125     NULL            Create this file.
***********************************************************************************/




#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

#include <stdio.h>

#include "sm_fileOption.h"
#include "logger.h"

// 尝试打开文件，这里使用该函数判断文件是否存在。 返回值: 0, 存在    其他, 不存在
int file_open_try(char *file_name, char *mode)
{
    FILE *fp;
    fp = fopen(file_name, mode);
    if(NULL == fp){
        return -1;
    }

    fclose(fp);
    return 0;
}


/* 读取整个文件内容到buf,   mode: 同fopen的mode , 此处多用rb  */
int file_read(char *file_name, char *buf, int buf_len, char *mode)
{
    FILE *fp;
    int file_size;
    int n_read = 0;
    
    fp = fopen(file_name, mode);
    if(NULL == fp){
        logger(TLOG_ERROR, "file_read failed\n");
        return -1;
    }

    // 获取文件大小
    fseek(fp, 0, SEEK_END);
    file_size = ftell(fp);
    if(buf_len < file_size){
        logger(TLOG_ERROR, "buf space is not enough for read file\n ");
        fclose(fp);
        return -1;
    }
    
	fseek(fp,0, SEEK_SET);
	
    
    n_read = fread(buf, sizeof(unsigned char), file_size, fp );
    fclose(fp);
    
    return n_read;
}

/* 文件读,  mode: 同fopen的mode , 此处多用wb, 即覆盖写方式*/
int file_write(char *file_name, char *buf, int buf_len, char *mode)
{
    FILE *fp;
    int n_writed;
    
    fp = fopen(file_name, mode);
    if(NULL == fp){
        logger(TLOG_ERROR, "file_write  file open failed filename=%s", file_name);
        return -1;
    }

    n_writed = fwrite(buf, sizeof(unsigned char), buf_len, fp);
    fclose(fp);
    
    return n_writed;
}


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
