/*************************************************************************
    > File Name: snack.h
    > Author: swolf
    > Mail: *-* 
    > Created Time: Thu 14 Aug 2014 07:07:30 PM CST
 ************************************************************************/
#ifndef __SNACK_H
#define __SNACK_H


#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<sys/time.h>
#include<unistd.h>
#include<time.h>

#define ROW  20
#define COL  40
typedef struct pos
{
	int x;
	int y;
}pos_t;

typedef struct dir{
	int x;
	int y;
	int f;
}dir_t;

typedef struct game{
	pos_t head;
	pos_t body[200];
	pos_t food;
	dir_t dir;
	char fkey;
	int grade;
	int level;
	int count;
	int speed;
	int max_grade[10];
}game_t;

game_t g;
void game_init_game(void);
void game_init_data(void);
int  game_end(void);
int game_key(void);
void game_box(void);
void game_snack(void);
void move_snack(void);
void game_food(void);
void func_hander(int);
int save_data(void);
int load_data(void);
void game_grade_cmp(void);
int life_end(void);
#endif
