#ifndef CURSORS_H
#define CURSORS_H

#define CLEAR() printf("\033[2J")
#define SAVE_CURSOR() printf("\033[s");
#define LOAD_CURSOR() printf("\033[u");
#define MOVE_TO(x, y) printf("\033[%d;%dH", (x), (y))
#define HIDE_CURSOR() printf("\033[?25l");
#define SHOW_CURSOR() printf("\033[?25h");
#define PRINT_CH(fcolor, bcolor, ch)                                        \
        printf("\033[%d;%dm%c\033[0m", (fcolor), (bcolor), (ch));
#define PRINT_STR(fcolor, bcolor, str)                                      \
        printf("\033[%d;%dm%s\033[0m", (fcolor), (bcolor), (str));
#define WINDOWS(offset_x, offset_y, row, col, color) do{         			\
int i, j;                                                                   \
for (i = 0; i <= row; ++i)                                                  \
    for (j = 0; j <= col; ++j) {                                            \
        if (i == 0 || i == row												\
                || j == 0 || j == 1 || j == col - 1 || j == col)         	\
            printf("\033[%d;%dH\033[%dm \033[0m\n",							\
            i + (offset_x), j + (offset_y), (color));      					\
        else        														\
            printf("\033[%d;%dH%c", i + (offset_x), j + (offset_y), ' ');   \
    }       																\
}while(0)

#define BODY(offset_x, offset_y, color) do{									\
    printf("\033[%d;%dH\033[%dm \033[0m\n",									\
        1 + (offset_x), 1 + (offset_y), color);								\
    printf("\033[%d;%dH\033[%dm \033[0m\n",									\
        1 + (offset_x), 2 + (offset_y), color);								\
}while(0)

#endif // CURSORS_H
