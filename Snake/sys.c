/*************************************************************************
    > File Name: sys.c
    > Author: swolf
    > Mail: *-* 
    > Created Time: 2014年08月12日 星期二 13时04分00秒
 ************************************************************************/

#include"sys.h"


// 定时器函数   tim_ms 设置的定时毫秒数
void game_timer(int tim_ms)
{
	struct itimerval time;
	time.it_interval.tv_sec = tim_ms / 1000; 
	time.it_interval.tv_usec = tim_ms % 1000 * 1000;
	
	time.it_value.tv_sec = tim_ms / 1000;
	time.it_value.tv_usec = tim_ms % 1000 * 1000;

	setitimer(ITIMER_REAL,&time,NULL);
}


// 按键函数
char get_key(void) 
{
	int n;
	char buf[3];
	n = read(0,buf,sizeof(buf));
	if(3 == n && buf[0] == 27 && buf[1] == 91)
	{
		return buf[2];
	}
	else if(1 == n)
	{
		return buf[0];
	}
	return 0;
}

