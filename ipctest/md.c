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
extern "C"
{
#endif
#endif /* __cplusplus */

#include "md.h"
#include "logger.h"

#define PIX_DIFF 0

// 移动侦测区域获取
//int md_eara_get()

// 比较新老buf是否有移动, sensitivity为侦测敏感阀值，该值为不同点数的百分比。返回值 0 无移动 1 有移动
int md_detect(char *buf_old, char *buf_new, int size, int sensitivity)
{
    int i;            // 行列
    int counter = 0;
    int pot_limit;

    // 计算点数阀值
    pot_limit = size * sensitivity / 100 / 3;
//	logger(TLOG_NOTICE, "size:%d, sensitivity:%d, pot_limit:%d", size, sensitivity, pot_limit);

    for (i = 0; i <= size; i = i + 3)
    {
        if ((abs(buf_old[i] - buf_new[i]) > PIX_DIFF)
			||(abs(buf_old[i+1] - buf_new[i+1]) > PIX_DIFF)
			||(abs(buf_old[i+2] - buf_new[i+2]) > PIX_DIFF))
        {
 //       	printf("detect differ:%d-%d=%d\n", buf_old[i], buf_new[i], buf_old[i]-buf_new[i]);
            counter++;
            if (counter >= pot_limit){
//				printf("md_detect got move, counter:%d\n", counter);
//				rt_md_report_set_req(NULL);
//				alert_send_start(2);
                return 1;
            }
        }

    }
    /*
        for(i=0; i<solution.x; i++)
        {
            if((i<md_eara.y) || (i>=(md_eara.y+md_eara.h)))
                continue;

            for(j= 0; j<solution.y; j++)
            {
                if((j<md_eara.x) || (i>=(md_eara.x+md_eara.w)))
                    continue;

                // 到此，为侦测区域
                if(buf_old[i*solution.x + j] != buf_new[i*solution.x + j])
                {
                    counter++;
                    if(counter >= pot_limit)
                        return 1;
                }
            }
        }
        */
 //    printf("NNNNNNNNNNNNNNNNNNNNNNNNNo move, counter:%d\n", counter);
    return 0;
}

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


