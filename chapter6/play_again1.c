//
// Created by 王琛超 on 2020/2/11.
//

#include <stdio.h>
#include <termios.h>

#define QUESTION "Do u want another transaction"

void tty_mode(int);

void set_crmode();

int get_response(char *);

int main() {
    int response;
    tty_mode(0);
    set_crmode();
    response = get_response(QUESTION);
    tty_mode(1);
    return response;
}

int get_response(char *question) {
    int input;
    printf("%s (y/n)?", question);
    while (1) {
        switch (input = getchar()) {
            case 'Y':
            case 'y':
                return 0;
            case 'N':
            case 'n':
            case EOF:
                return 1;
            default:
                printf("\n cannot understand %c ", input);
                printf("Please type y or n\n");
        }
    }
}

void set_crmode() {
    struct termios ttystate;
    tcgetattr(0, &ttystate);
    // 关闭规范模式
    ttystate.c_lflag &= ~ICANON;
    // 控制字符数数量
    ttystate.c_cc[VMIN] = 1;
    tcsetattr(0, TCSANOW, &ttystate);
}

void tty_mode(int how) {
    static struct termios original_mode;
    if (how == 0) {
        tcgetattr(0, &original_mode);
    } else if (how == 1) {
        // 还原
        tcsetattr(0, TCSANOW, &original_mode);
    }
}

