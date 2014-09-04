/*************************************************************************
    > File Name: vt.h
    > Author: swolf
    > Mail: *-* 
    > Created Time: 2014年08月11日 星期一 19时41分03秒
 ************************************************************************/

#ifndef __VT_H__
#define __VT_H__


void goto_xy(int x, int y);
void putch(int fcolor, int bcolor, char ch);
void putstr(int fcolor, int bcolor, const char *str);
void clr_scrn(void);
void hide_cur(void);
void show_cur(void);
void store_cur(void);
void load_cur(void);
void draw_box(int x, int y, int row, int col, int fcolor, int bcolor,char ch);
void draw_rect(int x, int y, int row, int col, int fcolor, int bcolor,char ch);

#endif	/*__VT_H__*/
