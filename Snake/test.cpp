#include <stdio.h>
#include <unistd.h>

#define CLEAR() printf("\033[2J")
#define SAVE_CURSOR() printf("\033[s");
#define LOAD_CURSOR() printf("\033[u");
#define MOVE_TO(x, y) printf("\033[%d;%dH", (x), (y))
#define HIDE_CURSOR() printf("\033[?25l");
#define SHOW_CURSOR() printf("\033[?25h");
#define PRINT_CH(fcolor, bcolor, ch) \
    printf("\033[%d;%dm%c\033[0m", (fcolor), (bcolor), (ch));
#define PRINT_STR(fcolor, bcolor, str) \
    printf("\033[%d;%dm%s\033[0m", (fcolor), (bcolor), (str));

#define WINDOW(offset_x, offset_y, row, col, color) do{         \
for (int i = 0; i <= row; ++i)                                  \
    for (int i = 0; i <= col; ++i) {                            \
        if (i == 0 || i == row || j == 0 || j == 1 || j == col - 1 || j == col)         \
            printf("\033[%d;%dH\033[%dm \033[0m\n", i + (offset_x), j + (offset_y), (color));       \
        else        \
            printf("\033[%d;%dH%c", i + (offset_x), j + (offset_y), ' ');       \
    }       \
}while(0)

void draw_box(int offset_x, int offset_y, int row, int col, int color)
{	int i, j;
    for(i = 0;i <= row; i++)
        for(j = 0; j <= col; j++)
        {
            if(i == 0 || i == row
                    || j == 0 || j == 1 || j == col - 1 || j == col)
                printf("\033[%d;%dH\033[%dm \033[0m\n",i + offset_x,j + offset_y,color);
            else
                printf("\033[%d;%dH%c",i + offset_x,j + offset_y,' ');
        }
}

void draw_rect(int x, int y, int row, int col, int color)
{
    int i, j;
    for(i = 0; i < row; i++)
        for(j = 0; j < col; j++)
        {
            printf("\033[%d;%dH\033[%dm \033[0m\n",i + x,j + y,color);
        }
}

int
main(void) {
    // const char *str = "hello world!!!\n";
    // PRINT_STR(37,42,str);
    // int x, y;
    // x = 25;
    // y = 30;
    // MOVE_TO(x,y);
    // PRINT_STR(37,42,str);
    // SAVE_CURSOR();
    // sleep(3);
    // MOVE_TO(0,0);
    // PRINT_STR(37,42,str);
    // sleep(3);
    // LOAD_CURSOR();
    // PRINT_STR(37,42,str);
    // HIDE_CURSOR();
    // sleep(5);
    // SHOW_CURSOR();

    draw_box(1, 20, 20, 40, 44);
    draw_rect(10,25,1,2,43);

    return 0;
}
