//
// Created by 王琛超 on 2020/2/13.
//

// 每次计时器到达就改变位置；每次用户输入就改变速度或者方向

#include <stdio.h>
#include <curses.h>
#include <signal.h>
#include <string.h>
#include <sys/time.h>

#define MESSAGE "hello"
#define BLANK "     "

int set_ticker(int);

int row;
int col;
int dir;

int main() {
    int delay, ndelay;
    int c;
    void move_msg(int);

    initscr();
    crmode();
    noecho();
    clear();

    row = 10;
    col = 0;
    dir = 1;
    delay = 200;

    move(row,col);
    addstr(MESSAGE);
    signal(SIGALRM, move_msg);

    set_ticker(delay);

    while (1) {
        ndelay = 0;
        c = getch(); // 不回显函数
        if (c == 'Q') break;
        if (c == ' ') dir = -dir;
        if (c == 'f' && delay > 2) ndelay = delay / 2;
        if (c == 's') ndelay = delay * 2;
        if (ndelay > 0) set_ticker(ndelay);
    }
    endwin();
    return 0;
}

// 设置定时器
int set_ticker(int n_msecs) {
    struct itimerval new_timeset;
    long n_sec, n_usecs;

    n_sec = n_msecs / 1000;
    n_usecs = (n_msecs % 1000) * 1000L;

    new_timeset.it_interval.tv_sec = n_sec;
    new_timeset.it_interval.tv_usec = n_usecs;

    new_timeset.it_value.tv_sec = n_sec;
    new_timeset.it_value.tv_usec = n_usecs;

    return setitimer(ITIMER_REAL, &new_timeset, NULL);
}

void move_msg(int signum) {
    signal(SIGALRM, move_msg);
    move(row, col);
    addstr(BLANK);
    col += dir;
    move(row, col);
    addstr(MESSAGE);
    refresh();

    if (col <= 0 && dir == -1)
        dir = 1;
    else if (dir == 1 && strlen(MESSAGE) + col >= COLS)
        dir = -1;
}

