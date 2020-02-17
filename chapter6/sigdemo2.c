//
// Created by 王琛超 on 2020/2/11.
//

#include <stdio.h>
#include <signal.h>

int main() {
    // 忽略SIGINT信号
    signal(SIGINT, SIG_IGN);
    printf("u can't stop me!\n");
    while (1) {
        sleep(1);
        printf("haha\n");
    }
}

