/*************************************************************************
    > File Name: snack.c
    > Author: swolf
    > Mail: *-* 
    > Created Time: Thu 14 Aug 2014 06:55:42 PM CST
 ************************************************************************/

#include "sys.h"
#include "vt.h"
#include"snack.h"


int main(void)
{
	int quit = 0;
	while(!quit)
	{
		system("stty -echo -icanon");	//取消回显和缓存；
		hide_cur();						//隐藏光标；
		clr_scrn();						//清屏；
		game_box();						//画边框；

		goto_xy(6,33);					//移动光标位置；
		putstr(31,1," HAVE FUN SNACK");	//输出字符串；
		goto_xy(8,33);
		putstr(31,1," 1. 新游戏");
		goto_xy(9,33);
		putstr(31,1," 2. 读取存档");
		goto_xy(10,33);
		putstr(31,1," 3. 排行榜");
		goto_xy(11,33);
		putstr(31,1," 4. 退出游戏");
		fflush(stdout);
		int back = 0;
		while(!back)
		{
			int ret;
			char key = '0';
			int i;
			key = get_key();			//获取按键
			switch(key)
			{
				case 49:				// 1  选项
					game_init_game();	// 初始化游戏环境
					game_init_data();	// 初始化游戏数据
					game_key();			// 调用游戏按键函数	

					back = 1;			// 退出标志
					break;
				case 50:				// 2  选项	
					ret = load_data();	//  加载游戏存档
					goto_xy(7,62);
					if(ret == 0)
						putstr(8,5," load_success!");

					game_init_game();
					game_key();

					back = 1;
					break;
				case 51:				//3 选项  排行榜
					clr_scrn();			
					goto_xy(1,33);
					putstr(31,1," num.	GRADE");
					for(i = 1; i < 11; i++)
					{
						goto_xy(i * 2,33);
						printf("\033[%d;%dm %d.	%d\033[0m",31,1,i, g.max_grade[i - 1]);
					}

					getchar();
					back = 1;
					break;

				case 52:			// 4 选项 退出游戏
					quit = 1;
					back = 1;
					break;
				default:
					;
			}	

		}
	}
	game_end();						// 游戏结束函数
	return 0;
}


void game_init_game(void)			// 初始化游戏环境
{
	srand(time(NULL));				// 设置随机数种子
	signal(SIGALRM,func_hander);	// 注册定时信号
	game_timer(400);				// 设置定时时间
	system("stty -echo -icanon");	// 取消回显和缓存
	hide_cur();						// 隐藏光标
}

void game_init_data(void)
{
	g.count = 2;					//初始化蛇的节数
	g.head.x = 10;					//初始化蛇头位置
	g.head.y = 20;			
	g.body[0].x = 10;				//初始化蛇身位置
	g.body[0].y = 19;
	g.body[1].x = 10;
	g.body[1].y = 18;
	g.body[2].x = 10;
	g.body[2].y = 17;
	//g.dir.x = 0;				
	//g.dir.y = 1;
	g.fkey = 'r';					//方向标志位
	g.dir.f = RIGHT;				//初始化蛇的行动方向	
	g.level = 0;					//初始化等级
	g.speed = 401;					//初始化速度即定时器刷新时间
	g.grade = 0;					//初始化分数
	game_food();					//随机食物位置
}


int game_end(void)					//退出游戏函数
{
	goto_xy(ROW + 3,1);

	system("stty echo icanon");		//设置回回显和缓存
	show_cur();						//显示光标
	exit(0);						//退出函数
}


int game_key(void)					//游戏按键控制函数
{
	int quit = 0;
	int flag = 1;
	int ret;
	while(!quit)
	{
		char key;
		key = get_key();

		switch(key)
		{
			case SPACE:				//按space 暂停并存档 即关闭定时器
				if(flag)
				{
					game_timer(0);
					ret = save_data();
					goto_xy(8,5);
					if(ret == 0)
						printf("save success!\n");
				}
				else				// 再按space 取消暂停  即开启定时器
				{
					game_timer(g.speed);
				}
				flag = !flag;
				break;


			case ESC:				// esc 退出游戏按键
				game_grade_cmp();	
				game_timer(0);
				quit = 1;
				break;

			case UP:				// 向上
				g.dir.f = UP;
				break;
	
			case DOWN:				//向下
				g.dir.f = DOWN;
				break;

			case RIGHT:				//向左
				g.dir.f = RIGHT;
				break;

			case LEFT:				//向右
				g.dir.f = LEFT;
				break;
			default:
				break;

		}
	}
	return 0;
}

void game_box()						//画边框函数
{
	clr_scrn();
	draw_box(1,20,ROW,COL,44,34,'#');
}

