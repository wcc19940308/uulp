//
// Created by 王琛超 on 2020/2/12.
//
#include <stdio.h>
#include <curses.h>
main() {
    initscr();
    clear();
    for (int i = 0; i < LINES; i++) {
        move(i, i + i);
        if (i % 2 == 1) standout();
        addstr("hello, world");
        if (i % 2 == 1) standend();
    }
    refresh();
    getch();
    endwin();
}


