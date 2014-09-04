#include <stdio.h>
#include "cursors.h"
#include <unistd.h>

int main(void)
{
    CLEAR();
    HIDE_CURSOR();
    WINDOWS(10, 10, 25, 50, 43);
    BODY(22, 33, 42);
    SHOW_CURSOR();

    sleep(5);
    CLEAR();

    return 0;
}

