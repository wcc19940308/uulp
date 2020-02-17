//
// Created by 王琛超 on 2020/2/12.
//

#include <stdio.h>
#include <curses.h>

main() {
    initscr();

    clear();
    move(10,20);
    addstr("hello world");
    move(LINES - 1,0);

    refresh();
    getch();
    endwin();
}

