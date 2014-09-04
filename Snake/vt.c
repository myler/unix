#include<stdio.h>

// 设置光标位置
void goto_xy(int x, int y)
{
    printf("\033[%d;%dH",x,y);
}

// 打印前景色为fcolor 背景色为bcolor 的字符 ch
void putch(int fcolor, int bcolor, char ch)
{
	printf("\033[%dm\033[%dm%c\033[0m",fcolor,bcolor,ch);
}

// 打印前景色为fcolor 背景色为bcolor 的字符串 str
void putstr(int fcolor, int bcolor, const char *str)
{
	printf("\033[%dm\033[%dm%s\033[0m",fcolor,bcolor,str);
}
// 清屏
void clr_scrn(void)
{
	printf("\033[2J");
}

// 隐藏光标
void hide_cur(void)
{
	printf("\033[?25l");
}

//显示光标
void show_cur(void)
{
	printf("\033[?25h");
}

//保存光标
void store_cur(void)
{
	printf("\033[s");
}

//加载光标
void load_cur(void)
{
	printf("\033[u");
}

//画一个 盒子
void draw_box(int x, int y, int row, int col, int fcolor,int bcolor, char ch)
{	int i, j;
	for(i = 0;i <= row; i++)
		for(j = 0; j <= col; j++)
		{
			if(i == 0 || i == row 
					|| j == 0 || j == col)
				printf("\033[%d;%dH\033[%d;%dm%c\033[0m\n",i + x,j + y,fcolor,bcolor,ch);
			else
				printf("\033[%d;%dH%c",i + x,j + y,' ');
		}
}

//画一个 方块
void draw_rect(int x, int y, int row, int col, int fcolor,int bcolor, char ch)
{
	int i, j;
	for(i = 0; i < row; i++)
		for(j = 0; j < col; j++)
		{
			printf("\033[%d;%dH\033[%d;%dm%c\033[0m\n",i + x,j + y,fcolor,bcolor,ch);
		}
}

