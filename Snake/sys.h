/*************************************************************************
    > File Name: sys.h
    > Author: swolf
    > Mail: *-* 
    > Created Time: 2014年08月12日 星期二 13时23分07秒
 ************************************************************************/

#ifndef __SYS_H
#define __SYS_H

#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<sys/time.h>
#include<unistd.h>




#define SPACE	 32
#define ESC		 27
#define UP		 65
#define DOWN     66
#define RIGHT    67
#define LEFT     68


extern void game_timer(int);

extern char get_key(void);

//void game_key(void);

#endif  /* __SYS_H  */