void game_snack(void)					// 画蛇函数
{
	int i;
	draw_rect(g.head.x,g.head.y + 20 ,1,1,43,33,'x');
	for(i = 0; i <= g.count - 1; i++)
	{
		draw_rect(g.body[i].x,g.body[i].y + 20,1,1,3,32,'@');
	}
}

void move_snack(void)					//移动蛇函数
{
	int i;

	if(g.head.x <= 1 || g.head.x >= ROW + 1 || g.head.y <= 0 || g.head.y >= COL)//蛇头撞墙游戏结束
	{
		life_end();
		game_end();
	}


	for(i = 0;i < g.count;i++)
	{
		if(g.head.x == g.body[i].x && g.head.y == g.body[i].y)	//蛇撞到身体游戏结束
		{
			life_end();
			game_end();		
		}
	}

	if(g.head.x == g.food.x && g.head.y == g.food.y)	//蛇头撞到食物
	{
		game_food();
		g.count++;										//节数加一
		g.grade += 10;									//分数加十
		g.level = g.grade / 50;							//五十分等级加一
		g.speed = 401 - g.level * 20;					//一级减 20 ms
		game_timer(g.speed);							//重新设置定时时间改变速度
	}

	for(i = g.count - 1; i > 0; i--)
	{
		g.body[i].x = g.body[i - 1].x;			// 身体自动移动
		g.body[i].y = g.body[i - 1].y;			
	}
	g.body[0].x = g.head.x;						
	g.body[0].y = g.head.y;
	switch(g.dir.f)								//根据按键控制蛇头移动方向
	{
		case UP:
			if(g.fkey != 'd')					// g.fkey 防止蛇头往回走
			{
				g.head.x -= 1;
				g.fkey = 'u';
			}
			else 
			{
				g.head.x += 1;
			}
			break;

		case DOWN:
			if(g.fkey != 'u')
			{
				g.head.x += 1;
				g.fkey = 'd';
			}
			else
			{
				g.head.x -= 1;
			}
			break;

		case RIGHT:
			if(g.fkey != 'l')
			{
				g.head.y += 1;
				g.fkey = 'r';
			}
			else
			{
				g.head.y -= 1;
			}
			break;

		case LEFT:
			if(g.fkey != 'r')
			{
				g.head.y -= 1;
				g.fkey = 'l';
			}
			else
			{
				g.head.y += 1;
			}
			break;

		default:

			break;

	}
}

void game_food(void)			//随机食物位置的函数
{
	int i;
	int flag = 0;
	while(1)
	{
		g.food.x = (rand() % (ROW - 2)) + 2;
		g.food.y = (rand() % (COL - 2)) + 2;

		if(g.food.x != g.head.x && g.food.y != g.head.y)	//食物不与蛇头重合
			for(i = 0;i < g.count;i++)						//食物不与身体重合
			{
				if(g.food.x != g.body[i].x && g.food.y != g.body[i].y )
					flag = 1;
			}

		if(flag)
		{
			break;
		}
		continue;
	}
}


void func_hander(int sig)		//定时器时间到调用此函数 刷新屏幕				
{

	game_box();
	draw_rect(g.food.x, g.food.y + 20, 1, 1, 46,36,'#' );
	move_snack();
	game_snack();
	goto_xy(5,5);
	printf("分数：%d",g.grade);
	goto_xy(6,5);
	printf("等级：%d",g.level);
	goto_xy(7,5);
	printf("最高分：%d",g.max_grade[0]);
	fflush(stdout);
}

int save_data(void)				//存档函数
{
	FILE * fp = NULL;
	fp = fopen("game_data","w");
	fwrite(&g,sizeof(game_t),1,fp);
	fclose(fp);
	return (0);
}

int load_data(void)				//读档函数
{
	FILE * fp = NULL;
	fp = fopen("game_data","r");
	fread(&g,sizeof(game_t),1,fp);
	fclose(fp);
	return 0;

}

void game_grade_cmp(void)		//改变排行函数
{
	int i, j; 	
	for(i = 0; i < 10; i++)
	{
		if(g.grade > g.max_grade[i])
		{
			for(j = 9;j > i;j--)
			{
				g.max_grade[j] = g.max_grade[j - 1];
			}
			g.max_grade[i] = g.grade;
			break;		
		}
	}
}

int life_end(void)			//生命结束函数
{
	game_timer(0);
	goto_xy(10,31);
	putstr(33,1," GAME OVER!");
	goto_xy(11,31);
	printf("\033[33m GRADE: %d\033[0m\n",g.grade);
	game_grade_cmp();
	getchar();
	return 0;
}

