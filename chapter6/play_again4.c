//
// Created by 王琛超 on 2020/2/11.
//

#include <stdio.h>
#include <termios.h>
#include <string.h>
#include <fcntl.h>
#include <signal.h>
#include <stdlib.h>

#define ASK "Do u want another transaction"
#define TRIES 3
#define SLEEPTIME 2
#define BEEP putchar('\a')

void tty_mode(int);
void set_cr_noecho_mode();
void set_nodely_mode();
int get_response(char *, int);
int get_ok_char();
void ctrl_c_handler();
int main() {
    int response;
    tty_mode(0);
    signal(SIGINT, ctrl_c_handler);
    signal(SIGQUIT, SIG_IGN);
    set_cr_noecho_mode();
    set_nodely_mode();
    response = get_response(ASK, TRIES);
    tty_mode(1);
    return response;
}

int get_response(char *question, int maxtries) {
    int input;
    printf("%s (y/n)?", question);
    fflush(stdout);
    while (1) {
        sleep(SLEEPTIME);
        input = get_ok_char();
        if (input == 'y') return 0;
        if (input == 'n') return 1;
        if (maxtries-- == 0) return 2;
        BEEP;
    }
}

int get_ok_char() {
    int c;
    // 搜索第是否有满足条件的字符出现
    while ((c = getchar()) != EOF && strchr("yYnN",c) == NULL);
    return c;
}

void set_cr_noecho_mode() {
    struct termios ttystate;
    tcgetattr(0, &ttystate);
    // 关闭规范模式
    ttystate.c_lflag &= ~ICANON;
    ttystate.c_lflag &= ~ECHO;
    // 控制字符数数量
    ttystate.c_cc[VMIN] = 1;
    tcsetattr(0, TCSANOW, &ttystate);
}

void set_nodely_mode() {
    int termflags;
    termflags = fcntl(0, F_GETFL);
    termflags |= O_NDELAY;
    fcntl(0, F_SETFL, termflags);
}

void tty_mode(int how) {
    static struct termios original_mode;
    static int original_flags;
    if (how == 0) {
        tcgetattr(0, &original_mode);
        original_flags = fcntl(0, F_GETFL);
    } else if (how == 1) {
        // 还原
        tcsetattr(0, TCSANOW, &original_mode);
        fcntl(0, F_SETFL, original_flags);
    }
}

void ctrl_c_handler() {
    tty_mode(1);
    exit(1);
}

